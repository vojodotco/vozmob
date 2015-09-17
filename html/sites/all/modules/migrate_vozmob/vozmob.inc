<?php
$saved_count = 0;
/**
 *
 */
abstract class VozmobMigration extends DynamicMigration {
  public function __construct() {
    // Always call the parent constructor first for basic setup
    //parent::__construct();
    //parent::__construct(MigrateGroup::getInstance('vozomb', array('default')));
    parent::__construct(MigrateGroup::getInstance('vozomb'));
    $db_config = include('migrate_config.php');
    Database::addConnectionInfo('vozmob_migration', 'default', $db_config);
    
    // With migrate_ui enabled, migration pages will indicate people involved in
    // the particular migration, with their role and contact info. We default the
    // list in the shared class; it can be overridden for specific migrations.
    $this->team = array(
      new MigrateTeamMember('Mario Romero', 'mario@romero.fm', t('Implementor')),
    );

    // Individual mappings in a migration can be linked to a ticket or issue
    // in an external tracking system. Define the URL pattern here in the shared
    // class with ':id:' representing the position of the issue number, then add
    // ->issueNumber(1234) to a mapping.
    //$this->issuePattern = 'http://drupal.org/node/:id:';
  }
}




class VozmobUserMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob Users');
    $this->map = new MigrateSQLMap($this->machineName,
      array('uid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'User ID.'
              )
           ),
        MigrateDestinationUser::getKeySchema()
    );

    $source_fields = array(
      'uid' => t('User ID'),
      'roles' => t('The set of roles assigned to a user.'),
      'role_names' => t('The set of role names assigned to a user.'),
    );

    
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('users', 'users')
      ->fields('users', array('uid','name', 'pass', 'mail','theme','signature','created','access','login','status', 'timezone','language','picture','init','signature_format'));

    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationUser();

    $this->addSimpleMappings(array('pass','mail','theme','signature','created','access','login','status', 'timezone','language','picture','init','signature_format'));

    //$this->addFieldMapping('uid', 'uid');
    $this->addFieldMapping('roles', 'roles');
    $this->addFieldMapping('role_names', 'role_names');
    $this->addFieldMapping('name', 'name')
         ->dedupe('users', 'name');

  }

  // massage the user roles before saving
  public function prepareRow($current_row) {


    $current_row->picture = str_replace('sites/default/files/', 'sites/default/s3files/',$current_row->picture);
     

    global $saved_count;
    //print "hellofrom prepareRow\n";
    $source_id = $current_row->uid;
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('users_roles', 'r')
      ->fields('r', array('uid', 'rid'))
      ->condition('r.uid', $source_id, '=');
    $results = $query->execute();
    // add the Authenticated role for everyone
    $roles = array('2' => '2');
    $role_names = array();
    foreach ($results as $row) {
      $roles[$row->rid] = $row->rid;
      $aquery = db_select('role', 'rl')
       ->fields('rl', array('rid','name'))
      ->condition('rl.rid', $row->rid, '=');
     $rlresults = $aquery->execute();
     foreach ($rlresults as $rlrow) {
       $role_names[$rlrow->name] = $rlrow->name;
     }
    }
    $current_row->roles = $roles;
    $current_row->role_names = $role_names;
    //print_r($roles);
    //return TRUE;
    //sms user test
    $saved_count++;
    print $saved_count;
    print "\n";
    //return TRUE;

    
    return TRUE;
    // return FALSE if you wish to skip a particular row
  }
  
}



class VozmobSMSUserMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migrate sms_user table');
    $this->dependencies = array('VozmobUser');

    $this->map = new MigrateSQLMap($this->machineName,
      array('uid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'User ID.'
              )
           ),
        MigrateDestinationTable::getKeySchema('sms_user')
    );


    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('sms_user', 's')
       ->fields('s', array('uid', 'delta', 'number', 'status', 'code', 'gateway'));
       
    /* $source_fields = array(
      'uid' => t('User ID'),
      'roles' => t('The set of roles assigned to a user.'),
      );*/

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTable('sms_user');
   

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);
    $this->addFieldMapping('sid', 'delta');
    $this->addSimpleMappings(array('number', 'status', 'code', 'gateway'));

  }

}


class VozmobTermMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Migrate taxonomy terms');
    $this->map = new MigrateSQLMap($this->machineName,
      array('tid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'Term ID.'
              )
           ),
        MigrateDestinationTerm::getKeySchema()
    );


    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('term_data', 'term')
      ->fields('term', array('tid', 'vid','name', 'description','weight'));
    $source_fields = array(
      'tid' => t('Term ID'),
      'parent' => t('Term Parent.'),
      );
    

    
    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationTerm('terms');
    $this->addSimpleMappings(array('vid','name','description','weight'));
    $this->addFieldMapping('parent', 'parent');
  }


  /*public function prepareRow($current_row) {

    
    $source_id = $current_row->tid;
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('term_hierarchy', 'r')
      ->fields('r', array('tid', 'parent'))
      ->condition('r.tid', $source_id, '=');
    $results = $query->execute();

    
    
    $current_row->parent = $results->fetchAll();
  }
  */


}





class VozmobTermSynonymMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('term_synonym table');
    $this->dependencies = array('VozmobTerm');

    $this->map = new MigrateSQLMap($this->machineName,
      array('tsid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'Term Synonym ID.'
              )
           ),
        MigrateDestinationTable::getKeySchema('term_synonym')
    );

    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('term_synonym', 's')
       ->fields('s', array('tsid', 'tid', 'name'));
       
    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationTable('term_synonym');
   

    $this->addFieldMapping('tid', 'tid')
      ->sourceMigration('VozmobTerm');
    
    $this->addSimpleMappings(array('name'));

  }

}

/**
class VozmobNodeMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob nodes');
    $this->dependencies = array('VozmobUser');
    $this->map = new MigrateSQLMap($this->machineName,
      array('nid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'Node ID.',
	      //'alias' => 'node',
	     ),
	    'vid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'VID.',
	      //'alias' => 'node',
	     )


           ),

      array('nid' => array(
	      'type' => 'int',
              'not null' => TRUE,
              'description' => 'Node ID.',
	      //'alias' => 'node',
	   ),
	    'vid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'VID.',
	      //'alias' => 'node',
	     )


           )
				   //MigrateDestinationTable::getKeySchema('node')
    );

    
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('node', 'node');
    //$query->leftJoin('node_counter', 'nc', 'nc.nid = node.nid');
    $query->fields('node', array('nid', 'vid', 'type', 'language','title','uid','status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'));
    //$query->fields('nc', array('totalcount','daycount','timestamp'));
    //$query->join('node_revisions', 'nr', 'nr.vid = node.vid');
    //$query->fields('nr', array('body', 'teaser', 'format', 'log', 'uid'));
    
    $source_fields = array(
      'vid_to_map' => t('vid to map'),

      );

    $this->source = new MigrateSourceSQL($query, $source_fields);

    $this->destination = new MigrateDestinationTable('node');
    $this->addSimpleMappings(array('title','type','created','changed','status','promote', 'sticky', 'revision','language', 'tnid', 'translate', 'comment','moderate'));


    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);

    // $this->addFieldMapping('nid', 'nid');
    $this->addFieldMapping('vid', 'vid_to_map');

  }

  public function prepareRow($current_row) {

    $result = db_query("SHOW TABLE STATUS LIKE 'node'");
    $record = db_fetch_object($result);
    $current_row->vid_to_map = $record->Auto_increment+1;
    return True;
      

    }

}
**/





class VozmobNodeMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob nodes');
    $this->dependencies = array('VozmobTerm', 'VozmobUser');
    $this->map = new MigrateSQLMap($this->machineName,
      array('nid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'Node ID.',
	      'alias' => 'node',
              )
           ),
        MigrateDestinationNode::getKeySchema()
    );

    
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('node', 'node');
    $query->leftJoin('node_counter', 'nc', 'nc.nid = node.nid');
    $query->fields('node', array('nid', 'vid', 'type', 'language','title','uid','status', 'created', 'changed', 'comment', 'promote', 'moderate', 'sticky', 'tnid', 'translate'));
    $query->fields('nc', array('totalcount','daycount','timestamp'));
    $query->join('node_revisions', 'nr', 'nr.vid = node.vid');
    $query->fields('nr', array('body', 'teaser', 'format', 'log', 'uid'));
    
    $source_fields = array(
      'uid' => t('User ID'),
      'revision' => t('node revision.'),
      );

    $this->source = new MigrateSourceSQL($query, $source_fields);

    $this->destination = new MigrateDestinationNode('Nodes');
    $this->addSimpleMappings(array('title','vid','type','created','changed','status','promote', 'sticky', 'revision','language', 'tnid', 'translate', 'comment','moderate'));


    $this->addFieldMapping('body', 'body');
    $this->addFieldMapping('format', 'format');
    $this->addFieldMapping('teaser', 'teaser');
    $this->addFieldMapping('log', 'log');
    //$this->addFieldMapping('revision_uid', 'nr_uid');
    $this->addFieldMapping('totalcount', 'totalcount');
    $this->addFieldMapping('daycount', 'daycount');
    $this->addFieldMapping('timestamp', 'timestamp');

    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);

    $this->addFieldMapping('revision_uid', 'nr_uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);

    

  }

}




class VozmobNodeRevisionMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob node revisions');
    $this->dependencies = array('VozmobNode', 'VozmobUser');
    //perhaps needs to get vid from VozmobNode, but not all vids will be on the table,
    // only those from the latest revision
    
    $this->map = new MigrateSQLMap($this->machineName,
      array('vid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'Node Revision ID.',
              )
           ),
        MigrateDestinationTable::getKeySchema('node_revisions')
    );

    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('node_revisions', 'nr');
    $query->fields('nr', array('vid','nid','title','body', 'teaser', 'format', 'log', 'uid', 'timestamp'));

    $this->source = new MigrateSourceSQL($query);

    $this->destination = new MigrateDestinationTable('node_revisions');
    $this->addSimpleMappings(array('title','body', 'teaser', 'format', 'log', 'timestamp'));

    $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode');

    $this->addFieldMapping('vid', 'vid')
      ->sourceMigration('VozmobNode');

    
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);

  }
}




class VozmobTermNodeMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob term node');
    $this->dependencies = array('VozmobNode', 'VozmobNodeRevision', 'VozmobTerm');
    $this->map = new MigrateSQLMap($this->machineName,
      array('vid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'Node Revision ID.',
			   ),
	    'tid' => array(
              'type' => 'int',
              'not null' => TRUE,
              'description' => 'Term ID.',
			   ),
           ),
        MigrateDestinationTable::getKeySchema('term_node')
    );


    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('term_node', 'tn');
    $query->fields('tn', array('nid','vid','tid'));

    
    $source_fields = array(
	'vid_to_map' => t('vid we will map the vid to'),
    );



    $this->source = new MigrateSourceSQL($query, $source_fields);


    
    $this->destination = new MigrateDestinationTable('term_node');


    $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode');

    $this->addFieldMapping('vid', 'vid_to_map');

    
    $this->addFieldMapping('tid', 'tid')
      ->sourceMigration('VozmobTerm');


  }

  
  // massage the user roles before saving
  public function prepareRow($current_row) {


    $query = Database::getConnection('default', 'vozmob_migration')
	->select('node', 'n');
    $query->fields('n', array('vid'));
    $query->condition('n.nid', $current_row->nid, '=');
    $results= $query->execute()->fetchAll();
    if($current_row->vid != $results[0]->vid) {
      return FALSE;
    }

    $query = db_select('migrate_map_vozmobnode', 'mn')
      ->fields('mn', array('destid1'))
      ->condition('mn.sourceid1', $current_row->nid, '=')
      ->range(0,1);
    $results = $query->execute()->fetchAll();
    $mapped_nid = $results[0]->destid1;


    $query = db_select('node', 'n')
      ->fields('n', array('vid'))
      ->condition('n.nid', $mapped_nid, '=')
      ->range(0,1);
    $results = $query->execute()->fetchAll();
    $current_row->vid_to_map = $results[0]->vid;
    
    return TRUE;

  }

  
}



class VozmobCommentsMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob comments migration');
    $this->dependencies = array('VozmobNode', 'VozmobUser');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'cid' => array(
           'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'Id of the comment',
           ),
        ),
      MigrateDestinationTable::getKeySchema('comments')
      );
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('comments', 'c');
    $query->fields('c', array('cid','pid','nid','uid', 'subject', 'comment', 'hostname', 'timestamp', 'status','format','thread','name','mail','homepage'));

    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTable('comments');
    $this->addSimpleMappings(array('cid','subject', 'timestamp', 'status', 'hostname', 'name', 'mail', 'homepage', 'thread', 'pid', 'comment', 'format'));

      $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode');
      
    
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);

  }
}



/**
class VozmobOGMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob OG migration');
    $this->dependencies = array('VozmobNode', 'VozmobUser');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
           'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'node id',
           ),
        ),
      MigrateDestinationOGMembership::getKeySchema()
      );

    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('og', 'og');
    $query->fields('og', array('nid','og_selective','og_description','og_theme', 'og_register', 'og_directory', 'og_language', 'og_private'));


    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationOGMembership();

    $this->addFieldMapping('gid', 'nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);


    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);

    $this->addSimpleMappings(array('is_active','is_admin','created'));

  

  }
}



**/




class VozmobOGMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob OG migration');
    $this->dependencies = array('VozmobNode');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
           'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'node id',
           ),
        ),
      MigrateDestinationTable::getKeySchema('og')
      );


    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('og', 'og');
    $query->fields('og', array('nid','og_selective','og_description','og_theme', 'og_register', 'og_directory', 'og_language', 'og_private'));


    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTable('og');

    $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);

    $this->addSimpleMappings(array('og_selective','og_description','og_theme', 'og_register', 'og_directory', 'og_language', 'og_private'));

  

  }
}







class VozmobOGUIDMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob OG UID migration');
    $this->dependencies = array('VozmobNode', 'VozmobUser');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
           'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'node id',
           ),
	'uid' => array(
	   'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'user id',
           ),
        ),
      MigrateDestinationTable::getKeySchema('og_uid')
      );



    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('og_uid', 'ogu');
    $query->fields('ogu', array('nid','og_role','is_active','is_admin', 'uid', 'created', 'changed'));


    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTable('og_uid');

    $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);
    
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);
    
    $this->addSimpleMappings(array('og_role','is_active','is_admin','created', 'changed'));

  

  }
}




class VozmobOGAncestryMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob OG ancestry migration');
    $this->dependencies = array('VozmobNode');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
           'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'node id',
           ),
	'group_nid' => array(
	   'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'group node id',
           ),
        ),
      MigrateDestinationTable::getKeySchema('og_ancestry')
      );



    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('og_ancestry', 'oga');
    $query->fields('oga', array('nid','group_nid'));


    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTable('og_ancestry');

    $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);
    
    $this->addFieldMapping('group_nid', 'group_nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);
    
  

  }
}




class VozmobOGAccessPostMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob OG access post migration');
    $this->dependencies = array('VozmobNode');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'nid' => array(
           'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'node id',
	  ),
        ),
      MigrateDestinationTable::getKeySchema('og_access_post')
      );



    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('og_access_post', 'ogap');
    $query->fields('ogap', array('nid','og_public'));


    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTable('og_access_post');

    $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);
    $this->addSimpleMappings(array('og_public'));


    
    }
}





