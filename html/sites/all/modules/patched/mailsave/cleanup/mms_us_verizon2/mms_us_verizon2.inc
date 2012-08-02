<?php

/**
 * Cleanup messages received from vtext.com
 */
function mms_us_verizon2_mailsave_clean(&$node, $result, $i, $header, $mailbox) {
  //watchdog('mailsave','Enter verizon2');
  $pattern = '!@vtext.com.?$!i';
  if (preg_match($pattern, $header->fromaddress)) {

    //watchdog('mailsave', 'Got email from Verion2 vtext.com');

    $text_content = "";
    // find the plain text attachements and stich them together as the body
    foreach ($node->mimeparts as $key => $mimepart) {
      //watchdog('mailsave', "  ".$key." = ".$mimepart->filemime." - ".$mimepart->filename." (".strlen($mimepart->data).")");
      $temp = serialize($mimepart);
      if( ($mimepart->filemime=="TEXT/PLAIN") && ($key!=0) ) {
        //watchdog('mailsave', "    replaced body (".$mimepart->data.")");
        $text_content .= str_replace("Message:","",$mimepart->data);
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
function mms_us_verizon2_mailsave_clean_info() {
  $items['mms_us_verizon2'] = array(
    'provider'    => t('Verizon2'),
    'country'     => 'US',
    'author'      => 'Rahul Bhargava',
    'description' => t('Clean up SMS messages sent from vtext.com via Verizon.'),
  );
  return $items;
}
