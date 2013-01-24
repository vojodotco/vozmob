Modules in here are hosted on drupal.org, but needed to be patched.  If the path is accepted and rolled upstream, move the module to contrib.

audiorecorderfield:
Changes text of button from "Upload" to "Save Recording".

filefield_sources:
Reversed order of default and custom file sources in the module.  Modified the javascript to display the first custom source by default.
Applied the patch from http://drupal.org/node/1795160

i18n:
Applied some patch from Drupal.org (what issue is this?)

mail2og: Posts received emails to the right organic group (based on "to" address).
* Patched to fix permissions check: http://drupal.org/node/965200

mailsave:
A number of the cleanup email gateway filters have been changed to keep up to date with changes in the emails sent by providers.

messaging:
Only insert footer glue string if footer is not empty. 

notifications:
In notifications_preprocess_message() use module name as notification group and replace underscores with dashes.

og: Enables the creation of multiple groups.
Patches to og_notifications:
* Specify module name when sending message.
* Make default strings empty.
* Modifications to og_notifications_message_alter for consistency with notifications_process_compose()

smsframework:
This has been modified by ekes, and we should think about contributing these back upstream  to the module maintainers.

sms_registration:
* Changed username/password workflow, added logging to catch registration errors.  Moved feedback messages into variables and added admin UI to change them.
* Added hook_init to set up config variables for i18n.