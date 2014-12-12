<?php
// $Id$

/**
 * Implementation of hook_mailsave_clean().
 */
function mms_mx_iusacell_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  watchdog('mariorz', 'hello from mailsave clean ');

  if (preg_match('/@rek2\.com\.mx$/', $header->fromaddress)) {

    //Discard "unamed_attachments" (whatever those are)
    foreach ($node->mimeparts as $key => $mimepart) {
      $filename = strtolower($mimepart->filename);
      if($filename=='unnamed_attachment') {
        mailsave_discard_attachment($node, $filename);
      }
    }

    //fetch actual message content from included url
    if (preg_match('!(http://3g\.iusacell\.com\.mx/share\.do\?invite=.*)"!', $node->body, $matches)) {

      $url = str_replace('http://', 'https://', $matches[1]);
      $message_view = drupal_http_request($url);

      //message body is actually only included as a js object declartion (ugh!)
      if (preg_match('!new slideshowObjectInfo(.*)!', $message_view->data, $matches)) {
	$type_arr = preg_replace('#^new slideshowObjectInfo\s*\(\s*\'|\'\s*\)\s*$#', '', $matches[0]);
	$result_arr = preg_split('#\'\s*,\s*\'#', $type_arr);
	$node->body = $result_arr[3];
	$node->teaser = node_teaser($node->body);
      } else {
	$node->body = '';
	$node->teaser = node_teaser($node->body);
      }
      

      if (preg_match('!<strong>Subject:</strong> (.*)!', $message_view->data, $matches)) {
	$node->title = decode_entities(strip_tags($matches[1]));
      } else {
	$node->title = substr($node->body,0,60);
      }

    } else {
      //emtpy title & body in case url regex fails
      $node->body = '';
      $node->teaser = node_teaser($node->body);
      $node->title = '';
    }
  }
}

/**
 * Report back module information when requested.
 */
function mms_mx_iusacell_mailsave_clean_info() {
  $items['mms_mx_iusacell'] = array(
    'provider'    => t('Iusacell'),
    'country'     => 'MX',
    'author'      => 'Mario Romero (mario@romero.fm)',
    'description' => t('Clean up MMS messages sent via the Iusacell network.'),
  );
  return $items;
}
