<?php
// $Id$

/**
 * Implementation of hook_mailsave_clean().
 */
function mms_br_oi_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  if (preg_match('/@mms\.oi\.com\.br$/', $header->fromaddress)) {
    $node->title = substr($node->body, 0, 60);
  }
}

/**
 * Report back module information when requested.
 */
function mms_br_oi_mailsave_clean_info() {
  $items['mms_br_oi'] = array(
    'provider'    => t('Oi'),
    'country'     => 'BR',
    'author'      => 'Edward L Platt',
    'description' => t('Clean up MMS messages sent via the Oi network.'),
  );
  return $items;
}
