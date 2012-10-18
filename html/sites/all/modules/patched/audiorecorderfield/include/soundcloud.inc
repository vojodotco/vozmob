<?php

/*
 * Soundcloud flash recorder
 */
function audiorecorderfield_recorder_soundcloud($element, $widget) {
  return theme('audiorecorderfield_soundcloud', $element); 
}

function theme_audiorecorderfield_soundcloud($element) {
  // The widget is being presented, so apply the JavaScript.
    $field_name=audiorecorderfield_str_replace_once('field_', '', $element['#field_name']);
    //Change "_" into "-"
    $field_name=str_replace('_', '-', $field_name);
    $op = NULL;
    drupal_add_css(drupal_get_path('module', 'audiorecorderfield') . '/css/audiorecorderfield.css');
    drupal_add_js(array('soundcloud_recorder' => array(base_path().drupal_get_path('module', 'audiorecorderfield').'/recorders/recorder.swf')), 'setting');
    drupal_add_js(drupal_get_path('module', 'audiorecorderfield') . '/js/recorder.js');   
    drupal_add_js(drupal_get_path('module', 'audiorecorderfield') . '/js/audiorecorder_soundcloud.js');   
    if (!empty($element['#value']['filepath'])) {
        $info = pathinfo($element['#value']['filename']);
        $button_op='Remove';
        $audiofile=file_create_url($element['#value']['filepath']);
        $op = $info['extension'];
        $output = '<div id="soundcloud-wrapper">' . audiofield_get_player($audiofile, $op) . '</div>';
        //watchdog('audiorecorderfield','File detected '.print_r($element,true));
    }
    else {
        $button_op='Upload';
        
        
        $output = theme('audiorecorderfield_soundcloud_skin', $field_name, $element['#delta']);
    }
    $output.='<div><input type="button" onclick="javascript:upload(\'' . $field_name . '\',\'' . $element['#delta'] . '\')"  
        id="soundcloud-button-' . $field_name . '-' . $element['#delta'] . '" value="'.$button_op.'"/></div>';
    return $output;
}

/*Skin for Soundcloud Flash recorder. Override to implement different skin*/
function theme_audiorecorderfield_soundcloud_skin($field_name, $delta) {
  //Add css
  drupal_add_css(drupal_get_path('module', 'audiorecorderfield') . '/css/audiorecorderfield.css');
  $output = '<div id="soundcloud-' . $field_name . '-' . $delta . '-wrapper">
        <div>
          <span onclick="record(\'' . $field_name . '\',\'' . $delta . '\')"  class="soundcloud-record">Record</span>
          <span onclick="stop(\'' . $field_name . '\',\'' . $delta . '\')"    class="soundcloud-stop" style="display:none;">Stop</span>
          <span onclick="play(\'' . $field_name . '\',\'' . $delta . '\')" style="display:none;"   class="soundcloud-play">Play</span>
          <span onclick="pause(\'' . $field_name . '\',\'' . $delta . '\')" style="display:none;"   class="soundcloud-pause">Pause</span>
        </div>
        <span id="time-' . $field_name . '-' . $delta . '">0:00</span>
        <a class="record-again-btn" style="display:none;" href="javascript:record_again(\'' . $field_name . '\',\'' . $delta . '\')">Start over</a>
        </div>
        ';
  return $output;      
}

/*
 * Soundcloud recorder callback. This is what happens when 
 * 'upload' is pressed in the flash.
 */
function audiorecorderfield_soundcloud_file_receive() {
  $upload_dir = file_directory_path();
  // TODO: get file extension from real file type
  $new_name = file_create_filename(time() . '.wav', $upload_dir);
  $_FILES['files'] = $_FILES['track'];
  $_FILES['files']['name'] = $new_name;

  foreach ($_FILES['files'] as $key => $value) {
      if ($key == 'tmp_name') {
        $_FILES['files'][$key] = array(0 => $value['asset_data']);
      }
      else if($key !='error') {
        $_FILES['files'][$key] = array(0 => $value);
      }
  }
    $res = is_uploaded_file($_FILES['files']['tmp_name'][0]);  
    if (!$file = file_save_upload(0, NULL, $upload_dir)) {
      watchdog('audiofield_soundcloud', "ERROR - file_save_upload failed");
      $fid = "NULL";
    } 
    else {
      $fid = $file->fid;
    }
  
  //Return fid to javascript
  print("$fid"); 
}