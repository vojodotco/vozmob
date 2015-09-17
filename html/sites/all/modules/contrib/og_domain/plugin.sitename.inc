<?php


/**
 * Implementation of hook_override_form_add().
 *
 * @param int $nid
 * @return array
 */
function sitename_override_form_add($nid) {
  $overrides = _og_domain_get_overrides($nid);
  return array(
    'sitename_override' => array(
      '#title' => t('Use default sitename'),
      '#type' => 'checkbox',
      '#value' => 1,
      '#default_value' => variable_get('og_domain_sitename_default_override', 0),
    ),
    'sitename_override_custom' => array(
      '#title' => t('Custom sitename'),
      '#type' => 'textfield',
      '#default_value' => isset($overrides['site_name']) ? $overrides['site_name'] : '',
    ),
  );
}

/**
 * Implementation of hook_override_form_validate().
 *
 * @param array $form_state
 */
function sitename_override_form_validate($form_state) {

}

/**
 * Implementation of hook_override_form_submit().
 *
 * @param array $form_state
 */
function sitename_override_form_submit($form_state) {
  $overrides = _og_domain_get_overrides($form_state['values']['nid']);
  if($form_state['values']['sitename_override']) {
    $overrides['site_name'] = $form_state['values']['title'];
  } else if(trim($form_state['values']['sitename_override_custom']) != '') {
    $overrides['site_name'] = $form_state['values']['sitename_override_custom'];
  }
  _og_domain_set_overrides($form_state['values']['nid'], $overrides);
}