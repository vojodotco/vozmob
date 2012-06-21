<?php

/**
 * FormAPI theme function. Theme the output of an video upload field.
 * @param $element
 * @return mixed
 */
function theme_jwfilefield_widget($element) {
  return theme('form_element', $element, $element['#children']);
}

function theme_jwfilefield_widget_item($element) {
  return theme('filefield_widget_item', $element);
}

function theme_jwfilefield_widget_preview($item) {
  return theme('filefield_widget_preview', $item);
}