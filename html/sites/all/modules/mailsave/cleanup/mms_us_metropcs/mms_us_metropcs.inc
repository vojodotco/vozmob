<?php
// $Id: mms_us_metropcs.inc,v 1.2 2007/10/28 13:36:08 stuartgreenfield Exp $

/**
 * Implementation of hook_mailsave_clean().
 */
function mms_us_metropcs_mailsave_clean(&$node, $result, $i, $header, $mailbox) {

  //watchdog('mailsave','Enter metropcs');

  // Build regex to see if this was from MetroPCS.
  $pattern = '@mymetropcs\.com$@';
  if (preg_match($pattern, $header->fromaddress)) {

    //watchdog('mailsave', 'Got email from MetroPCS');

    $text_content = "";
    // find the plain text attachements and stich them together as the body
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
function mms_us_metropcs_mailsave_clean_info() {
  $items['mms_us_metropcs'] = array(
    'provider'    => t('MetroPCS'),
    'country'     => 'US',
    'author'      => 'Rahul Bhargava',
    'description' => t('Clean up MMS messages sent via the MetroPCS US network.'),
  );
  return $items;
}
