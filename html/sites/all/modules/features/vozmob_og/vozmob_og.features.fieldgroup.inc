<?php

/**
 * Implementation of hook_fieldgroup_default_groups().
 */
function vozmob_og_fieldgroup_default_groups() {
  $groups = array();

  // Exported group: group_voipnode_settings
  $groups['group-group_voipnode_settings'] = array(
    'group_type' => 'standard',
    'type_name' => 'group',
    'group_name' => 'group_voipnode_settings',
    'label' => 'Custom Phone Audio',
    'settings' => array(
      'form' => array(
        'style' => 'fieldset_collapsible',
        'description' => '',
      ),
      'display' => array(
        'description' => '',
        'teaser' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'full' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '4' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '2' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '3' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        '5' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'token' => array(
          'format' => 'fieldset',
          'exclude' => 0,
        ),
        'label' => 'above',
      ),
    ),
    'weight' => '10',
    'fields' => array(
      '0' => 'field_voipnode_adesc',
      '1' => 'field_voipnode_agreet',
      '2' => 'field_voipnode_aname',
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Custom Phone Audio');

  return $groups;
}