class VozmobFileMigration extends VozmobMigration {
  public function __construct() {
    parent::__construct();
    $this->description = t('Vozmob file migration');
    $this->dependencies = array('VozmobUser');
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'fid' => array(
           'type' => 'int',
           'length' => 11,
           'not null' => TRUE,
           'description' => 'file id',
	  ),
        ),
      MigrateDestinationTable::getKeySchema('files')
      );


    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('files', 'f');
    $query->fields('f', array('fid','uid', 'filename','filepath','filemime','filesize','status','timestamp'));


    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTable('files');

 
    $this->addFieldMapping('uid', 'uid')
      ->sourceMigration('VozmobUser')
      ->defaultValue(1);

    
    $this->addSimpleMappings(array('filename','filemime','filesize','status','timestamp'));

    $this->addFieldMapping('filepath', 'filepath');

    
    }


    public function prepareRow($current_row) {

      $current_row->filepath = str_replace('sites/default/files/', 'sites/default/s3files/',$current_row->filepath);
      return TRUE;


    }
}



class VozmobCFIMigration extends VozmobMigration {
  public function __construct() {

    /**
       RUN TINS QUERY BEFORE RUNNING THE MIGRATION as the vozmobnode migration seems to add content_field_image rows with a NULL FID
       delete from content_field_image where vid in (select vid from node where nid in (select destid1 from migrate_map_vozmobnode));

    **/
    parent::__construct();
    $this->description = t('Vozmob content_field_image migration');
    $this->dependencies = array('VozmobNode', 'VozmobFile');
    $table_name = 'content_field_image';
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'vid' => array(
           'type' => 'int',
           'length' => 10,
           'not null' => TRUE,
           'description' => 'vid',
	  ),
	  'delta' => array(
           'type' => 'int',
           'length' => 10,
           'not null' => TRUE,
           'description' => 'delta',
	  ),

        ),
      MigrateDestinationTable::getKeySchema($table_name)
      );

   Database::addConnectionInfo('vozmob_migration', 'default', array(
      'driver' => 'mysql',
      'database' => 'vozmob',
      'username' => 'vozmob_dev',
      'password' => 'vm4vojo2dev',
      'host' => 'localhost',
      'prefix' => '',
    ));


    
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('content_field_image', 'cf');
    $query->fields('cf', array('vid','nid', 'delta','field_image_fid','field_image_list','field_image_data'));

    $source_fields = array(
	'vid_to_map' => t('vid we will map the vid to'),
    );



    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);



    
    $this->addFieldMapping('field_image_fid', 'field_image_fid')
      ->sourceMigration('VozmobFile')
      ->defaultValue(1);
    
    $this->addSimpleMappings(array('delta','field_image_list','field_image_data'));
    $this->addFieldMapping('vid','vid_to_map');

    /*$this->addFieldMapping('vid', 'vid')
      ->dedupe('content_field_image', 'vid');*/


    }



    public function prepareRow($current_row) {


      
      $query = Database::getConnection('default', 'vozmob_migration')
	->select('node', 'n');
      $query->fields('n', array('vid'));
      $query->condition('n.nid', $current_row->nid, '=');
       $results= $query->execute()->fetchAll();
       if($current_row->vid != $results[0]->vid) {
	 return FALSE;
       }

       $query = db_select('migrate_map_vozmobnode', 'mn')
      ->fields('mn', array('destid1'))
      ->condition('mn.sourceid1', $current_row->nid, '=')
      ->range(0,1);
      $results = $query->execute()->fetchAll();
      $mapped_nid = $results[0]->destid1;


      $query = db_select('node', 'n')
      ->fields('n', array('vid'))
      ->condition('n.nid', $mapped_nid, '=')
      ->range(0,1);
      $results = $query->execute()->fetchAll();
      $current_row->vid_to_map = $results[0]->vid;
      
      return True;

    }  
}







