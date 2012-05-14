<?php

/**
 * @file
 *  Views include file with hooks.
 */

/**
 * Implementation of hook_views_plugin.
 */
function voipviews_views_plugins() {
  $path = drupal_get_path('module', 'voipviews');
  return array(
    'module' => 'voipviews',
    'display' => array(
      'voipviews' => array(
        'title' => t('VoIP'),
        'help' => t('View output for VoIP call.'),
        'handler' => 'voipviews_views_plugin_display',
        'path' => $path . '/views',
        'uses hook menu' => FALSE,
        'uses voipextension' => TRUE,
        'use ajax' => FALSE,
        'use pager' => FALSE,
        'accept attachments' => FALSE,
        'admin' => t('VoIP'),
      ),
    ),
    'style' => array(
      'voipviews_list' => array(
        'title' => t('VoIP rows'),
        'help' => t('Rows in a VoIP script.'),
        'handler' => 'voipviews_views_plugin_style',
        'path' => $path .'/views',
        'theme' => 'voipviews_views',
        'theme path' => $path .'/theme',
        'theme file' => 'voipviews.theme.inc',
        'uses fields' => TRUE,
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'type' => 'voipviews',
        'even empty' => TRUE,
      ),
/*      'voipviews_menu' => array(
        'title' => t('IVR menu'),
        'help' => t('Provides simple readout of the field rows.'),
        'handler' => 'voipviews_views_plugin_style_ivr', // 'voipviews_views_style',
        'path' => $path .'/views',
        'theme' => 'voipviews_views',
        'theme path' => $path .'/views',
        'theme file' => 'voipviews.theme.inc',
        'uses fields' => TRUE,
        'uses row plugin' => TRUE,
        'uses options' => TRUE,
        'uses grouping' => TRUE,
        'type' => 'voipviews',
        'even empty' => TRUE,
      ),*/
    ),
    'row' => array(
      'voipviews_row' => array(
        'title' => t('Standard VoIP script'),
        'help' => t('Sequential script of the rows.'),
        'handler' => 'voipviews_views_plugin_row',
        'path' => $path .'/views',
        'theme' => 'voipviews_views_row',
        'theme path' => $path . '/theme',
        'theme file' => 'voipviews.theme.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'voipviews',
      ),
      'voipviews_row_ivr' => array(
        'title' => t('VoIP script with IVR'),
        'help' => t('Menu script of the rows.'),
        'handler' => 'voipviews_views_plugin_row_ivr',
        'path' => $path .'/views',
        'theme' => 'voipviews_views_row',
        'theme path' => $path . '/theme',
        'theme file' => 'voipviews.theme.inc',
        'uses fields' => TRUE,
        'uses options' => TRUE,
        'type' => 'voipviews',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_handlers().
 */
function voipviews_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'voipviews') . '/views',
    ),
    'handlers' => array(
      'voipviews_handler_field_sms_text' => array(
        'parent' => 'views_handler_field',
      ),
      'voipviews_handler_field_gosub' => array(
        'parent' => 'views_handler_field',
      ),
      'voipviews_handler_field_ivr' => array(
        'parent' => 'views_handler_field',
      ),
      'voipviews_handler_field_ivr_goto_begin' => array(
        'parent' => 'voipviews_handler_field_ivr',
      ),
      'voipviews_handler_field_ivr_goto_menu' => array(
        'parent' => 'voipviews_handler_field_ivr',
      ),
      'voipviews_handler_field_ivr_return' => array(
        'parent' => 'voipviews_handler_field_ivr',
      ),
      'voipviews_handler_field_ivr_next_row' => array(
        'parent' => 'voipviews_handler_field_ivr',
      ),
      'voipviews_handler_field_ivr_previous_row' => array(
        'parent' => 'voipviews_handler_field_ivr',
      ),
      'voipviews_handler_field_file_url' => array(
        'parent' => 'views_handler_field_file',
      ),
    ),
  );
}

/**
 * Implementation of hook_views_data().
 */
function voipviews_views_data() {
  $data['voipviews']['table']['group'] = t('VoIP');
  $data['voipviews']['table']['join'] = array(
    '#global' => array(),
  );

  $data['voipviews']['sms_text'] = array(
    'title' => t('SMS text'),
    'help' => t('Custom text field, with token replacement, that will be sent by sms.'),
    'field' => array(
      'handler' => 'voipviews_handler_field_sms_text',
    ),
  );
  $data['voipviews']['gosub'] = array(
    'title' => t('Gosub'),
    'help' => t('Call a voipscript subroutine.'),
    'field' => array(
      'handler' => 'voipviews_handler_field_gosub',
    ),
  );
  $data['voipviews']['ivr_goto_begin'] = array(
    'title' => t('IVR: Goto beginning'),
    'help' => t('Return to the begining of the view row.'),
    'field' => array(
      'handler' => 'voipviews_handler_field_ivr_goto_begin',
    ),
  );
  $data['voipviews']['ivr_goto_menu'] = array(
    'title' => t('IVR: Goto menu'),
    'help' => t('Return to the ivr menu.'),
    'field' => array(
      'handler' => 'voipviews_handler_field_ivr_goto_menu',
    ),
  );
  $data['voipviews']['ivr_return'] = array(
    'title' => t('IVR: Return'),
    'help' => t('Return to the previous voip script.'),
    'field' => array(
      'handler' => 'voipviews_handler_field_ivr_return',
    ),
  );
  $data['voipviews']['ivr_next_row'] = array(
    'title' => t('IVR: Goto next'),
    'help' => t('Goto the next view row.'),
    'field' => array(
      'handler' => 'voipviews_handler_field_ivr_next_row',
    ),
  );
  $data['voipviews']['ivr_previous_row'] = array(
    'title' => t('IVR: Goto previous'),
    'help' => t('Goto the previous view row.'),
    'field' => array(
      'handler' => 'voipviews_handler_field_ivr_previous_row',
    ),
  );
  return $data;
}

/**
 * Implementation of hook_views_data_alter().
 */
function voipviews_views_data_alter(&$data) {
  $data['files']['fileurl'] = array(
    'title' => t('URL'),
    'help' => t('Plain text absolute url to the file'),
    'field' => array(
      'field' => 'filepath',
      'handler' => 'voipviews_handler_field_file_url',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
    'argument' => array(
      'handler' => 'views_handler_argument_string',
    ),
  );
}

