<?php
function phptemplate_preprocess_page(&$vars) {

  // Load custom links menu into a variable, the name is always prefixed with 'menu-'
  $vars['menu_vozmobnet'] = menu_navigation_links('menu-vozmobnet');

}
