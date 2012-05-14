<?php

/**
 * @file
 *   voip script fields.
 */

class voipviews_views_plugin_row_ivr extends views_plugin_row {

  function option_definition() {
    $options = parent::option_definition();

    $options['ivr_prompt_intro'] = array(
      'default' => 'Press any key from the telephone keypad.',
      'translatable' => TRUE,
    );
    $options['ivr_invalid_msg'] = array(
      'default' => 'Invalid option selected.', 
      'translatable' => TRUE,
    );
    $options['ivr_no_input_msg'] = array(
      'default' => 'Invalid option selected.',
      'translatable' => TRUE,
    );
    $options['ivr_max_attempts'] = array(
      'default' => '3',
    );
    $options['ivr_timeout'] = array(
      'default' => '5',
    );
    $options['ivr_options'] = array(
      'default' => array(),
    );
    $options['ivr_prompt'] = array(
      'default' => array(),
    );
    $options['ivr_notfirst'] = array(
      'default' => array(),
    );
    $options['ivr_notlast'] = array(
      'default' => array(),
    );

    return $options;
  }

  /**
   * Provide the default form for setting options.
   */
  function options_form(&$form, &$form_state) {
    /**
     * setIvrMenu standard settings.
     */
    $form['ivr_prompt_intro'] = array(
      '#title' => t('Prompt message introduction'),
      '#type' => 'textfield',
      '#default_value' => filter_xss_admin($this->options['ivr_prompt_intro']),
      '#description' => t('Prompt message to read. Additional lines can be added for each key option below.'),
    );
    $form['ivr_invalid_msg'] = array(
      '#title' => t('Invalid input message'),
      '#type' => 'textfield',
      '#default_value' => filter_xss_admin($this->options['ivr_invalid_msg']),
      '#description' => t('This is the message that will be read out if an invalid key is pressed.'),
    );
    $form['ivr_no_input_msg'] = array(
      '#title' => t('No key pressed message'),
      '#type' => 'textfield',
      '#default_value' => filter_xss_admin($this->options['ivr_no_input_msg']),
      '#description' => t('This is the message that will be read out if an no key is pressed by the timeout.'),
    );
    $form['ivr_max_attempts'] = array(
      '#title' => t('Maximum attempts'),
      '#type' => 'textfield',
      '#default_value' => intval($this->options['ivr_max_attempts']),
      '#description' => t('Maximum number of times that the menu is read out on failure.'),
    );
    $form['ivr_timeout'] = array(
      '#title' => t('Timeout'),
      '#type' => 'textfield',
      '#default_value' => intval($this->options['ivr_timeout']),
      '#description' => t('Time in seconds to wait for input.'),
    );

    /**
     * Available fields to put into options.
     *
     * @todo what's the best UI for this?
     */
    $form['ivr_options'] = array(
      '#type' => 'fieldset',
      '#tree' => TRUE,
      '#title' => t('IVR rows'),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );
    $form['ivr_options']['introduction'] = array('#value' => t('First select the fields, then place them into dial option groups. Anything without a dial option will be read out before the menu starts.'));
    $fields = array();
    $handlers = $this->display->handler->get_handlers('field');
  
    // Check for any fields, as the view needs them
    if (empty($handlers)) {
      $form['ivr_options']['error_markup'] = array(
        '#value' => t('You need to enable at least one field before you can configure the IVR option group settings.'),
        '#prefix' => '<div class="error form-item description">',
        '#suffix' => '</div>',
      );
      return;
    }
    $key_options = array('' => '', '0' => '0', '1' => '1', '2' => '2', '3' => '3', '4' => '4', '5' => '5', '6' => '6', '7' => '7', '8' => '8', '9' => '9', '*' => '*', '#' => '#'); 
    // Go through fields
    foreach ($handlers as $field_id => $handler) {
      if (! $handler->options['exclude']) {
        $form['ivr_options'][$field_id] = array(
          '#title' => filter_xss_admin($handler->definition['title']),
          '#options' => $key_options,
          '#type' => 'select',
          '#default_value' => isset($this->options['ivr_options'][$field_id]) ? $this->options['ivr_options'][$field_id] : '',
        );
      }
    }
    $form['ivr_prompt']['#tree'] = TRUE;
    $form['ivr_notfirst']['#tree'] = TRUE;
    $form['ivr_notlast']['#tree'] = TRUE;
    foreach ($key_options as $key) {
      if ($key == '') { continue; }
      $form['ivr_prompt']["\\$key"] = array(
        '#title' => t('%key prompt text', array('%key' => $key)),
        '#type' => 'textfield',
        '#default_value' => empty($this->options['ivr_prompt']["\\$key"]) ? '' : $this->options['ivr_prompt']["\\$key"],
      );
      $form['ivr_notfirst']["\\$key"] = array(
        '#title' => t('%key not in first row', array('%key' => $key)),
        '#type' => 'checkbox',
        '#default_value' => isset($this->options['ivr_notfirst']["\\$key"]) ? $this->options['ivr_notfirst']["\\$key"] : FALSE,
      );
      $form['ivr_notlast']["\\$key"] = array(
        '#title' => t('%key not in last row', array('%key' => $key)),
        '#type' => 'checkbox',
        '#default_value' => isset($this->options['ivr_notlast']["\\$key"]) ? $this->options['ivr_notlast']["\\$key"] : FALSE,
      );
    }
  }

