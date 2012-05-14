<?php

/**
 * A handler for a voip menu item that returns say text if selected.
 */
class voipviews_handler_field_ivr_return extends voipviews_handler_field_ivr {
  function render_script($values) {
    $script = new voipScriptStore();
    $script->addReturn();
    return $script;
  } 

  function render($values) { 
    return NULL;
  }
}
