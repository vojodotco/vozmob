<?php

/**
 * A handler for a voip menu item that returns say text if selected.
 */
class voipviews_handler_field_ivr_next_row extends voipviews_handler_field_ivr {
  function render_script($values) {
    $script = new voipScriptStore();
    // Going to the end of this row, which is always there.
    // This will be just before the begin of the next row if it exists.
    $script->addGoto('row_' . ($this->view->row_index) . '_end');
    return $script;
  }

  function render($values) {
    return 'row_' . $this->view->row_index + 1 . '_begin';
  }
}
