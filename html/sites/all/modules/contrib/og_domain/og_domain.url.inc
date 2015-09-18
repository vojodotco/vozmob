<?php


include_once 'og_domain.module';

/**
 * Rewrites domains in urls.
 *
 * @staticvar array $cache
 * @param string $path
 * @param array $options
 * @param string $original_path
 */
function custom_url_rewrite_outbound(&$path, &$options, $original_path) {
  static $enabled = NULL;
  if($enabled === NULL) {
    $enabled = module_exists('og_domain');
  }
  if($enabled)
    _og_domain_custom_url_rewrite_outbound($path, $options, $original_path);
}

function _og_domain_custom_url_rewrite_outbound(&$path, &$options, $original_path) {
  static $cache = array();

  if(strpos($original_path, 'node/') === 0) {
    $nid = (int) substr($original_path, 5);
    if(!isset($cache[$nid])) {
      $domain = _og_domain_db_lookup_domain($nid);
      $cache[$nid] = NULL;
      if($domain !== FALSE) {
        $cache[$nid] = _og_domain_rewrite_url($options['base_url'], $domain);
      } else {
        $group = _og_domain_get_group($nid);
        if($group !== FALSE) {
          $domain = _og_domain_db_lookup_domain($group);
          $cache[$nid] = _og_domain_rewrite_url($options['base_url'], $domain);
        }
      }
    }
    if($cache[$nid] !== NULL){
      $options['base_url'] = $cache[$nid];
      $options['absolute'] = TRUE;
    }
  }
}