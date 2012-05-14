<?php

/**
 * Just a file entry wrapped with audiofield theme.
 */
class voipviews_handler_field_file_url extends views_handler_field_file {
  function render($values) {
    return file_create_url($values->{$this->field_alias});
  }
}
