<?php

/**
 * @file
 * Migrate plugin for the Content Taxonomy module as a destination.
 *
 * The example field mapping code below shows how to import terms in content
 * taxonomy field.
 *
 * Note that these code snippet must go into your Migration
 * subclass's constructor - see the migrate_example module
 * for an example of how and where to use field mappings.
 *
 *  // Import source field "content_taxonomy" containing tids into
 *  // destination field field_content_taxonomy:
 *  $this->addFieldMapping('field_content_taxonomy', 'term');
 *
 *  // Import source field "content_taxonomy" containing names into
 *  // destination field field_content_taxonomy and optionally telling which 
 *  // vocabulary to search in (in case you have equal terms name in several
 *  // vocabularies):
 *  $arguments = MigrateContentTaxonomyFieldHandler::arguments('name', 4);
 *  // 4 is the vid of the vocabulary to search in
 *  $this->addFieldMapping('field_content_taxonomy', 'term')
 *    ->arguments($arguments);
 */

/**
 * Field handler.
 */
class MigrateContentTaxonomyFieldHandler extends MigrateFieldHandler {

  public function __construct() {
    $this->registerTypes(array('content_taxonomy'));
  }

  static function arguments($mode = 'tid', $vid = 0) {
    return array('mode' => $mode, 'vid' => $vid);
  }

  public function prepare($entity, array $instance, array $values) {
    $mode = $values['arguments']['mode'];
    $vid = $values['arguments']['vid'];

    //remove arguments or they will be searched too
    unset($values['arguments']);
    $values = array_values($values);

    $return = array();

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      if ($mode == 'name') {
        if ($vid > 0) {
          $query = db_select('term_data', 'td')
                  ->fields('td', array('tid'))
                  ->condition('name', $value, '=')
                  ->condition('vid', $vid, '=');
        }
        else {
          $query = db_select('term_data', 'td')
                  ->fields('td', array('tid'))
                  ->condition('name', $value, '=');
        }
        $result = $query->execute();
        $record = $result->fetchAssoc();
        if ($record['tid'] == 0) {
          //dvm('Term not found: '.$value);
          continue;
        }
        $value = $record['tid'];
      }
      $item = array();
      $item['value'] = $value;

      $return[$delta] = $item;
      $delta++;
    }
    return empty($return) ? NULL : $return;
  }

}
