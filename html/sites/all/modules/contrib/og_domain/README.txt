=============================
Organic Groups domain support
=============================

--------------
Before install
--------------

Make sure that you don't have any module which is using
custom_url_rewrite_outbound().
There is a short script to determine (execute it from the
drupal root):
# grep -rin 'function custom_url_rewrite_outbound(' sites/ && echo 'incompatible' || echo 'compatible'

If this small snippet returns 'incompatible', check which
module defines it, and make sure the module is not enabled
and the file, which holds the function definition will not
be loaded (eg.: from settings.php).

------------
Installation
------------

The module needs to have the og_domain.url.inc file loaded before
any link gets outputted. The easiest way to accomplish that is
to include it from settings.php (which is loaded in the first step
of the bootstrap, so it gets loaded before anything).

Put the case that you installed the module under sites/all. In
this case, you have to add the following line to the end of
your settings.php:

include './sites/all/modules/og_domain/og_domain.url.inc';
