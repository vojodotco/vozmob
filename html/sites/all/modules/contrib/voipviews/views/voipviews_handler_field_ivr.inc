<?php

/**
 * @file
 *   Really paired down base field handler class.
 *
 * Could the options be simplified further?
 */


class voipviews_handler_field_ivr extends views_handler_field {
  /****
   * These are the two methods generally changed.
   */

  /**
   * Returned content is used for argument for voip script command.
   * 
   * If we can guarantee the voip context; then we could return array here?
   */
  function render($values) { 
    return '';
  }

  function render_script($values) {
    $script = new voipScriptStore;
    if (! empty($this->options['label'])) {
      $script->addSay($this->options['label']);
    }
    return $script;
  }

  /****
   * General field handler overrides.
   */
  function element_type() {
    return 'voipviews';
  }

  function query() {
  }

  function option_definition() {
    $options = parent::option_definition();
    $options['alter']['contains']['alter_text'] = array('default' => FALSE);
    $options['alter']['contains']['strip_tags'] = array('default' => TRUE);
    $options['empty']['default'] = '';
    $options['hide_empty'] = FALSE;
    $options['empty_zero'] = FALSE;
    $options['label']['default'] = '';
    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    unset($form['empty']);
    unset($form['empty_zero']);
    unset($form['hide_empty']);
    $form['label']['#title'] = t('Say');
    $form['label']['#description'] = t('Text to be said before the operation. (optional)');
  }

  /**
   * We just want to have render() called.
   */
  function allow_advanced_render() {
    return FALSE;
  }

  function advanced_render($values) {
    return $this->render($values);
  }
}
