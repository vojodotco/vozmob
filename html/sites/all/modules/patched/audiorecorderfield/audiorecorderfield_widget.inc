<?php
// $Id:

/**
 * @file
 * audiorecorderfield widget hooks and callbacks.
 */

/**
 * Implementation of CCK's hook_widget_settings($op = 'form').
 */
function audiorecorderfield_widget_settings_form($widget) {
  $form = module_invoke('filefield', 'widget_settings', 'form', $widget);

  $form['file_extensions'] = array(
    '#type' => 'textfield',
    '#title' => t('Permitted upload file extensions'),
    '#default_value' => is_string($widget['file_extensions']) ? $widget['file_extensions'] :'mp3 wav',
    '#size' => 64,
    '#description' => t('Extensions a user can upload to this field. Separate extensions with a space and do not include the leading dot. Leaving this blank will allow users to upload a file with any extension.'),
    '#weight' => 1,
  );
  
  return $form;
}

/**
 * Implementation of CCK's hook_widget_settings($op = 'save').
 */
function audiorecorderfield_widget_settings_save($widget) {
  $filefield_settings = module_invoke('filefield', 'widget_settings', 'save', $widget);
  return $filefield_settings;
}

/**
 * Element #value_callback function.
 */
function audiorecorderfield_widget_value($element, $edit = FALSE) {
  $field = filefield_widget_value($element, $edit);
  
  return $field;
}

/**
 * FormAPI theme function. Theme the output of an image field.
 */
function theme_audiorecorderfield_widget($element) {
  
  $z=theme('form_element', $element, $element['#children']);
  
  return $z;
}

/**
 * Process an individual element.
 *
 * Build the form element. When creating a form using FAPI #process,
 * note that $element['#value'] is already set.
 *
 * The $fields array is in $form['#field_info'][$element['#field_name']].
 */
function audiorecorderfield_widget_process($element, $edit, $form_state, $form) {
  $field = $form['#field_info'][$element['#field_name']];
  $field_key = $element['#columns'][0];
  $fid=$element['#value'][$field_key];  
  $field_name=audiorecorderfield_str_replace_once('field_', '', $element['#field_name']);

  //Change "_" into "-"
  $field_name=str_replace('_', '-', $field_name);
  $recorder = audiorecorderfield_get_recorder();
  $element['applet'] = array(
    '#required' => $element['#required'],
    '#value' => "<div id='audiorecorderfield-".$field_name."-".$element['#delta']."-wrapper'>".$recorder['callback']($element, $field['widget'])."</div>"
  );
     
  // this would be the hidden field the applet would insert the newly uploaded file fid to.
  $element[$field_key] = array(
    '#type' => 'hidden',
    '#title' => t($field['widget']['label']),
    '#required' => $element['#required'],
    '#default_value' => isset($fid) ? $fid : "",
  );

  return $element;
}