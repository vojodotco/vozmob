<?php


/**
 * Implementation of hook_admin_form().
 *
 * @return array
 */
function lockedcontenttypes_admin_form() {
  $types = array();
  foreach(node_get_types() as $t) {
    if(og_is_omitted_type($t->type))
      $types[$t->type] = $t->name;
  }
  $default = variable_get('og_domain_locked_content_types', array());
  return array(
    'og_domain_locked_content_types' => array(
      '#type' => 'checkboxes',
      '#title' => t('Locked content types'),
      '#options' => $types,
      '#default_value' => $default,
    ),
  );
}

/**
 * Implementation of hook_domain().
 *
 * @param stdClass $node
 * @return array
 */
function lockedcontettypes_domain($node) {
  $lt = variable_get('og_domain_locked_content_types', array());
  foreach($lt as $k=>$v)
    if($k == $node->type && $v != 0) {
      $current_domain = _og_domain_get_base_url_domain();
      return $current_domain;
    }
  return NULL;
}