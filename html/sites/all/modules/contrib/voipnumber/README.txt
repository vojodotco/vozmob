== Introduction ==

The voipnumber.module provides an API for storing and managing phone, SMS and SIP numbers. It provides variaty of API methods like recognizing 
Country from phone number, extracting country code from phone number, storing additional data as number name, number type, number country and number status.

In particular, this module provides:

 - a new CCK VoIP Number field with specific widgets for storing landline and mobile phone numbers, SIP addresses, IM usernames and "unknown" number types 

 - a default VoIP Number that might be included directly into user profiles

 - an API that enables access to the different VoIP Numbers associated with individual users and content types

 - A "VoIP Number Phone" and a "VoIP Number SMS" module to facilitate the integration with the telephone numbers already provided by the Phone module (http://drupal.org/project/phone) and the SMS Framework (http://drupal.org/project/smsframework)


== Installation ==

1. Extract voipnumber.module to your sites/all/modules directory

2. Enable the VoIP Number module in admin/build/modules

3. Optionally enable "VoIP Number Phone" and/or "VoIP Number SMS" modules to use telephone numbers already defined by the 
Phone module and the SMS Framework, respectively.


== Using VoIP Number CCK fields ==

!!! THIS FEATURE IS MOVED TO SEPERATE MODULE (http://drupal.org/project/voipnumberfield) !!!


== The VoIP Number API ==

For API usage see voipnumber.inc


Hooks:

The VoIP Number module provides hook_get_voip_numbers() to enable other modules to add their own custom numbers to the VoIP Number API.

hook_get_voip_numbers($id, $type, $op):
$type - can be user, node, uids, nids for returing numbers by specific user, specific node, list of user ids by specific number and 
        list of node ids by specific number.
$op - is either uid, nid or number, depending on value of $type

For example of implementation check VoIP Phone and/or VoIP SMS modules.


---
The VoIP Number module has been originally developed by Tamer Zoubi under the sponsorship of the MIT Center for Future Civic Media (http://civic.mit.edu).
