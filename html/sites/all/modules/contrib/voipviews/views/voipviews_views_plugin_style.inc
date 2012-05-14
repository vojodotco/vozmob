<?php

/**
 * @file
 *   Views style plugin to render ..i
 *
 * Should we be rendering the whole thing or could we step through it?
 */
class voipviews_views_plugin_style extends views_plugin_style {
  /**
   * Render all of the fields for a given style and store them on the object.
   *
   * All row styles are voipviews ones so we can work with voipscript. 
   * Advanced rendering and token replacement still needs the standard render.
   *
   * @param $result
   *   The result array from $view->result
   */
  function render_fields($result) {
    if (!$this->uses_fields()) {
      return;
    }

    if (isset($this->rendered_fields)) {
      return $this->rendered_fields;
    }

    $this->view->row_index = 0;
    $keys = array_keys($this->view->field);
    foreach ($result as $count => $row) {
      $this->view->row_index = $count;
      foreach ($keys as $id) {
        $themed_output = $this->view->field[$id]->theme($row);
        if ($this->view->field[$id]->element_type() == 'voipviews') {
          // @todo check empty behaviour here
          $script = new voipScriptStore();
          $label = $this->view->field[$id]->label();
          if (! empty($label)) {
            $script->addSay($label);
          }
          $script->appendScript($this->view->field[$id]->render_script($row));
        }
        else {
          $script = new voipScriptStore();
          if ($themed_output !== 0 && empty($themed_output)) {
            if ($this->view->field[$id]->options['hide_empty'] || empty($this->view->field[$id]->options['empty'])) {
              // nuffink now
            }
            else {
              if (! empty($label)) {
                $script->addSay($label . '.');
              }
              $script->addSay($this->view->field[$id]->options['empty']);
            }
          }
          else {
            $label = $this->view->field[$id]->label(); // @todo clean characters.
            if (! empty($label)) {
              $script->addSay($label . '.');
            }
            $script->addSay($themed_output);
          }
        }
        $this->rendered_fields[$count][$id] = $themed_output;
        $this->rendered_scripts[$count][$id] = $script;
      }
    } 
    unset($this->view->row_index);
  }

  /**
   * Retrieve an individual fields script.
   *
   * @see render_fields().
   */
  function get_script($index, $field) {
    if (!isset($this->rendered_scripts)) {
      $this->render_fields($this->view->result);
    }

    if (isset($this->rendered_scripts[$index][$field])) {
      return $this->rendered_scripts[$index][$field];
    }
  }

  /**
   * Render the display in this style.
   */
  function render() {
    if ($this->uses_row_plugin() && empty($this->row_plugin)) {
      vpr('views_plugin_style_default: Missing row plugin');
      return;
    }

    // Group the rows according to the grouping field, if specified.
    $sets = $this->render_grouping($this->view->result, $this->options['grouping']);
    // Render each group separately and concatenate.  Plugins may override this
    // method if they wish some other way of handling grouping.
    $output = array();
    foreach ($sets as $title => $records) {
      if ($this->uses_row_plugin()) {
        $rows = array();
        foreach ($records as $row_index => $row) {
          $this->view->row_index = $row_index;
          $rows[] = $this->row_plugin->render($row);
        }
      }
      else {
        $rows = $records;
      }
    }

    // @todo:-
    // at this point theming would be normal. Some alternative would add flexibility...
    // What about sending multiple voipscriptstore objects that can be manipulated
    // and put together into the final returned script?
    // Normally $header, $footer etc. would be available seperately.
    if (count($rows) || $this->view->display_handler->get_option('header_empty')) {
      $header_text = $this->view->display_handler->render_header();
    }
    else {
      $header_text = '';
    }
    if (! count($rows)) {
      $empty_text = $this->view->display_handler->render_empty();
    }
    if (count($rows) || $this->view->display_handler->get_option('footer_empty')) {
      $footer_text = $this->view->display_handler->render_footer();
    }
    else {
      $footer_text = '';
    }

    $voipscript = new voipScriptStore();
    if (! empty($header_text)) {
      $voipscript->addSay($header_text);
    }
    if (count($rows)) {
      foreach ($rows as $row) {
        $voipscript->appendScript($row);
      }
    }
    elseif (! empty($empty_text)) {
      $voipscript->addSay($empty_text);
    }
    if (! empty($footer_text)) {
      $voipscript->addSay($footer_text);
    }

    unset($this->view->row_index);
    return $voipscript;
  }
}
