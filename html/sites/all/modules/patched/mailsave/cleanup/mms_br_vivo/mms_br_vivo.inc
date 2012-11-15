<?php
// $Id$

/**
 * Implementation of hook_mailsave_clean().
 */
function mms_br_vivo_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  if (preg_match('/@vivomms.com.br$/', $header->fromaddress)) {
    $body = strip_tags($node->body);
    $body = str_replace('New Page 1', '', $body);
    $body = str_replace('Conteudo enviado do meu Celular Vivo', '', $body);
    $body = trim($body);
    $node->body = $body;
    $node->title = substr($node->body,0,60);    // title length is based on experience
    $node->teaser = node_teaser($node->body);
  }
}

/**
 * Report back module information when requested.
 */
function mms_br_vivo_mailsave_clean_info() {
  $items['mms_br_vivo'] = array(
    'provider'    => t('Vivo'),
    'country'     => 'BR',
    'author'      => 'Edward L Platt',
    'description' => t('Clean up MMS messages sent via the Vivo network.'),
  );
  return $items;
}
