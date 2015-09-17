<?php
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>

<?php
// A hack to get blog node form to display for anonymouse users (due to a blog module permissions bug).
module_load_include('inc', 'node', 'node.pages');  
$node_type = 'blog';
$form_id = $node_type . '_node_form';
global $user;
$new_node = new stdClass();
$new_node->uid = $user->uid;
$new_node->name = (isset($user->name) ? $user->name : '');
$new_node->type = $node_type;
node_object_prepare($new_node);  // Invoke hook_nodapi and hook_node
$output = drupal_get_form($form_id, $new_node);
print $output;
?>
