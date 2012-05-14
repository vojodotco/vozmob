<?php

/**
 * A handler for a voip menu item that returns say text if selected.
 */
class voipviews_handler_field_ivr_goto_menu extends voipviews_handler_field_ivr {
  function render_script($values) {
    $script = new voipScriptStore();
    $script->addGoto('row_' . $this->view->row_index . '_menu');
    return $script;
  }

  function render($values) { 
    return 'row_' . $this->view->row_index . '_menu';
  }
}
