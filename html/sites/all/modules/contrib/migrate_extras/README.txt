The Migrate Extras module provides extensions to Migrate (http://drupal.org/project/migrate) 
to support various contributed modules. The ideal place to implement migration support 
for a contributed module is in that module. That way, the migration support is always 
self-consistent with the current module implementation - it's not practical for the 
migrate_extras module to keep up with changes to all other contrib modules. Support 
for contributed modules may be added to migrate_extras for two reasons - if the module's 
maintainer does not accept a patch providing migration support, or as an intermediate
step before submitting such a patch to the other module.

In cases where modules supported by migrate_extras end up implementing the support
themselves, you could at least temporarily end up with redundant implementations.
The extra implementation may be disabled at admin/content/migrate/configure.

The following modules are currently supported in Migrate Extras on Drupal 6:

Content Taxonomy
Date
Embedded Media Field
Flag
Formatted Number
Nodewords
Organic Groups
Page Title
Pathauto
Phone Number (cck_phone)
Privatemsg
Rules
User Relationships
UUID
Voting API

Compatibility
-------------
This release of Migrate Extras requires Migrate V2.4-beta1 or later.

Maintainers
-----------
Frank Carey http://drupal.org/user/112063
Mike Ryan - http://drupal.org/user/4420
Moshe Weitzman - http://drupal.org/user/23
