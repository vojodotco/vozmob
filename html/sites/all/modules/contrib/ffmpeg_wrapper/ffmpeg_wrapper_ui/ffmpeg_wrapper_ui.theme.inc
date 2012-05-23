<?php

// $Id$

/**
 * @file
 * Provides theming
 */


/**
 * Themes the list of radio buttons and other form data
 * @param $form
 *   drupal form
 * @return unknown_type
 */
function theme_ffmpeg_wrapper_ui_files_radios(&$form) {
  $rows = array();
  $header = array(t('File Name'), t('Use'), t('Attach'), t('Mime type'), t('Size'));
  // select each of the options from the $files form and build from the #options
  foreach (element_children($form['data']) as $key) {
    $row = array();
    // name of the file
    $row[] = drupal_render($form[$key]['name']);
    // render the radio
    unset($form['data'][$key]['#title']);
    $row[] = drupal_render($form['data'][$key]);
    // create the attach files radio, remove the title
    unset($form['attach_files'][$key]['#title']);
    $row[] = drupal_render($form['attach_files'][$key]);
    $row[] = drupal_render($form[$key]['mime']);
    $row[] = drupal_render($form[$key]['size']);
    $rows[] = $row;
  }
  $output = theme('table', $header, $rows);
  $output .= drupal_render($form);
  return $output;
}


/**
 * Theme file data for the passed in file
 * @param $filepath
 * @return string
 */
function theme_ffmpeg_wrapper_ui_file_data($filepath) {
  // Get the ffmpeg file data
  $file_data = ffmpeg_wrapper_get_file_data($filepath);

  $meta = array(
    t('File: !file', array('!file' => check_plain(basename($filepath)))),
    t('Format: !format', array('!format' => $file_data['format'])),
    t('Duration: !duration (seconds)', array('!duration' => $file_data['duration'])),
    t('Total bitrate: !rate', array('!rate' => $file_data['bitrate'])),
  );

  $video = array(
    t('Video codec: !codec', array('!codec' => $file_data['video']['codec'])),
    t('Frame size: !s', array('!s' => $file_data['video']['s'])),
    t('Bit rate: !br', array('!br' => $file_data['video']['br'])),
    NULL,
  );

  $audio = array(
    t('Audio codec: !codec', array('!codec' => $file_data['audio']['codec'])),
    t('Sample rate: !ar', array('!ar' => $file_data['audio']['ar'])),
    t('Bit rate: !br', array('!br' => $file_data['audio']['ab'])),
    t('Chanels: !ac', array('!ac' => $file_data['audio']['ac'])),
  );

  // build the rows for the display
  $rows = array($meta, $video, $audio);
  return theme('table', array(), $rows);
}