class VozmobUploadMigration extends VozmobMigration {
  public function __construct() {

    parent::__construct();
    $this->description = t('Vozmob upload table migration');
    $this->dependencies = array('VozmobNode', 'VozmobFile');
    $table_name = 'upload';
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'fid' => array(
           'type' => 'int',
           'length' => 10,
           'not null' => TRUE,
           'description' => 'vid',
	  ),
	  'vid' => array(
           'type' => 'int',
           'length' => 10,
           'not null' => TRUE,
           'description' => 'delta',
	  ),

        ),
      MigrateDestinationTable::getKeySchema($table_name)
      );

    
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select('upload', 'u');
    $query->fields('u', array('fid','nid', 'vid','description','list','weight'));

    $source_fields = array(
	'vid_to_map' => t('vid we will map the vid to'),
    );

    $this->source = new MigrateSourceSQL($query, $source_fields);
    $this->destination = new MigrateDestinationTable($table_name);

    $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);
    
    $this->addFieldMapping('fid', 'fid')
      ->sourceMigration('VozmobFile')
      ->defaultValue(1);
    
    $this->addSimpleMappings(array('description','list','weight'));
    $this->addFieldMapping('vid','vid_to_map');



    }


    public function prepareRow($current_row) {



      $query = Database::getConnection('default', 'vozmob_migration')
	->select('files', 'f');
      $query->fields('f', array('fid'));
      $query->condition('f.fid', $current_row->fid, '=');
       $results= $query->execute()->fetchAll();

       if (count($results)==0) {
	 return FALSE;
       }


      
      $query = Database::getConnection('default', 'vozmob_migration')
	->select('node', 'n');
      $query->fields('n', array('vid'));
      $query->condition('n.nid', $current_row->nid, '=');
       $results= $query->execute()->fetchAll();
       if($current_row->vid != $results[0]->vid) {
	 return FALSE;
       }

       $query = db_select('migrate_map_vozmobnode', 'mn')
      ->fields('mn', array('destid1'))
      ->condition('mn.sourceid1', $current_row->nid, '=')
      ->range(0,1);
      $results = $query->execute()->fetchAll();
      $mapped_nid = $results[0]->destid1;


      $query = db_select('node', 'n')
      ->fields('n', array('vid'))
      ->condition('n.nid', $mapped_nid, '=')
      ->range(0,1);
      $results = $query->execute()->fetchAll();
      $current_row->vid_to_map = $results[0]->vid;
      
      return True;

    }  
}













class VozmobMMFilesMigration extends VozmobMigration {
  public function __construct() {

    parent::__construct();
    $this->description = t('Vozmob media mover files table migration');
    $this->dependencies = array('VozmobNode', 'VozmobFile');
    $table_name = 'media_mover_files';
    $this->map = new MigrateSQLMap($this->machineName,
      array(
        'mmfid' => array(
           'type' => 'int',
           'length' => 10,
           'not null' => TRUE,
           'description' => 'vid',
	  ),	  
        ),
      MigrateDestinationTable::getKeySchema($table_name)
      );

        
    $query = Database::getConnection('default', 'vozmob_migration')
      ->select($table_name, 'm');
    $query->fields('m', array('mmfid','nid', 'fid','cid','harvest_file','process_file','storage_file','complete_file','status','date','data'));



    $this->source = new MigrateSourceSQL($query);
    $this->destination = new MigrateDestinationTable($table_name);


     $this->addFieldMapping('nid', 'nid')
      ->sourceMigration('VozmobNode')
      ->defaultValue(1);
    
    $this->addFieldMapping('fid', 'fid')
      ->sourceMigration('VozmobFile')
      ->defaultValue(1);
    
    $this->addSimpleMappings(array('cid','harvest_file','process_file','storage_file','complete_file','status','date','data'));


    }


  public function prepareRow($current_row) {

      $current_row->harvest_file = str_replace('sites/default/files/', 'sites/default/s3files/',$current_row->harvest_file);

      $current_row->process_file = str_replace('sites/default/files/', 'sites/default/s3files/',$current_row->process_file);

      $current_row->storage_file = str_replace('sites/default/files/', 'sites/default/s3files/',$current_row->storage_file);

      $current_row->complete_file = str_replace('sites/default/files/', 'sites/default/s3files/',$current_row->complete_file);

      return TRUE;


    }


}