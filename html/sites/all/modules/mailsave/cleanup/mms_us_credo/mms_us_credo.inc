<?php
// $Id$

/**
 * @file
 * Cleanup messages received from credo.
 */

function mms_us_credo_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  //watchdog('mailsave','Enter credo');
  $pattern = '!@waw.plspictures.com.?$!i';
  if (preg_match($pattern, $header->fromaddress)) {

    //watchdog('mailsave', 'Got email from Credo');

    $text_content = "";
    // find the "textplain_X.txt" attachement and use it for the body
    foreach ($node->mimeparts as $key => $mimepart) {
      //watchdog('mailsave', "  ".$key." = ".$mimepart->filemime." - ".$mimepart->filename." (".strlen($mimepart->data).")");
      $temp = serialize($mimepart);
      if( ($mimepart->filemime=="TEXT/PLAIN") && ($key!=0) ) {
        //watchdog('mailsave', "    replaced body (".$mimepart->data.")");
        $text_content .= $mimepart->data;
      }
    }
    //watchdog('mailsave', 'last = '.$temp);

    // there can be more than one "textplain_X.txt" attachment, so do this all outside the for loop
    $node->body = $text_content;
    $node->teaser = node_teaser($node->body);
    $node->title = substr($node->body,0,60);    // title length is based on experience

  }

}

/**
 * Report back module information when requested
 */
function mms_us_credo_mailsave_clean_info() {
  $items['mms_us_credo'] = array(
    'provider'    => t('Credo'),
    'country'     => 'US',
    'author'      => 'Rahul Bhargava',
    'description' => t('Clean up MMS messages sent via the Credo US network.'),
  );
  return $items;
}
