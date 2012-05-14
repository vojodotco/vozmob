<?php
/**
 * @file voipviews-views-row.tpl.php
 *   Output text to be spoken for a field in a row. NB it's actually just one field at a time.
 *
 * - $view: The view in use.
 * - $fields: an array of $field objects. Each one contains:
 *   - $field->content: The output of the field.
 *   - $field->raw: The raw data for the field, if it exists. This is NOT output safe.
 *   - $field->class: The safe class id to use.
 *   - $field->handler: The Views field handler object controlling this field. Do not use
 *     var_export to dump this object, as it can't handle the recursion.
***** not available as they are options removed - leaving here as a reminder.
 *   - $field->inline: Whether or not the field should be inline.
 *   - $field->inline_html: either div or span based on the above flag.
 *   - $field->separator: an optional separator that may appear before a field.
*****
 * - $row: The raw result object from the query, with all data it fetched.
 *
 */

?>
<?php foreach ($fields as $id => $field): ?>
  <?php if ($field->label): ?><?php print $field->label; ?>:<?php endif; ?>  <?php print $field->content; ?>
<?php endforeach; ?>
