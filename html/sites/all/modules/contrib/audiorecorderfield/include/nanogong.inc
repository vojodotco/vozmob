<?php 

/*
 * NanoGong recorder applet
 */
function audiorecorderfield_recorder_nanogong($element, $widget=NULL) {
    
    // The widget is being presented, so apply the JavaScript.
    drupal_add_js(drupal_get_path('module', 'audiorecorderfield') . '/js/audiorecorder_nanogong.js');
    $field_name=audiorecorderfield_str_replace_once('field_', '', $element['#field_name']);
    //Change "_" into "-"
    $field_name=str_replace('_', '-', $field_name);
    
    //TODO: Load options here (width, height,MaxDuration...)
    /*$width = isset($widget['player_width'])?$widget['recorder_width']:300;
    $height = isset($widget['player_height'])? $widget['recorder_height']:100;
    */
    //Nanogong configuration http://gong.ust.hk/nanogong/info_config.html
    $config = '<param name="ShowSaveButton" value="false" />'; //Disable Save button
    $config .= '<param name="ShowTime" value="true" /> '; //Show Time
    $config .= '<param name="ShowSpeedButton" value="false" /> '; //Disable speed button
    $config .= '<param name="MaxDuration" value="1200" /> '; //Set MaxDuration to maximum (20 minutes) 
    $config .= '<param name="AudioFormat" value="ImaADPCM" />'; //Set AudioFormat to Wav
    
    if (!empty($element['#value']['filepath'])) {
        $info = pathinfo($element['#value']['filename']);
        $button_op='Remove';
        //$class_suffix='player';
        $audiofile=file_create_url($element['#value']['filepath']);
        $op=$info['extension'];
        $output = '<div id="nanogong-' . $field_name . '-' . $element['#delta'] . '-wrapper">' . audiofield_get_player($audiofile, $op) . '</div>';
    }
    else {
        $button_op='Upload';
        $class_suffix='recorder';
        $width='113px';
         //Add css
        drupal_add_css(drupal_get_path('module', 'audiorecorderfield') . '/css/audiorecorderfield.css');
        //Nanogong Applet
        $output = '<div class="nanogong-' . $class_suffix . '" id="nanogong-' . $field_name . '-' . $element['#delta'] . '-wrapper"><applet id="nanogong-' . $field_name . '-' . $element['#delta'] . '" archive="' . base_path() . drupal_get_path('module', 'audiorecorderfield') . '/recorders/nanogong.jar" 
            code="gong.NanoGong" width="' . $width . '" height="40">
            ' . $config . '
            ' . $audio_url . '
            </applet></div>';
    }

    //Upload/Remove button
    $output .= '<div><input id="nanogong-button-' . $field_name . '-' . $element['#delta'] . '" type="button" value="' . $button_op . '" onclick="submitVoice(\'' . $field_name . '\',' . $element['#delta'] . ')" /></div>';
    
    return $output;
}

/*
 * Nanogong recorder applet callback. This is what happens when 
 * 'upload' is pressed in the applet
 */
function audiorecorderfield_nanogong_file_receive() {
  header("Cache-control: private");
  header("Content-Type: text/plain");
    
  //$field_id = $_GET['field_id'];
  //$tmp_name = $_FILES['voicefile']['tmp_name'];
  $upload_dir = file_directory_path();
  
  // TODO: get file extension from real file type
  $new_name = file_create_filename(time() . '.wav', $upload_dir);
  //$new_path = $upload_dir . $new_name;
    
  if ($_FILES['voicefile']['error']>0) {
    watchdog('audiorecorder_field', "ERROR - error code: " . $_FILES['voicefile']['error']);
    $fid = "NULL";
  }
  else {
    $_FILES['files'] = $_FILES['voicefile'];
    $_FILES['files']['name'] = $new_name;
    foreach ($_FILES['files'] as $key => $value) {
      $_FILES['files'][$key] = array(0 => $value);
    }

    if (!$file = file_save_upload(0, NULL, $upload_dir)) {
      watchdog('audiorecorder_field', "ERROR - file_save_upload failed");
      $fid = "NULL";
    } 
    else {
      $fid = $file->fid;
    }
  }
  //Return fid to javascript
  print("$fid"); 
}

function audiorecorderfield_nanogong_player($player_path, $audio_file, $id="nanogong") {
    //Add css
    drupal_add_css(drupal_get_path('module', 'audiorecorderfield') . '/css/audiorecorderfield.css');
    $config = '<param name="ShowSaveButton" value="false" />'; //Disable Save button
    $config .= '<param name="ShowTime" value="true" /> '; //Show Time
    $config .= '<param name="ShowRecordButton" value="false" /> '; //Disable Record button
    $config .= '<param name="ShowSpeedButton" value="false" /> '; //Disable speed button
    $output='<div class="nanogong-player" id="' . $id . '-wrapper"><applet id="' . $id . '" archive="' . $player_path . '" code="gong.NanoGong" width="82" height="40">  
            ' . $config . '<param name="SoundFileURL" value="' . $audio_file . '"/> </applet></div>';

    return $output;
}