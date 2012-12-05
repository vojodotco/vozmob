<?php
// $Id$

/**
 * Implementation of hook_mailsave_clean().
 */
function mms_us_virgin_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  // Build regex to see if this was from virgin mobile
  if (preg_match('@vmpix.com@', $header->fromaddress)) {

    $node->body = str_replace('<p ALIGN=LEFT><font size=2 color="#cc0000" face=Verdana>This message is from', '', $node->body);
    $node->body = str_replace('a Virgin Mobile user. Enjoy.<br>', '', $node->body);
    $node->body = str_replace('_____________________________________________________________</font></p>', '', $node->body);

    $node->teaser = node_teaser($node->body);

    // Set node title from body if title is empty.
    if (empty($node->title)) {
      $node->title = truncate_utf8(decode_entities(strip_tags($body)), 60, TRUE, TRUE);
    }

    // Get rid of extra text attachments
    foreach ($node->mailsave_attachments as $key => $file) {
      if ($file['filemime'] == 'text/plain') {
        unset($node->mailsave_attachments[$key]);
      }
    }
  } else if (preg_match('@pixmbl.com@', $header->fromaddress)) {
    $matches = array();
    preg_match('@<TITLE>(.*)</TITLE>.*<PRE>(.*)</PRE>@s', $node->body, $matches);
    $node->title = trim(strip_tags($matches[1]));
    $node->body = trim(strip_tags($matches[2]));
    if (empty($node->title)) {
      $node->title = truncate_utf8(decode_entities(strip_tags($node->body)), 60, TRUE, TRUE);
    }
    if (empty($node->body)) {
      $node->body = $node->title;
    }
    $node->teaser = node_teaser($node->body);
  }
}

/**
 * Report back module information when requested
 */
function mms_us_virgin_mailsave_clean_info() {
  $items['mms_us_virgin'] = array(
    'provider'     => t('Virgin Mobile'),
    'country'      => 'US',
    'author'       => 'Gabriela Rodriguez',
    'description'  => t('Clean up MMS messages sent via the Virgin Mobile USA network.'),
  );

  return $items;
}
