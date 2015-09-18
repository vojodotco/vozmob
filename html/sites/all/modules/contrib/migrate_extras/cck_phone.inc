<?php

/**
 * Primary value passed to this field must be the two letter ISO country code of
 * the phone number.
 *
 * Arguments are used to specify all the other values:
 *   'number' - The actual phone number.
 *   'extension' - The extension.
 *
 * Add the source field mappings to the argument array then add null mappings to
 * avoid having fields flagged as unmapped:
 * @code
 *   $arguments = array(
 *     'number' => array('source_field' => 'phone_number'),
 *     'extension' => array('source_field' => 'profile_phone_ext'),
 *   );
 *   // The country should be passed in as the primary value.
 *   $this->addFieldMapping('field_user_phone', 'profile_country')
 *        ->arguments($arguments);
 *   // Since the excerpt is mapped via an argument, add a null mapping so it's
 *   // not flagged as unmapped.
 *   $this->addFieldMapping(NULL, 'profile_phone_number');
 *   $this->addFieldMapping(NULL, 'profile_phone_ext');
 * @endcode
 */
class MigrateCckPhoneHandler extends MigrateFieldHandler {
  public function __construct() {
    $this->registerTypes(array('phone_number'));
  }

  static function arguments($number = '', $extension = '') {
    return array('number' => $number, 'extension' => $extension);
  }

  public function prepare($entity, array $instance, array $values) {
    $arguments = array();
    if (isset($values['arguments'])) {
      $arguments = array_filter($values['arguments']);
      unset($values['arguments']);
    }

    // Setup the standard Field API array for saving.
    $delta = 0;
    foreach ($values as $value) {
      $return[$delta]['country_codes'] = drupal_strtolower($value);
      $return[$delta]['number'] = isset($arguments['number']) ? $arguments['number'] : '';
      $return[$delta]['extension'] = isset($arguments['extension']) ? $arguments['extension'] : '';
      $delta++;
    }

    return isset($return) ? $return : NULL;
  }
}
