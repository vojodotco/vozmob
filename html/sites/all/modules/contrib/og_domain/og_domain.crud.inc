<?php


define('OG_DOMAIN_WITH_NODEOBJECTS', TRUE);
define('OG_DOMAIN_WITHOUT_NODEOBJECTS', FALSE);

/**
 * A little function to help db queries.
 *
 * @param result $res
 * @return array
 */
function db_fetch_all($res) {
  $ret = array();
  while($row = db_fetch_array($res))
    $ret []= $row;
  return $ret;
}

/**
 * Maps an organic group with a domain.
 *
 * @param int $nid
 * @param int $domain
 * @param array $overrides an array of the overrides of $GLOBAL['conf']. Warning, this will be always overwritten!
 */
function _og_domain_do_mapping($nid, $domain, $overrides = array()) {
  if(!is_numeric($domain)) {
    $domain = _og_domain_get_did_by_domain($domain);
  }
  $mappings = db_fetch_all(db_query('SELECT * FROM {og_domain_mapping} WHERE nid = %d OR did = %d',
    $nid, $domain));
  switch(count($mappings)) {
    default:
      db_query('DELETE FROM {og_domain_mapping} WHERE nid = %d OR did = %d',
        $nid, $domain);
    case 0:
      db_query('INSERT INTO {og_domain_mapping}(nid,did,overrides) VALUES(%d, %d, \'%s\')',
        $nid, $domain, serialize($overrides));
      break;
    case 1:
      $m = array_shift($mappings); // !!!
      if($m['nid'] == $nid) {
        db_query('UPDATE {og_domain_mapping} SET did = %d, overrides = \'%s\' WHERE nid = %d',
          $domain, serialize($overrides), $nid);
      } else {
        db_query('UPDATE {og_domain_mapping} SET nid = %d, overrides = \'%s\' WHERE did = %d',
          $nid, serialize($overrides), $domain);
      }
      break;
  }
}

/**
 * Saves the overrides.
 *
 * @param int $nid
 * @param array $overrides
 */
function _og_domain_set_overrides($nid, $overrides) {
  db_query('UPDATE {og_domain_mapping} SET overrides = \'%s\' WHERE nid = %d', serialize($overrides), $nid);
}

/**
 * Retrieve the overrides.
 *
 * @param int $nid
 * @return array
 */
function _og_domain_get_overrides($nid) {
  $override = db_result(db_query('SELECT overrides FROM {og_domain_mapping} WHERE nid = %d', $nid));
  $override = $override === FALSE ? array() : unserialize($override);
  return $override;
}

/**
 * Unmaps a group and a domain by nid.
 *
 * @param int $nid
 */
function _og_domain_unmap_by_nid($nid) {
  db_query('DELETE FROM {og_domain_mapping} WHERE nid = %d', $nid);
}

/**
 * Unmaps a group and a domain by the domain's name.
 *
 * @param int $domain
 */
function _og_domain_unmap_by_domain($domain) {
  if(!is_numeric($domain)) $domain = _og_domain_get_did_by_domain($domain);
  db_query('DELETE FROM {og_domain_mapping} WHERE did = %d', $domain);
}

/**
 * Unmaps a group and a domain by nid and the domain's name.
 *
 * @param int $nid
 * @param int $domain
 */
function _og_domain_unmap_by_nid_and_domain($nid, $domain) {
  if(!is_numeric($domain)) $domain = _og_domain_get_did_by_domain($domain);
  db_query('DELETE FROM {og_domain_mapping} WHERE nid = %d AND did = %d', $nid, $domain);
}

/**
 * Returns all domains.
 *
 * @param int $uid
 * @return array
 */
function _og_domain_get_all_domains($uid = NULL) {
  if($uid === NULL) {
    return db_fetch_all(db_query('SELECT did, domain, uid, name FROM {og_domain_domain} NATURAL JOIN {users} ORDER BY uid, did'));
  } else {
    return db_fetch_all(db_query('SELECT did, domain, uid FROM {og_domain_domain} WHERE uid = %d ORDER BY did', $uid));
  }
}

/**
 * Returns all mappings.
 *
 * Please use OG_DOMAIN_WITH{,OUT}_NODEOBJECT constants for better DX.
 *
 * @param boolean $with_nodeobjects
 * @return array
 */
function _og_domain_get_all($with_nodeobjects = FALSE) {
  $res = db_fetch_all(db_query('SELECT nid, domain FROM {og_domain_mapping} NATURAL JOIN {og_domain_domain} ORDER BY nid DESC'));
  if($with_nodeobjects) {
    foreach($res as $k=>$v) {
      $res[$k]['node'] = node_load($v['nid']);
      unset($res[$k]['nid']);
    }
  }
  return $res;
}

/**
 * Returns a group id of a node.
 *
 * @param int $nid
 * @return int
 */
function _og_domain_get_group($nid) {
  return db_result(db_query('SELECT group_nid FROM {og_ancestry} WHERE nid = %d', $nid));
}

/**
 * Return the $node->status
 *
 * @staticvar array $cache
 * @param int $nid
 * @return bool
 */
function _og_domain_node_is_enabled($nid) {
  static $cache = array();
  if(!isset($cache[$nid])) {
    $node = node_load($nid);
    $cache[$nid] = (bool)$node->status;
  }
  return $cache[$nid];
}

/**
 * Returns TRUE if the domain is enabled.
 *
 * @staticvar array $cache
 * @param string $domain
 * @param bool $strict returns false if domain not found
 * @return bool
 */
function _og_domain_is_enabled($domain, $strict = FALSE) {
  static $cache = array();
  if(!isset($cache[$domain])) {
    $nid = _og_domain_db_lookup_nid($domain);
    $cache[$domain] = $nid === FALSE ?
      variable_get('og_domain_default_value', _og_domain_get_base_url_domain()) == $domain || !$strict:
      _og_domain_node_is_enabled($nid);
  }
  return $cache[$domain];
}

/**
 * Returns a domain id of a domain.
 *
 * @param string $domain
 * @return int
 */
function _og_domain_get_did_by_domain($domain) {
  return (int)db_result(db_query('SELECT did FROM {og_domain_domain} WHERE domain = \'%s\'', $domain));
}

function _og_domain_add_domain($domain, $uid) {
  db_query('INSERT INTO {og_domain_domain}(domain, uid) VALUES(\'%s\', %d)', $domain, $uid);
}

function _og_domain_update_domain($did, $domain, $uid) {
  db_query('UPDATE {og_domain_domain} SET domain = \'%s\', uid = %d WHERE did = %d', $domain, $uid, $did);
}

function _og_domain_delete_domain($did) {
  db_query('DELETE FROM {og_domain_mapping} WHERE did = %d', $did);
  db_query('DELETE FROM {og_domain_domain} WHERE did = %d', $did);
}

function _og_domain_check_user($did, $uid) {
  return db_result(db_query('SELECT uid FROM {og_domain_domain} WHERE did = %d', $did)) == $uid;
}

function _og_domain_get_available_domains($uid, $nid = 0) {
  $ret = array('0' => t('No domain'));
  $nid = (int)$nid;
  $res = db_query('SELECT {og_domain_domain}.did AS did, domain
    FROM {og_domain_domain} LEFT JOIN {og_domain_mapping} ON {og_domain_domain}.did = {og_domain_mapping}.did
    WHERE (nid IS NULL OR nid = %d ) AND uid = %d', $nid, $uid);
  while($row = db_fetch_array($res)) {
    $ret[$row['did']] = $row['domain'];
  }
  return $ret;
}
