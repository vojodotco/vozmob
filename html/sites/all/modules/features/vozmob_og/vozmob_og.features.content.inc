<?php

/**
 * Implementation of hook_content_default_fields().
 */
function vozmob_og_content_default_fields() {
  $fields = array();

  // Exported field: field_blog_promote
  $fields['blog-field_blog_promote'] = array(
    'field_name' => 'field_blog_promote',
    'type_name' => 'blog',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'text',
    'required' => '0',
    'multiple' => '0',
    'module' => 'text',
    'active' => '1',
    'text_processing' => '0',
    'max_length' => '',
    'allowed_values' => '0|Uncheck box to remove story to front page and featured stories
1|Yes, feature this story!',
    'allowed_values_php' => '',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => 0,
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Promote story',
      'weight' => '8',
      'description' => '',
      'type' => 'optionwidgets_onoff',
      'module' => 'optionwidgets',
    ),
  );

  // Exported field: field_group_logo
  $fields['group-field_group_logo'] = array(
    'field_name' => 'field_group_logo',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '-4',
      'parent' => '',
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'group_logo_small_linked',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'group_logo_large_default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'image_plain',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'png gif jpg jpeg',
      'file_path' => '',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'max_resolution' => '0',
      'min_resolution' => '0',
      'alt' => '',
      'custom_alt' => 0,
      'title' => '',
      'custom_title' => 0,
      'title_type' => 'textfield',
      'default_image' => NULL,
      'use_default_image' => 0,
      'rotate' => 0,
      'label' => 'Group logo',
      'weight' => '-3',
      'description' => 'Please upload a logo or image for your group! Your image will be resized if over 700px by 200px, so that it fits within the website header. ',
      'type' => 'imagefield_widget',
      'module' => 'imagefield',
    ),
  );

  // Exported field: field_map
  $fields['group-field_map'] = array(
    'field_name' => 'field_map',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '26',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 1,
      ),
      'full' => array(
        'format' => 'openlayers_map_default',
        'exclude' => 1,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'openlayers_wkt',
    'required' => '0',
    'multiple' => '0',
    'module' => 'openlayers_cck',
    'active' => '1',
    'openlayers_cck_feature_types' => array(
      'point' => 'point',
      'path' => 0,
      'polygon' => 0,
    ),
    'widget' => array(
      'openlayers_cck_preset_map' => 'vojo_default',
      'openlayers_behaviors' => array(
        'openlayers_behavior_zoomtolayer' => array(
          'enabled' => 0,
          'options' => array(
            'zoomtolayer' => 'openlayers_cck_vector_layer',
            'point_zoom_level' => '5',
          ),
        ),
      ),
      'keep_points' => 0,
      'position' => '10',
      'default_value' => array(
        '0' => array(
          'openlayers_wkt' => '',
        ),
      ),
      'default_value_php' => NULL,
      'autocompletion_field_location_string_enable' => 0,
      'autocompletion_field_location_string_override' => 0,
      'autocompletion_field_location_string_content' => '',
      'autocompletion_field_location_string_type' => 'input',
      'autocompletion_field_gps_gpslongituderef_enable' => 0,
      'autocompletion_field_gps_gpslongituderef_override' => 0,
      'autocompletion_field_gps_gpslongituderef_content' => '',
      'autocompletion_field_gps_gpslongituderef_type' => 'input',
      'autocompletion_field_gps_gpslatituderef_enable' => 0,
      'autocompletion_field_gps_gpslatituderef_override' => 0,
      'autocompletion_field_gps_gpslatituderef_content' => '',
      'autocompletion_field_gps_gpslatituderef_type' => 'input',
      'autocompletion_field_group_type_enable' => 0,
      'autocompletion_field_group_type_override' => 0,
      'autocompletion_field_group_type_content' => '',
      'autocompletion_field_group_type_type' => 'select',
      'label' => 'Map',
      'weight' => '-1',
      'description' => 'Type in an address to tell us where this group is located.  This will be helpful for showing other stories on the group map.',
      'type' => 'openlayers_geocoder_widget',
      'module' => 'openlayers_geocoder',
    ),
  );

  // Exported field: field_voipnode_adesc
  $fields['group-field_voipnode_adesc'] = array(
    'field_name' => 'field_voipnode_adesc',
    'type_name' => 'group',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '1',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'amr mp3 qcp wav',
      'file_path' => 'group_audio',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'filefield_sources' => array(
        'recorder' => 'recorder',
        'remote' => 0,
        'reference' => 0,
        'attach' => 0,
      ),
      'filefield_source_attach_path' => 'file_attach',
      'filefield_source_attach_absolute' => '0',
      'filefield_source_attach_mode' => 'move',
      'filefield_source_autocomplete' => '0',
      'label' => '"More Info" Audio for Phone Calls',
      'weight' => 0,
      'description' => 'When people call your group over the phone, they have an option to hear more about the group.  This is the audio that will be played there.  If you don\'t have a recording here, then people will hear the "About this Group" text read aloud in a robot voice.',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_voipnode_agreet
  $fields['group-field_voipnode_agreet'] = array(
    'field_name' => 'field_voipnode_agreet',
    'type_name' => 'group',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'amr mp3 qcp wav',
      'file_path' => 'group_audio',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'filefield_sources' => array(
        'recorder' => 'recorder',
        'remote' => 0,
        'reference' => 0,
        'attach' => 0,
      ),
      'filefield_source_attach_path' => 'file_attach',
      'filefield_source_attach_absolute' => '0',
      'filefield_source_attach_mode' => 'move',
      'filefield_source_autocomplete' => '0',
      'label' => '"Menu" Audio for Phone Calls',
      'weight' => 0,
      'description' => 'When people call your group over the phone, they hear a menu of options.  You can record that menu in your own voice.  You should be sure to include "Press 2 to record your own story, or press 3 to hear more about the group".',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_voipnode_aname
  $fields['group-field_voipnode_aname'] = array(
    'field_name' => 'field_voipnode_aname',
    'type_name' => 'group',
    'display_settings' => array(
      'label' => array(
        'format' => 'above',
        'exclude' => 0,
      ),
      'teaser' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'audiofield_embedded',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'filefield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'filefield',
    'active' => '1',
    'list_field' => '0',
    'list_default' => 1,
    'description_field' => '0',
    'widget' => array(
      'file_extensions' => 'amr mp3 qcp wav',
      'file_path' => 'group_audio',
      'progress_indicator' => 'bar',
      'max_filesize_per_file' => '',
      'max_filesize_per_node' => '',
      'filefield_sources' => array(
        'recorder' => 'recorder',
        'remote' => 0,
        'reference' => 0,
        'attach' => 0,
      ),
      'filefield_source_attach_path' => 'file_attach',
      'filefield_source_attach_absolute' => '0',
      'filefield_source_attach_mode' => 'move',
      'filefield_source_autocomplete' => '0',
      'label' => '"Name" Audio for Phone Calls',
      'weight' => 0,
      'description' => 'When people call your group over the phone, this will be the first thing they hear (once they transfer to your group).  If you don\'t have a recording here, then people will hear your group\'s name read in a robot voice.',
      'type' => 'filefield_widget',
      'module' => 'filefield',
    ),
  );

  // Exported field: field_yeta
  $fields['group-field_yeta'] = array(
    'field_name' => 'field_yeta',
    'type_name' => 'group',
    'display_settings' => array(
      'weight' => '14',
      'parent' => '',
      'label' => array(
        'format' => 'above',
      ),
      'teaser' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '2' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '3' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      '5' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'token' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'mail2og_emailfield',
    'required' => '0',
    'multiple' => '0',
    'module' => 'mail2og',
    'active' => '1',
    'mail2og_emailfield_process' => '',
    'widget' => array(
      'size' => NULL,
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_yeta][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'E-mail address',
      'weight' => '10',
      'description' => '',
      'type' => 'mail2og_emailfield',
      'module' => 'mail2og',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('"Menu" Audio for Phone Calls');
  t('"More Info" Audio for Phone Calls');
  t('"Name" Audio for Phone Calls');
  t('E-mail address');
  t('Group logo');
  t('Map');

  return $fields;
}
