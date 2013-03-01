<?php
// $Id$

/**
 * @file
 * A FileField extension to allow uploading audio files by using audio recorder
 */

/**
 * Implementation of hook_filefield_source_info().
 */
function filefield_source_recorder_info() {
  $source['recorder'] = array(
    'name' => t('Audio Recorder'),
    'label' => t('Audio Recorder'),
    'description' => t('Record audio using default recorder.'),
    'process' => 'filefield_source_recorder_process',
    'weight' => 3,
  );
  return $source;
}

/**
 * Implementation of hook_theme().
 */
function filefield_source_recorder_theme() {
  return array(
    'filefield_source_recorder_element' => array(
      'arguments' => array('element' => NULL),
      'file' => 'sources/recorder.inc',
    ),
  );
}

/**
 * A #process callback to extend the filefield_widget element type.
 */
function filefield_source_recorder_process($element, $edit, &$form_state, $form) {
  $field = content_fields($element['#field_name'], $element['#type_name']);
 
  $field_name=audiorecorderfield_str_replace_once('field_', '', $element['#field_name']);
  //Change "_" into "-"
  $field_name=str_replace('_', '-', $field_name);
  $element['filefield_recorder'] = array(
    '#theme' => 'filefield_source_recorder_element',
    '#weight' => 100.5,
    '#access' => empty($element['fid']['#value']),
  );

  $description = t('Record audio using default audio recorder.');

  $validators = $element['#upload_validators'];
  if (isset($validators['filefield_validate_size'])) {
      unset($validators['filefield_validate_size']);
  }
  
  if($edit['fid']){
    unset($element['#value']['filepath']);
  }
  $recorder = audiorecorderfield_get_recorder();  
  $element['filefield_recorder']['#description'] = $description;
  $element['filefield_recorder']['rec'] = array(
    '#value' => "<div id='audiorecorderfield-".$field_name."-".$element['#delta']."-wrapper'>".$recorder['callback']($element, $field['widget'])."</div>"
  );

  return $element;
}

/**
 * Theme the output of the audio recorder field.
 */
function theme_filefield_source_recorder_element($element) {
  $output .= $element['rec']['#value'];
  $element['#type'] = 'item';
  return '<div class="filefield-source filefield-source-recorder clear-block">' . theme('form_element', $element, $output) . '</div>';
}