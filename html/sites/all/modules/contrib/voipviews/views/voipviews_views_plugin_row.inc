<?php

/**
 * @file
 *   voip script fields.
 */

class voipviews_views_plugin_row extends views_plugin_row {

  /**
   * Renders the views.
   */
  function render($row) {
    $view = $this->view;
    $row_count = count($view->result);
    $voipscript = new voipScriptStore();
    foreach ($view->field as $id => $field) {
      // render this even if set to exclude so it can be used elsewhere.
      $field_output = $view->style_plugin->get_field($view->row_index, $id);
      if (! (empty($field_output) && $field->options['hide_empty'])) {
        $script_output = $view->style_plugin->get_script($view->row_index, $id);
        $voipscript->appendScript($script_output);
      }
    }

    return $voipscript;
  }
}
