<?php

/**
 * @file
 *   Views theme related functions.
 */

/**
 * Preprocess voip output template.
 */
function template_preprocess_voipviews_views(&$vars) {
}

/**
 * As normal row handling, but it recieves a single field array rather than a row.
 */
function template_preprocess_voipviews_views_row(&$vars) {
  foreach ($vars['row'] as $id => $field) {
    // $field has really been created in the render() method.
    $vars['fields'][$id] = $field;
  }
}

/**
 * Pretty print voipScriptStore for views live_preview.
 */
function theme_voipviews_view_preview($script) {
  if (is_object($script)) {
    $output = '<h3>Title: ' . check_plain($script->getName()) . '</h3>';
    $output .= '<pre>Variables: ' . print_r($script->getVariables(), true) . '</pre>';
    $output .= '<div class="voipviews-preview">';
    foreach ($script as $key => $line) {
      list($cmd, $params) = $line;
      array_walk($params, '_theme_voipviews_parameters');
      $output .= '<p><span class="voipviews-row">' . $key . ':</span> <span class="voipviews-cmd">'. $cmd . '</span><span class="voipviews-params">( ' . implode(', ', $params) . ' )</span></p>';
    }
    $output .= '</div>';
  }
  else {
    $output = t('Error rendering view.');
  }
 
  return $output;
}

function _theme_voipviews_parameters(&$item, $key) {
  if (is_string($item)) {
    $item = '"' . $item . '"';
  }
  if (is_array($item)) {
    $item = print_r($item, true);
    $item = str_replace("\n", '', $item);
  }
  $item = check_plain($item);
}
