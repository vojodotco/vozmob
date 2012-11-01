<?php
// $Id$

/**
 * @file
 * Cleanup messages received from credo.
 */

/**
 * Implementation of hook_mailsave_clean().
 */
function mms_us_credo_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  // Check if this message was from credo.
  if (preg_match('!@waw.plspictures.com$!i', $header->fromaddress)) {
    // Check for text attachments to get body text
    $text_content = '';
    if ($debug) watchdog('mailsave', "Credo SMS/MMS with " . count($node->mimeparts)) . " MIME parts";
    $text_attachment_filenames = array();
    foreach ($node->mimeparts as $key => $mimepart) {
      if($debug) watchdog('mailsave', " - mimepart ".$key." = ".$mimepart->filemime." - ".$mimepart->filename." (".strlen($mimepart->data).")");
      $temp = serialize($mimepart);
      if(substr($mimepart->filename,0,4)=="text") {
        if($debug) watchdog('mailsave', " -- replaced body (".$mimepart->data.")");
        $text_content .= $mimepart->data;
        $text_attachment_filenames[] = $mimepart->filename;
      }
    }
    if (empty($text_content) && $node->title !== 'New Message') {
      // No text attachments, pull body from subject unless it's the default
      $text_content = $node->title;
    }
    $node->body = $text_content;
    $node->teaser = node_teaser($node->body);
    $node->title = substr($node->body,0,60);    // title length is based on experience
    
    // remove the "textplain_X.txt" attachements since we used them for the body
    foreach($text_attachment_filenames as $filename) {
      mailsave_discard_attachment($node, $filename);
      if($debug) watchdog('mailsave', ' - discarded attachment'.$filename);
    }
  }
}

/**
 * Report back module information when requested
 */
function mms_us_credo_mailsave_clean_info() {
  $items['mms_us_credo'] = array(
    'provider'    => t('Credo'),
    'country'     => 'US',
    'author'      => 'Mark Burdett',
    'description' => t('Clean up MMS messages sent via the Credo US network.'),
  );
  return $items;
}
