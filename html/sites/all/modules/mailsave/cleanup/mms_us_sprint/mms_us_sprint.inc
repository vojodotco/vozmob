<?php

/**
 * Implementation of hook_mailsave_clean().
 * The new sprint messages look like they have everything attached inline, which is great 
 * (no more cloud-CDN!). The email body is HTML, and doesn't actually contain the text 
 * content of the mms - that is in an attachment called "textplain_X.txt".
 */
function mms_us_sprint_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  $pattern = '!@pm.sprint.com.?$!i';
  if (preg_match($pattern, $header->fromaddress)) {

    //watchdog('mailsave', 'Got email from Sprint');

    $text_attachment_filename = null;

    // find the "textplain_X.txt" attachement and use it for the body
    foreach ($node->mimeparts as $key => $mimepart) {
      //watchdog('mailsave', "  ".$key." = ".$mimepart->filemime." - ".$mimepart->filename." (".strlen($mimepart->data).")");
      $temp = serialize($mimepart);
      if(substr($mimepart->filename,0,9)=="textplain") {
        //watchdog('mailsave', "    replaced body (".$mimepart->data.")");
        $node->body = $mimepart->data;
        $node->teaser = node_teaser($node->body);
        $node->title = substr($node->body,0,20);    // totally arbitrary title length
        $text_attachment_filename = $mimepart->filename;
      }
    }
    //watchdog('mailsave', 'last = '.$temp);

    // remove the "textplain_X.txt" attachement since we used if for the body
    if ($text_attachement_filename!=null) {
      //unset($node->mailsave_attachments[$text_attachment_key]);
      mailsave_discard_attachment($node, $text_attachment_filename);
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
