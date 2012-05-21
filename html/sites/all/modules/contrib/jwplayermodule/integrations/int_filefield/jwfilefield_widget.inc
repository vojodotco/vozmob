<?php

/**
 * Implementation of CCK's hook_widget_settings($op = 'form').
 * @param $widget
 * @return mixed
 */
function jwfilefield_widget_settings_form($widget) {
  $form = module_invoke('filefield', 'widget_settings', 'form', $widget);
  if ($form['file_extensions']['#default_value'] == 'txt') {
    $form['file_extensions']['#default_value'] = 'mp4 mpeg avi mpg wmv flv mov';
  }
  $default = jwfilefield_default_widget_settings($widget);
  $form = $form + $default;
  return $form;
}

function jwfilefield_default_widget_settings($widget) {
  $form = array();
  $form['plugins'] = array(
    '#type' => 'fieldset',
    '#title' => t('JW Player Settings'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#weight' => 10
  );
  $form['plugins']['default_player'] = array(
    '#type' => 'select',
    '#title' => t('Default Custom Player'),
    '#default_value' => !empty($widget['default_player']) ? $widget['default_player'] : '',
    '#options' => LongTailFramework::getConfigs(),
    '#description' => t('Choose the default player to display your uploaded video.')
  );
  return $form;
}

/**
 * Implementation of CCK's hook_widget_settings($op = 'save').
 * @param $widget
 * @return array
 */
function jwfilefield_widget_settings_save($widget) {
  $filefield_settings = module_invoke('filefield', 'widget_settings', 'save', $widget);
  return array_merge($filefield_settings, array('default_player'));
}

function jwfilefield_widget_process($element, $edit, &$form_state, $form) {
  $item = $element['#value'];
  $element['#theme'] = 'jwfilefield_widget_item';
  if (!empty($item['fid'])) {
    jwfilefield_widget_element_settings($element);
  }
  return $element;
}

function jwfilefield_widget_value($element, $edit = FALSE) {
  if (!$edit) {
    // Creating so we load up our empty values.
    $file = field_file_load($element['#default_value']['fid']);
    $item = $element['#default_value'];
  }
  else {
    // Reset our item array for our data.
    $item = array_merge($element['#default_value'], $edit);
    if (isset($element['#default_value']['data']) && isset($edit['data'])) {
      $item['data'] = array_merge($element['#default_value']['data'], $edit['data']);
    }
    $field = content_fields($element['#field_name'], $element['#type_name']);

    // Uploads take priority over value of fid text field.
    if ($fid = filefield_save_upload($element)) {
      $item['fid'] = $fid;
      $item['data'] = $element['#default_value']['data'];
    }
    // Check for #filefield_value_callback values.
    // Because FAPI does not allow multiple #value_callback values like it does
    // for #element_validate and #process, this fills the missing functionality
    // to allow FileField to be extended purely through FAPI.
    elseif (isset($element['#filefield_value_callback'])) {
      foreach ($element['#filefield_value_callback'] as $callback) {
        $callback($element, $item);
      }
    }

    // Load file if the FID has changed so that it can be saved by CCK.
    $file = isset($item['fid']) ? field_file_load($item['fid']) : NULL;

    // If the file entry doesn't exist, don't save anything.
    if (empty($file)) {
      $item = array();
      $file = array();
    }

    // Checkboxes loose their value when empty.
    // If the list field is present make sure its unchecked value is saved.
    if (!empty($field['list_field']) && empty($edit['list'])) {
      $item['list'] = 0;
    }
  }
  // Merge file and item data so it is available to all widgets.
  if (isset($item['data']) && isset($file['data'])) {
    $file['data'] = array_merge($item['data'], $file['data']);
  }
  $item = array_merge($item, $file);

  return $item;
}

function jwfilefield_widget_element_settings(&$element) {
  $delta = $element["#delta"];
  if ($delta > 0) return;
  $file = $element['#value'];
  $field = content_fields($element['#field_name'], $element['#type_name']);
  $default_player = $field['widget']['default_player'];
  if ($file['data']['default_player'] != null) {
    $default_player = $file['data']['default_player'];
  }
  $element['data']['default_player'] = array(
    '#type' => 'select',
    '#title' => t('Custom Player'),
    '#default_value' => $default_player,
    '#description' => t("Select the Custom Player you would like to use to display your media file."),
    '#options' => LongTailFramework::getConfigs()
  );
}