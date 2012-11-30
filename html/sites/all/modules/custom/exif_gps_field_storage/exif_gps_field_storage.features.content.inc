<?php

/**
 * Implementation of hook_content_default_fields().
 */
function exif_gps_field_storage_content_default_fields() {
  $fields = array();

  // Exported field: field_gps_gpslatitude
  $fields['blog-field_gps_gpslatitude'] = array(
    'field_name' => 'field_gps_gpslatitude',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => '14',
      'parent' => '',
      'token' => array(
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_decimal',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '-90',
    'max' => '90',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'precision' => '12',
    'scale' => '10',
    'decimal' => '.',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_gps_gpslatitude][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Latitude',
      'weight' => '14',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_gps_gpslatituderef
  $fields['blog-field_gps_gpslatituderef'] = array(
    'field_name' => 'field_gps_gpslatituderef',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => '19',
      'parent' => '',
      'token' => array(
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
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
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_gps_gpslatituderef][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Latitude ref',
      'weight' => '19',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_gps_gpslongitude
  $fields['blog-field_gps_gpslongitude'] = array(
    'field_name' => 'field_gps_gpslongitude',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => '13',
      'parent' => '',
      'token' => array(
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
    ),
    'widget_active' => '1',
    'type' => 'number_decimal',
    'required' => '0',
    'multiple' => '0',
    'module' => 'number',
    'active' => '1',
    'prefix' => '',
    'suffix' => '',
    'min' => '-180',
    'max' => '180',
    'allowed_values' => '',
    'allowed_values_php' => '',
    'precision' => '13',
    'scale' => '10',
    'decimal' => '.',
    'widget' => array(
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_gps_gpslongitude][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Longitude',
      'weight' => '13',
      'description' => '',
      'type' => 'number',
      'module' => 'number',
    ),
  );

  // Exported field: field_gps_gpslongituderef
  $fields['blog-field_gps_gpslongituderef'] = array(
    'field_name' => 'field_gps_gpslongituderef',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => '17',
      'parent' => '',
      'token' => array(
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
      'label' => array(
        'format' => 'hidden',
      ),
      'teaser' => array(
        'format' => 'hidden',
        'exclude' => 0,
      ),
      'full' => array(
        'format' => 'hidden',
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
    'allowed_values' => '',
    'allowed_values_php' => '',
    'widget' => array(
      'rows' => 5,
      'size' => '60',
      'default_value' => array(
        '0' => array(
          'value' => '',
          '_error_element' => 'default_value_widget][field_gps_gpslongituderef][0][value',
        ),
      ),
      'default_value_php' => NULL,
      'label' => 'Longitude ref',
      'weight' => '17',
      'description' => '',
      'type' => 'text_textfield',
      'module' => 'text',
    ),
  );

  // Exported field: field_map
  $fields['blog-field_map'] = array(
    'field_name' => 'field_map',
    'type_name' => 'blog',
    'display_settings' => array(
      'weight' => '6',
      'parent' => '',
      'token' => array(
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
      '4' => array(
        'format' => 'default',
        'exclude' => 0,
      ),
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
      '5' => array(
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
      'label' => 'Map',
      'weight' => '6',
      'description' => 'Type in an address to tell us where this story took place.  Your story will then show up on the group map.',
      'type' => 'openlayers_geocoder_widget',
      'module' => 'openlayers_geocoder',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Latitude');
  t('Latitude ref');
  t('Longitude');
  t('Longitude ref');
  t('Map');

  return $fields;
}
