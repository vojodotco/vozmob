<?php


function og_domain_admin_page() {
  $out = '';
  
  // set some internal variables
  $out .= drupal_get_form('og_domain_admin_page_form');

  return $out;
}

function og_domain_admin_page_form() {
  $form = array(
    'og_domain_default_value' => array(
      '#type' => 'textfield',
      '#title' => 'Default domain',
      '#default_value' => variable_get('og_domain_default_value', _og_domain_get_base_url_domain()),
    ),
    'og_domain_disabled_page' => array(
      '#type' => 'textfield',
      '#title' => 'Redirect page when the domain is disabled',
      '#default_value' => variable_get('og_domain_disabled_page', _og_domain_get_default_disabled_page()),
    ),
    'og_domain_force_context' => array(
      '#type' => 'checkbox',
      '#title' => 'Force OG context on every domain',
      '#default_value' => variable_get('og_domain_force_context', FALSE),
    ),
    'og_domain_force_theme' => array(
      '#type' => 'checkbox',
      '#title' => 'Force theme on domain',
      '#default_value' => variable_get('og_domain_force_theme', FALSE),
    ),
  );
  return system_settings_form(array_merge_recursive($form, _og_domain_invoke_all('admin_form')));
}

function _og_domain_check_mappings_access($record) {
  global $user;
  return $record['node']->uid == $user->uid && node_access("update", $record['node']);
}

function og_domain_mappings_admin_page($all = FALSE) {
  $header = array('Group', 'Domain', '&nbsp;');
  $rows = array();
  $records = _og_domain_get_all(OG_DOMAIN_WITH_NODEOBJECTS);
  if(!$all) $records = array_filter($records, '_og_domain_check_mappings_access');
  foreach($records as $r) {
    $rows []= array(
      l($r['node']->title, 'node/'.$r['node']->nid) . ' (' . l(t('Edit'), 'node/'.$r['node']->nid.'/edit') . ')',
      $r['domain'],
      l(t('Unmap'), ($all ? 'admin/og/domain/mappings/unmap/' : 'og_domain/mappings/unmap/').$r['node']->nid),
    );
  }
  return theme('table', $header, $rows);
}

function og_domain_manager_admin_page($all = FALSE) {
  $header = $all ? array('Domain', 'User', '&nbsp;') : array('Domain', '&nbsp;');
  $rows = array();
  if($all) {
    $records = _og_domain_get_all_domains();
    foreach($records as $r) {
      $rows []= array(
        $r['domain'],
        $r['name'],
        l(t('Delete'), 'admin/og/domain/manager/delete/'.$r['did']),
      );
    }
  } else {
    global $user;
    $records = _og_domain_get_all_domains($user->uid);
    foreach($records as $r) {
      $rows []= array(
        $r['domain'],
        l(t('Delete'), 'og_domain/manager/delete/'.$r['did']),
      );
    }
  }
  return theme('table', $header, $rows);
}

function og_domain_manager_add_page($is_admin = FALSE) {
  return drupal_get_form('og_domain_manager_form', !$is_admin);
}

function og_domain_manager_delete_page($did, $is_admin = FALSE) {
  global $user;
  if(!$is_admin && !_og_domain_check_user($did, $user->uid))
    drupal_access_denied();
  else return drupal_get_form('og_domain_manager_delete_form', $did, $is_admin);
}

