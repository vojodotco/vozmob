<?php
// $Id$

/**
 * Render SMS Registration settings form.
 */
function sms_registration_settings() {

  $form['options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Core Options'),
    '#tree' => FALSE,
  );
  $form['options']['sms_registration_address'] = array(
    '#type' => 'textfield',
    '#title' => t('Registration address'),
    '#description' => t('Enter the e-mail address used to receive site registrations.'),
    '#default_value' => variable_get('sms_registration_address', ''),
  );
  $form['options']['sms_registration_request_user'] = array(
    '#type' => 'radios',
    '#options' => array('' => t('None'), 'name' => t('User name'), 'mail' => t('User e-mail address')),
    '#title' => t('Request user fields on registration'),
    '#description' => t('Select a user field to request from users after creating a new account.'),
    '#default_value' => variable_get('sms_registration_request_user', 'name'),
  );
  $form['options']['sms_registration_username'] = array(
    '#type' => 'textfield',
    '#title' => t('User name prefix'),
    '#description' => t('Enter a user name prefix on randomly generated user names.'),
    '#default_value' => variable_get('sms_registration_username', 'Drupal-'),
  );
  $form['options']['sms_registration_role'] = array(
    '#type' => 'select',
    '#title' => t('Default role'),
    '#description' => t('Select a default role granted to users registering via SMS.'),
    '#options' => user_roles(TRUE),
    '#default_value' => variable_get('sms_registration_role', NULL),
  );
  
  $form['feedback'] = array(
    '#type' => 'fieldset',
    '#title' => t('Feedback to Registrants'),
    '#tree' => FALSE,
  );
  $form['feedback']['sms_registration_failed_msg'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#title' => t('Registration Failed'),
    '#description' => t('Text to send when the attempt to change username failed (this assumes the name must have been duplicate). '.
      'Use !name to represent the user\s name'),
    '#default_value' => variable_get('sms_registration_failed_msg', 
      'A blog for !name was not created. Please choose another name.'),
  );
  $form['feedback']['sms_registration_name_changed_msg'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#title' => t('Name Changed'),
    '#description' => t('Text to send when the attempt to change username worked.  '.
      'Use !name to represent the user\s name, and !server_url to represent the server url.'),
    '#default_value' => variable_get('sms_registration_name_changed_msg', 
      'We changed your !server_url username to !name'),
  );
  $form['feedback']['sms_registration_welcome_email_msg'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#title' => t('Welcome with Email Request'),
    '#description' => t('Text to send when the user submitted content for the first time, and we are requesting email upon registration. '.
      'Use !name to represent the user\s name, and !pass for their password, and !server_url to represent the server url.'),
    '#default_value' => variable_get('sms_registration_welcome_email_msg', 
      'Welcome to !server_url. Your username is !name, password is !pass. To submit your content, please reply with your email address!'),
  );
  $form['feedback']['sms_registration_welcome_username_msg'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#title' => t('Welcome with Username Request'),
    '#description' => t('Text to send when the user submitted content for the first time, and we are requesting a unique username upon registration. '.
      'Use !name to represent the user\s name, and !pass for their password, and !server_url to represent the server url.'),
    '#default_value' => variable_get('sms_registration_welcome_username_msg', 
      'Welcome to !server_url ! Your username is !name, password is !pass. To change your username, reply to this msg w/the name you want!'),
  );
  $form['feedback']['sms_registration_registrar_welcome_msg'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#title' => t('Welcome from Registrar'),
    '#description' => t('Text to send when the user submitted directly to the registrar email address. '.
      'Use !name to represent the user\s name, and !pass for their password, and !server_url to represent the server url.'),
    '#default_value' => variable_get('sms_registration_registrar_welcome_msg', 
      'Welcome to !server_url ! Your username is !name, password is !pass. You can log in to the website with this info.'),
  );
  $form['feedback']['sms_registration_parse_error_msg'] = array(
    '#type' => 'textarea',
    '#rows' => 2,
    '#title' => t('Parse Error'),
    '#description' => t('Text to send when the user\s message wasn\'t parsed correctly.. '.
      'Use !carrier to represent domain name the email was received from.'),
    '#default_value' => variable_get('sms_registration_parse_error_msg', 
      'Sorry, we don\'t yet support !carrier.'),
  );
  
  return system_settings_form($form);
}
