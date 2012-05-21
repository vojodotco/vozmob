<?php

function jwemfield_emfield_widget_settings_extra($op, $widget) {
  switch ($op) {
    case 'form':
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
    case 'save':
      return array('default_player');
  }
}

function jwemfield_emfield_widget_extra($form, $form_state, $field, $items, $delta = 0, $module) {
  $file = $items[$delta];
  $element = array();
  $default_player = $field["widget"]["default_player"];
  if ($file['default_player'] != null) {
    $default_player = $file['default_player'];
  }
  $element['default_player'] = array(
    '#type' => 'select',
    '#title' => t('Custom Player'),
    '#default_value' => $default_player,
    '#description' => t("Select the Custom Player you would like to use to display your media file."),
    '#options' => LongTailFramework::getConfigs()
  );
  return $element;
}

function jwemfield_emfield_field_columns_extra() {
  $columns = array(
    'default_player' => array('description' => "The JW Player config to use for embedding.", 'type' => 'int', 'unsigned' => 'TRUE', 'sortable' => FALSE, 'not null' => TRUE, 'default' => 0),
  );
  return $columns;
}