function og_domain_manager_delete_form($form, $did, $is_admin) {
  $f = array();

  $f['#redirect'] = $is_admin ? 'admin/og/domain/manager' : 'og_domain/manager';

  $f['did'] = array(
    '#type' => 'value',
    '#value' => $did,
  );

  $f['is_admin'] = array(
    '#type' => 'value',
    '#value' => (int)(bool)$is_admin,
  );

  $f['disclaimer'] = array(
    '#type' => 'item',
    '#title' => 'Are you sure you want to delete this domain?',
    '#description' => t('This action cannot be undone'),
  );

  $f['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );

  return $f;
}

function og_domain_manager_delete_form_validate($form, &$form_state) {
  global $user;
  if(!$form_state['values']['is_admin'] && !_og_domain_check_user($form_state['values']['did'], $user->uid)) {
    form_set_error('', 'Permission denied');
  }
}

function og_domain_manager_delete_form_submit($form, &$form_state) {
  _og_domain_delete_domain($form_state['values']['did']);
	drupal_set_message(t('Domain is deleted.'));
	drupal_goto('admin/og/domain/manager');
}

function og_domain_manager_form($form, $auto_user = TRUE, $data = array()) {
  $f = array();
  $f['did'] = array(
    '#type' => 'value',
    '#value' => isset($data['did']) ? $data['did'] : 0,
  );
  $f['domain'] = array(
    '#type' => 'textfield',
    '#default_value' => isset($data['domain']) ? $data['domain'] : '',
    '#title' => t('Domain'),
    '#required' => TRUE,
  );
  $f['force_check'] = array(
    '#type' => 'checkbox',
    '#default_value' => isset($data['force_check']) ? $data['force_check'] : 1,
    '#title' => 'Force check domain',
    '#required' => TRUE,
  );
  if($auto_user) {
    global $user;
    $f['uid'] = array(
      '#type' => 'value',
      '#value' => $user->uid,
    );
  } else {
    $rows = db_fetch_all(db_query('SELECT uid,name FROM {users}'));
    $options = array();
    foreach($rows as $r) {
      if(_og_domain_user_access(NULL, user_load($r['uid']))) {
        $options[$r['uid']] = $r['name'];
      }
    }
    $f['uid'] = array(
      '#type' => 'select',
      '#title' => 'User',
      '#options' => $options,
      '#default_value' => isset($data['uid']) ? $data['uid'] : 0,
      '#required' => TRUE,
    );
  }
  $f['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );
  return $f;
}

function og_domain_manager_form_validate($form, &$form_state) {
  if($form_state['values']['force_check']) {
    $domain = gethostbyname($form_state['values']['domain']);
    if($domain == $form_state['values']['domain'])
      form_set_error('domain', t('The domain does not exists'));
    else if($domain != $_SERVER['SERVER_ADDR']) {
      form_set_error('domain', t('The domain does not point to the server IP: %ip', array('%ip' => $_SERVER['SERVER_ADDR'])));
    }
  }
  if(_og_domain_get_did_by_domain($form_state['values']['domain'])) {
    form_set_error('domain', t('This domain is already exists'));
  }
}

function og_domain_manager_form_submit($form, &$form_state) {
  if($form_state['values']['did'] == 0) {
    _og_domain_add_domain($form_state['values']['domain'], $form_state['values']['uid']);
  } else {
    _og_domain_update_domain($form_state['values']['did'], $form_state['values']['domain'], $form_state['values']['uid']);
  }
  drupal_set_message('Domain added.');
}

function og_domain_mappings_unmap_admin_page($nid, $is_admin = FALSE) {
  if(!$is_admin && !_og_domain_check_mappings_access(array('node' => node_load($nid)))) {
    drupal_access_denied();
  } else {
    if(_og_domain_db_lookup_domain($nid) === FALSE) {
      drupal_goto($is_admin ? 'admin/og/domain/mappings' : 'og_domain/mappings');
    } else {
      return drupal_get_form('og_domain_unmap_form', $nid, $is_admin);
    }
  }
}

function og_domain_unmap_form($form_object, $nid, $is_admin = FALSE) {
  $form = array();

  $form['#redirect'] = $is_admin ? 'admin/og/domain/mappings' : 'og_domain/mappings';
  
  $form['nid'] = array(
    '#type' => 'hidden',
    '#value' => $nid,
  );

  $form['disclaimer'] = array(
    '#type' => 'item',
    '#title' => 'Are you sure you want to delete this mapping?',
    '#description' => t('This action cannot be undone'),
  );

  $form['delete'] = array(
    '#type' => 'submit',
    '#value' => t('Delete'),
  );

  return $form;
}

function og_domain_unmap_form_validate($form, &$form_state) {
  
}

function og_domain_unmap_form_submit($form, &$form_state) {
  _og_domain_unmap_by_nid($form_state['values']['nid']);
}