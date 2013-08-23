<?php

/**
 * Implementation of hook_strongarm().
 */
function vozmob_og_strongarm() {
  $export = array();

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_group';
  $strongarm->value = 0;
  $export['comment_anonymous_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_group';
  $strongarm->value = '3';
  $export['comment_controls_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_group';
  $strongarm->value = '4';
  $export['comment_default_mode_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_group';
  $strongarm->value = '1';
  $export['comment_default_order_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_group';
  $strongarm->value = '50';
  $export['comment_default_per_page_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_group';
  $strongarm->value = '0';
  $export['comment_form_location_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_group';
  $strongarm->value = '2';
  $export['comment_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_group';
  $strongarm->value = '1';
  $export['comment_preview_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_group';
  $strongarm->value = '1';
  $export['comment_subject_field_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_group';
  $strongarm->value = array(
    'og_user_roles_default_role' => '5',
    'title' => '-5',
    'body_field' => '-2',
    'revision_information' => '11',
    'author' => '12',
    'options' => '13',
    'comment_settings' => '14',
    'language' => '-4',
    'translation' => '17',
    'menu' => '2',
    'path' => '18',
    'attachments' => '16',
    'flag' => '9',
    'og_description' => '-3',
    'og_selective' => '4',
    'og_register' => '3',
    'og_directory' => '6',
    'og_language' => '0',
  );
  $export['content_extra_weights_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'language_content_type_group';
  $strongarm->value = '2';
  $export['language_content_type_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_group';
  $strongarm->value = array(
    0 => 'status',
  );
  $export['node_options_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_admin_email_body';
  $strongarm->value = '@body -- a msg from your Vojo group, \'@group.\' !url_group';
  $export['og_admin_email_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_approve_user_body';
  $strongarm->value = 'You may now post messages in this group located at !group_url';
  $export['og_approve_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_approve_user_subject';
  $strongarm->value = 'Membership request approved for \'@title\'';
  $export['og_approve_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_checkboxes';
  $strongarm->value = 0;
  $export['og_audience_checkboxes'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_audience_required';
  $strongarm->value = '0';
  $export['og_audience_required'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_blog';
  $strongarm->value = 'group_post_standard';
  $export['og_content_type_usage_blog'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_group';
  $strongarm->value = 'group';
  $export['og_content_type_usage_group'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_test';
  $strongarm->value = 'omitted';
  $export['og_content_type_usage_test'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_deny_user_body';
  $strongarm->value = 'Sorry, your membership request was denied. Please contact the group administrator!';
  $export['og_deny_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_deny_user_subject';
  $strongarm->value = 'Membership request denied for \'@title\'';
  $export['og_deny_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_email_notification_pattern';
  $strongarm->value = '@user_name  <@site_mail>';
  $export['og_email_notification_pattern'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_home_page_view';
  $strongarm->value = 'og_ghp_ron';
  $export['og_home_page_view'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_invite_user_body';
  $strongarm->value = 'Hi. I\'m a member of \'@group\' and I welcome you to join too: !group_url | @body';
  $export['og_invite_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_invite_user_subject';
  $strongarm->value = 'Invitation to join the group \'@group\' at @site';
  $export['og_invite_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_max_groups_blog';
  $strongarm->value = '';
  $export['og_max_groups_blog'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_new_admin_body';
  $strongarm->value = '@username, you are now an administrator for the group \'@group\'. You can administer this group by logging in here: !group_url';
  $export['og_new_admin_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_new_admin_subject';
  $strongarm->value = 'You are now an administrator for the group \'@group\'';
  $export['og_new_admin_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_new_node_body';
  $strongarm->value = '@type \'@subject\' by @username
@node_teaser
!read_more: !content_url
Post reply: !reply_url
--
You are subscribed to \'@group\' at @site. To manage your subscription, visit !group_url';
  $export['og_new_node_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_new_node_subject';
  $strongarm->value = '@group: \'@title\' at @site';
  $export['og_new_node_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_notifications_autosubscribe';
  $strongarm->value = 1;
  $export['og_notifications_autosubscribe'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_request_user_body';
  $strongarm->value = 'To instantly approve this request, visit !approve_url. You may deny this request or manage members at !group_url. Personal message from @username: @request';
  $export['og_request_user_body'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_request_user_subject';
  $strongarm->value = 'Membership request for \'@group\' from \'@username\'';
  $export['og_request_user_subject'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility_directory';
  $strongarm->value = '1';
  $export['og_visibility_directory'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_visibility_registration';
  $strongarm->value = '1';
  $export['og_visibility_registration'] = $strongarm;

  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_group';
  $strongarm->value = '1';
  $export['upload_group'] = $strongarm;

  return $export;
}
