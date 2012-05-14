<?php

/**
 * A handler for a voip menu item that returns say text if selected.
 */
class voipviews_handler_field_ivr_previous_row extends voipviews_handler_field_ivr {
  function render_script($values) {
    // Prevent fatal errors by accidentally going before first row.
    $row = $this->view->row_index > 0 ? $this->view->row_index - 1 : 0;
    $script = parent::render_script($values);
    $script->addGoto('row_' . $row . '_begin');
    return $script;
  }

  function render($values) {
    return 'row_' . $this->view->row_index - 1 . '_begin';
  }
}
