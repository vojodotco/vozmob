<?php
/**
 * @file
 * Migrate 6.x-2.x Plugin for the Embedded Media Field module as a destination.
 *
 * The example field mapping code below shows how to import video urls in
 * emvideo field.
 *
 * Note that these code snippet must go into your Migration
 * subclass's constructor - see the migrate_example module
 * for an example of how and where to use field mappings.
 *
 *  // Import source field "url_video" containing urls into
 *  // destination field field_emvideo:
 *  $this->addFieldMapping('field_emvideo', 'url_video');
 *
 *  // Import source field "url_video" containing names into
 *  // destination field field_emvideo (youtube provider is the default,
 *  // so it's not needed to pass this argument in this case):
 *  $arguments = MigrateEmvideoFieldHandler::arguments('youtube');
 *  $this->addFieldMapping('field_emvideo', 'url_video')
 *    ->arguments($arguments);
 */

/**
 * Field handler.
 */
class MigrateEmvideoFieldHandler extends MigrateFieldHandler {
  public function __construct() {
    $this->registerTypes(array('emvideo'));
  }

  static function arguments($provider = 'youtube') {
    return array('provider' => $provider);
  }

  public function prepare($entity, array $instance, array $values) {
    $provider = $values['arguments']['provider'];

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      $item = array();
      $item['value'] = basename($value);
      $item['embed'] = $value;
      $item['provider'] = $provider;

      $return[$delta] = $item;
      $delta++;
    }

    return isset($return) ? $return : NULL;
  }
}