  /**
   * Renders the views.
   *
   * Normally this runs through every field as defined in the view, for the $row.
   * This is called more than once for the voip ivr version.
   *
   * Rather than completly abuse the theme_ system we seperate out each 'field'/line of the row,
   * and theme each individually so we can then add the output of these correctly to a
   * script object in the correct order.
   */
  function render($row) {
    $view = $this->view;
    $row_count = count($view->result);
    $voipscript = new voipScriptStore();
    $voipscript->addLabel('row_' . $view->row_index . '_begin');

    foreach ($view->field as $id => $field) {
      // render this even if set to exclude so it can be used elsewhere.
      $script_output = $view->style_plugin->get_script($view->row_index, $id);
      $key_group = $this->options['ivr_options'][$id];
      if (($this->options['ivr_notlast']["\\$key_group"] && $view->row_index + 1 == $row_count) || ($this->options['ivr_notfirst']["\\$key_group"] && $view->row_index == 0)) {
        // skip first and last row excludes
        continue;
      }
      if (empty($field->options['exclude']) && (!$empty || (empty($field->options['hide_empty']) && empty($vars['options']['hide_empty'])))) {
        if ($key_group == '') {
          // not in a key group add to script directly.
          $voipscript->appendScript($script_output);
        }
        else {
          // include this key's prompt, and collect together.
          $prompts[$key_group] = (! empty($this->options['ivr_prompt']["\\$key_group"])) ? $this->options['ivr_prompt']["\\$key_group"] . " " : '';
          $key_scripts[$key_group][] = $script_output;
        }
      }
    }

    if (count($key_scripts)) {
      // add ivr menu with prompt and keys we have encountered.
      $prompt = (! empty($this->options['ivr_prompt_intro'])) ? $this->options['ivr_prompt_intro'] . ' ' : '';
      $prompt .= implode($prompts);
      $voipscript->addLabel('row_' . $view->row_index . '_menu');
      // add options pointing to key group scripts
      $input_options = array();
      foreach ($key_scripts as $key_group => $scripts) {
        $input_options[$key_group] = 'row_' . $view->row_index . '_key_' . $key_group;
      }
      $voipscript->addRunIvrMenu($prompt, $input_options, $this->options['ivr_invalid_msg'], $this->options['ivr_no_input_msg'], $this->options['ivr_max_attempts'], $this->options['ivr_timeout']);
      $voipscript->addGoto('%ivr_option_selected');
      $voipscript->addLabel('no_input_received_' . $view->row_index);
      $voipscript->addSay($this->options['ivr_invalid_msg']);
      $voipscript->addGoto('row_' . $view->row_index . '_menu'); // @todo beter to go to next row/return maybe?

      // add key groups scripts.
      foreach ($key_scripts as $key_group => $scripts) {
        $voipscript->addLabel('row_' . $view->row_index . '_key_' . $key_group);
        foreach ($scripts as $script) {
          $voipscript->appendScript($script);
        }
      }
      $voipscript->addLabel('row_' . $view->row_index . '_end');
    }
    else {
      if ($view->live_preview) {
        drupal_set_message('Configure the row style to add menu options and prompts');
      }
    }

    return $voipscript;
  }
}
