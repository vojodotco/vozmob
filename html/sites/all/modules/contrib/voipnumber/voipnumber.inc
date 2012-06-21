<?php 

/**
 * @file
 * Implementation of VoIP validation classes
 */

  class VoipNumber {
  
    private $number;
    private $name;
    private $type;
    private $nid;
    private $uid;
   
   function __construct($number, $name, $type) {
     $this->number = $number;
     $this->name = $name;
     $this->type = $type;
   }   
   /**
   * Returns an array with the VoIP Numbers associated with the given user
   *
   * @param $uid
   *   Integer representing user id value. If left empty then current user id will be used instead.
   *
   * @return
   *   Array of VoIP number objects.
   */
    public static function getNumbersFromUid($uid=NULL){
      if (empty($uid)) {
        global $user;
        $uid = $user->uid;
      }
      //Invoke hook_get_voip_numbers()
      $numbers = module_invoke_all('get_voip_numbers', $uid, 'user');
      return $numbers;
    }
    
   /**
   * Returns the default VoIP Number associated with the given user
   *
   * @param $uid
   *   Integer representing user id value. If left empty then current user id will be used instead.
   *
   * @return
   *   Single VoIP number object.
   */
    public static function getDefaultNumberFromUid($uid=NULL){
      if (empty($uid)) {
        global $user;
        $uid = $user->uid;
      }
      $voip_user = user_load($uid);
      //Retrieve default either from user profile
      if(!empty($voip_user->voipnumber_phone)){
         $number = $voip_user->voipnumber_country . $voip_user->voipnumber_phone;
         $name = 'Profile number(' . $numbers[0]->number . ')';
         $type = 'VoIP User Profile Number';
         $vn = new VoipNumber($number, $name, $type);
         return $vn;
      }
      else{
        //otherwise, get first number from the array
        $numbers = VoipNumber::getNumbersFromUid($uid); 
        if(empty($numbers)){
          return NULL;
        }
      }
      return $numbers[0];
    }
    
   /**
   * Returns an array with the VoIP Numbers associated with the given node
   *
   * @param $nid
   *   Integer representing node id value.
   *
   * @return
   *   Array of VoIP number objects.
   */
    public static function getNumbersFromNid($nid){
      //Invoke hook_get_voip_numbers()
      $numbers = module_invoke_all('get_voip_numbers', $nid, 'node');
      return $numbers;
    }
    
   /**
   * Returns the default VoIP Number associated with the given node
   *
   * @param $nid
   *   Integer representing node id value.
   *
   * @return
   *   Single VoIP number object.
   */
    public static function getDefaultNumberFromNid($nid){
      $numbers = VoipNumber::getNumbersFromNid($nid);
      if(empty($numbers)){
        return NULL;
      }
      return $numbers[0];
    }
    
   /**
   * Returns an array with the user ids associated with the specified number
   *
   * @param $number
   *   String containing the number
   *
   * @return
   *   Array of user ids.
   */
    public static function getUidsFromNumber($number){
      //Replace + signs with 2 zeroes
	  $number  = str_replace('+','00', $number);
	  //Replace any blanks minuses underscores...
	  $number  = str_replace(array(' ','-','.','/','(',')'), '', $number);
      $uids = module_invoke_all('get_voip_numbers', $number, 'uids');
      return $uids;
    }
    
   
   /**
   * Returns an array with the node ids associated with the given number
   *
   * @param $number
   *   String containing the number
   *
   * @return
   *   Array of node ids.
   */
    public static function getNidsFromNumber($number){
      //Replace + signs with 2 zeroes
	  $number  = str_replace('+','00', $number);
	  //Replace any blanks minuses underscores...
	  $number  = str_replace(array(' ','-','.','/','(',')'), '', $number);
      $nids = module_invoke_all('get_voip_numbers', $number, 'nids');
      return $nids;
    }
    
    function getNumber(){
      return $this->number;
    }
    function getType(){
      return $this->type;
    }
    function getName(){
      return $this->name;
    }
    function getUid(){
      return $this->uid;
    }
    function getNid(){
      return $this->nid;
    }
 }

