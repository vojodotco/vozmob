<?php

/**
 * @file
 * Support for the Formatted number module.
 */

/**
 * Field handler.
 */
class MigrateFormattedNumberFieldHandler extends MigrateValueFieldHandler {
  public function __construct() {
    $this->registerTypes(array(
      'formatted_tinyint',
      'formatted_tinyint_unsigned',
      'formatted_smallint',
      'formatted_smallint_unsigned',
      'formatted_mediumint',
      'formatted_mediumint_unsigned',
      'formatted_integer',
      'formatted_integer_unsigned',
      'formatted_bigint',
      'formatted_bigint_unsigned',
      'formatted_decimal',
      'formatted_float',
    ));
  }
}
