<?php
// $Id$

/**
 * Implementation of hook_mailsave_clean().
 */
function mms_br_tim_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  if (preg_match('/@tim.com.br$/', $header->fromaddress)) {
    // TODO
  }
}

/**
 * Report back module information when requested.
 */
function mms_br_tim_mailsave_clean_info() {
  $items['mms_br_tim'] = array(
    'provider'    => t('Tim'),
    'country'     => 'BR',
    'author'      => 'Edward L Platt',
    'description' => t('Clean up MMS messages sent via the Tim network.'),
  );
  return $items;
}
