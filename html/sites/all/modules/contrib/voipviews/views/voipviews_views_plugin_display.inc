<?php

/**
 * @file
 *  VoIP display plugin
 */
class voipviews_views_plugin_display extends views_plugin_display {
  function defaultable_sections($section = NULL) {
    $sections = parent::defaultable_sections($section);
    return $sections;
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['voipextension_enable'] = array('default' => 0);
    $options['voipextension_directory_type'] = array('default' => 1);
    $options['voipextension_title'] = array('default' => '', 'translatable' => TRUE);
    $options['voipextension_description'] = array('default' => '', 'translatable' => TRUE);

    return $options;
  }

  function options_summary(&$categories, &$options) {
    parent::options_summary($categories, $options);

    // unset options from general form that make no sense.
    unset($options['exposed_block']);
    unset($options['analyze-theme']);
    unset($options['css_class']);

    // As we don't deal with different filter formats, set format text to None/Text.
    foreach (array('header' => t('Header'), 'footer' => t('Footer'), 'empty' => t('Empty text')) as $type => $name) {
      if ($this->get_option($type)) {
        $options[$type]['value'] = t('Text');
      }
    }


    // Add VoIP specific fields
    $categories['voip'] = array(
      'title' => t('VoIP settings'),
    );

    if ($this->get_option('voipextension_enable')) {
      if ($extension = voipextension_load_by_module_id('voipviews', $this->view->name . '|' . $this->display->id)) {
        $extension_eid = $extension['eid'];
      }
      else {
        $extension_eid = t('Allocated when saved');
      }
    }
    else {
      $extension_eid = t('None');
    }
    $options['voipextension_enable'] = array(
      'category' => 'voip',
      'title' => t('Extension'),
      'value' => $extension_eid,
    );
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    switch ($form_state['section']) {
      case 'header':
      case 'footer':
      case 'empty':
        $form[$form_state['section'] . '_format']['#type'] = 'value';
        $form[$form_state['section'] . '_format']['#value'] = 0;
        break;
      case 'voipextension_enable':
        $form['#title'] .= t('Extension');
        if (! module_exists('voipextension')) {
          $form['description']['#value'] = '<p>' . t('Install VoIP extension module to set extensions for view displays.') . '</p>';
          break;
        }
        $form['voipextension_enable'] = array(
          '#title' => t('Enabled'),
          '#type' => 'checkbox',
          '#default_value' => $this->get_option('voipextension_enable'),
          '#description' => t('Should an extension be enabled for this display.'),
        );
        $title = $this->get_option('voipextension_title');
        if (empty($title)) {
          $title = $this->get_option('title');
        }
        $form['voipextension_title'] = array(
          '#title' => t('Title'),
          '#type' => 'textfield',
          '#description' => t('The title used for the extension. A title must be set if the extension is enabled.'),
          '#default_value' => $title,
        );
        $form['voipextension_description'] = array(
          '#title' => t('Description'),
          '#type' => 'textarea',
          '#description' => t('The description used for the extension.'),
          '#default_value' => $this->get_option('voipextension_description'),
        );
        $form['voipextension_directory_type'] = array(
          '#title' => t('Listed in directory'),
          '#type' => 'checkbox',
          '#default_value' => $this->get_option('voipextension_directory_type'),
          '#description' => t('Should the extension be listed in the directory.'),
        );
        break;
    }
  }
  
  /**
   * Validate options form.
   */
  function options_validate(&$form, &$form_state) {
    parent::options_submit($form, $form_state);

    switch ($form_state['section']) {
      case 'voipextension_enable':
        if ($form_state['values']['voipextension_enable'] && empty($form_state['values']['voipextension_title'])) {
          form_error($form['voipextension_title'], t('If the extension is enabled, a title is required.'));
        }
        break;
    }
  }


  /**
   * Alter submitted data.
   */
  function options_submit(&$form, &$form_state) {
    parent::options_submit($form, $form_state);

    switch ($form_state['section']) {
      case 'header':
      case 'footer':
      case 'empty':
        $this->set_option($form_state['section'] . '_format', 0);
        break;
      case 'voipextension_enable':
        $this->set_option('voipextension_enable', $form_state['values']['voipextension_enable']);
        if ($form_state['values']['voipextension_enable']) {
          $this->set_option('voipextension_title', $form_state['values']['voipextension_title']);
          $this->set_option('voipextension_description', $form_state['values']['voipextension_description']);
          // the extension is actually enabled or changed when the view is saved.
        }
        break;
    }
  }

  function uses_breadcrumb() { 
    return FALSE; 
  }

  function get_style_type() {
    return 'voipviews';
  }

  function execute() {
    return $this->view->render($this->current_display);
  }

  function preview() {
    $voipscript = $this->view->render($this->current_display);
    if ($this->view->live_preview) {
      return theme('voipviews_view_preview', $voipscript);
    }
    else {
      return $voipscript;
    }
  }

  function render() {
    $voipscript = $this->view->style_plugin->render($this->view->result);
    return $voipscript;
  }

  /**
   * Render a text area, used with header, footer, empty.
   */
  function render_textarea($area) {
    $value = $this->get_option($area);
    // @todo we should make a format type for voip that does this (and better).
    return strip_tags(html_entity_decode($value));
  }
}
