<?php

/**
 * Implementation of hook_node_info().
 */
function migrate_extras_date_node_info() {
  $items = array(
    'migrate_example_date' => array(
      'name' => t('Migrate example - dates'),
      'module' => 'features',
      'description' => t('This content type is used for demonstrating and testing Migrate Example support for the Date module.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'has_body' => '1',
      'body_label' => t('Body'),
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}
