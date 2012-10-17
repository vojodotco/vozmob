<?php

/**
 * Implementation of hook_mailsave_clean().
 * The new sprint messages look like they have everything attached inline, which is great 
 * (no more cloud-CDN!). The email body is HTML, and doesn't actually contain the text 
 * content of the mms - that is in an attachment called "textplain_X.txt".
 */
function mms_us_sprint_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  $debug = false;
  $pattern = '!@pm.sprint.com.?$!i';
  if (preg_match($pattern, $header->fromaddress)) {

    if($debug) watchdog('mailsave', 'Got email from Sprint');

    $text_attachment_filenames = array();

    if($debug) watchdog('mailsave'," - title:".$node->title);
    if($debug) watchdog('mailsave'," - body:".$node->body);
    $text_content = "";
    // find the "text_X.txt" attachement and use it for the body
    foreach ($node->mimeparts as $key => $mimepart) {
      if($debug) watchdog('mailsave', " - mimepart ".$key." = ".$mimepart->filemime." - ".$mimepart->filename." (".strlen($mimepart->data).")");
      $temp = serialize($mimepart);
      if(substr($mimepart->filename,0,4)=="text") {
        if($debug) watchdog('mailsave', " -- replaced body (".$mimepart->data.")");
        $text_content .= $mimepart->data;
        $text_attachment_filenames[] = $mimepart->filename;
      }
    }
    if (empty($test_content) && $node->title !== 'New Message') {
      // No text attachments, pull body from subject unless it's the default
      $text_content = $node->title;
    }
    if($debug) watchdog('mailsave', ' - last mimepart = '.$temp);

    // there can be more than one "textplain_X.txt" attachment, so do this all outside the for loop
    $node->body = $text_content;
    $node->teaser = node_teaser($node->body);
    $node->title = substr($node->body,0,60);    // title length is based on experience

    // remove the "textplain_X.txt" attachement since we used if for the body
    foreach($text_attachment_filenames as $filename) {
      //unset($node->mailsave_attachments[$text_attachment_key]);
      mailsave_discard_attachment($node, $filename);
      if($debug) watchdog('mailsave', ' - discarded attachment'.$filename);
    }

  }

}

/**
 * Report back module information when requested
 */
function mms_us_sprint_mailsave_clean_info() {
  $items['mms_us_sprint'] = array(
    'provider'    => t('Sprint'),
    'country'     => 'US',
    'author'      => 'Rahul Bhargava',
    'description' => t('Clean up MMS messages sent via the Sprint US network.'),
  );
  return $items;
}
