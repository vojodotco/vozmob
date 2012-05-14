<?php

/**
 * A handler for a voip menu item that returns say text if selected.
 */
class voipviews_handler_field_sms_text extends views_handler_field {
  function query() {
  }

  function element_type() {
    return 'voipviews';
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['alter']['contains']['alter_text'] = array('default' => TRUE);
    $options['alter']['contains']['strip_tags'] = array('default' => TRUE);
    $options['alter']['contains']['make_link'] = array('default' => FALSE);
    $options['label']['default'] = '';
    $options['number'] = array('default' => '');
    $options['network'] = array('default' => 'sms');
    $options['caller_id'] = array('default' => '');
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // Remove alter_text checkbox
    unset($form['alter']['alter_text']);
    unset($form['alter']['text']['#dependency']);
    unset($form['alter']['text']['#process']);
    $form['alter']['make_link']['#type'] = 'hidden';
    // Remove strip HTML checkbox
    unset($form['alter']['strip_tags']);
    // We use the label as the question
    unset($form['label']); 
    $form['number'] = array(
      '#type' => 'textfield',
      '#title' => 'Phone number',
      '#description' => "Number to send to. The default, if blank, is the caller's or called number.",
      '#default_value' => $this->options['number'],
    );
    $form['network'] = array(
      '#type' => 'textfield',
      '#title' => 'Network',
      '#description' => "String with the network to be used. The default network is 'sms'.",
      '#default_value' => $this->options['network'],
    );
    $form['caller_id'] = array(
      '#type' => 'textfield',
      '#title' => 'Caller ID',
      '#description' => "String with the caller id to be used. Depends on network. Defaults to called or calling party.",
      '#default_value' => $this->options['caller_id'],
    );
  }

  /**
   * If we can guarantee the voip context; then we could return array here?
   */
  function render($values) {
    return '';
  }

  function render_script($values) {
    $script = new voipScriptStore();
    // generally we should be called once rendering of text has happened.
    if (! isset($this->last_render)) {
      $this->advanced_render($values);
    }
    // @todo run these through token
    $to = $this->options['number'];
    $network = $this->options['network'];
    $caller_id = $this->options['caller_id'];
    $script->addSendText($this->last_render, $to, $network, $caller_id);
    // @todo this could get clever and have optional messages based on 'send_text_status' vscript variable.
    return $script;
  }
}
