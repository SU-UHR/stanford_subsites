<?php

/**
 * @file
 * A collection of private helper functions for use with the stanford_subsites.module
 */


/**
 * Gets the active subsite node based on node page and on path
 * @return $node [subsite]  or   false
 */
function _get_active_subsite() {
  global $subsite;

  // Grab from global object first
  if($subsite) {
    return $subsite;
  }

  // Not found or set yet. Carry on.
  $subsite_node = FALSE;

  // First try from node
  $a0 = arg(0);
  $a1 = arg(1);

  if($a0 == "node" && is_numeric($a1)) {
    $node = node_load($a1);
    $subsite_node = _lookup_subsite_reference_by_node($node);
  }


  // If the page being viewed is not a node then check the path
  if(!$subsite_node) {
    $request_path = request_path();
    $subsite_node = _lookup_subsite_reference_by_path($request_path);
  }

  // Assign the global subsite variable and return the result
  $subsite = $subsite_node;
  return $subsite_node;
}

/**
 * Get all subsite nodes.
 * @return  array() an array of subsite nodes
 */

function _get_subsite_nodes() {
  $query = db_select("node", "n")
            ->fields("n", array("nid"))
            ->condition("type", SUBSITE_CONTENT_TYPE)
            ->orderBy('title')
            ->execute();

  $nids = array();
  while($result = $query->fetchAssoc()) {
    $nids[] = $result['nid'];
  }

  return node_load_multiple($nids);
}

/**
 * _lookup_subsite_reference_by_node()
 * @param $node - The currently being viewed node object
 * @return  boolen - True if this node has a subsite / False if none
 */

function _lookup_subsite_reference_by_node($node) {

  // If the node that is being viewed is the subsite node then just return it!
  if($node->type == SUBSITE_CONTENT_TYPE) { return $node; }

  // Node is of another type... Get parent
  if(!isset($node->{SUBSITE_REF_FIELD}[$node->language][0]['target_id']) ||
  !is_numeric($node->{SUBSITE_REF_FIELD}[$node->language][0]['target_id']))
  {
    return false;
  } // no reference

  // This should always be a subsite content type based on field settings
  $subsite_node = node_load($node->{SUBSITE_REF_FIELD}[$node->language][0]['target_id']);

  // But just in case someone mucked with them
  if($subsite_node->type !== SUBSITE_CONTENT_TYPE) {
    return false;
  }

  return $subsite_node;
}

/**
 * _lookup_subsite_reference_by_path
 * @param  $path - String - The currently viewed url path
 * @return Mixed - A node object of the subsite node or false if none
 */

function _lookup_subsite_reference_by_path($path) {

  // First get all of the subsite paths
  $subsite_paths = _get_subsite_paths();

  // Check raw string for path... :( needs optimization
  foreach($subsite_paths as $nid => $site_path) {
    if(stripos($path, $site_path) !== FALSE) {
      return node_load($nid);
    }
  }

  return FALSE;
}

/**
 *_get_subsite_paths
 * @return  Array | an array of subsite paths
 */
function _get_subsite_paths() {

  $paths = cache_get('stanford_subsites_subsite_paths');

  // If cache isnt set then we need to generate it
  if(!$paths) {
    $paths = array();
    $query = db_select('node','n')
              ->fields('n', array('nid'))
              ->condition('type', SUBSITE_CONTENT_TYPE)
              ->execute();

    while($path_string = $query->fetchAssoc()) {
      $paths[$path_string['nid']] = drupal_get_path_alias("node/" . $path_string['nid']);
    }
    cache_set('stanford_subsites_subsite_paths', $paths);
    return $paths;
  }

  // Cached version
  return $paths->data;
}

/**
 * Generate a term for the subsite vocabulary
 * @param  object $node the subsite node
 * @return Object   the new term object or false if failed
 */
function _insert_subsite_term($node) {
  $term = new stdClass();
  $term->name = $node->title;
  $term->description = "Vocabulary term for " . $node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'] .  " subsite";
  $term->vocabulary_machine_name = SUBSITE_VOCAB;
  $term->format = "filtered_html";

  $vocabulary = taxonomy_vocabulary_machine_name_load(SUBSITE_VOCAB);
  $term->vid = $vocabulary->vid;


  $status = taxonomy_term_save($term, SUBSITE_VOCAB);
  if($status) {
    return $term;
  }
  else {
    drupal_set_message("FAILED TO INSERT NEW SUBSITE TERM", 'error');
  }

}

/**
 * Looks to update the term name in the subsite vocabulary if the node title
 * Changes on update
 * @param  object $node The original Node Object
 */
function _update_subsite_node_term_name($node) {

  // New node has been saved but we can still get the old node from cache
  $old_node = node_load($node->nid);

  // Check if the title of the node changed
  if($old_node->title == $node->title) {
    return; // they are the same. Nothing to do here.
  }

  // The title is different. Load up term by term name
  $terms = taxonomy_get_term_by_name($old_node->title, SUBSITE_VOCAB);

  // Failed to get a term. Lets insert a new one
  if(!$terms) {
    $term = _insert_subsite_term($node);
    return;
  }

  // Change the name and save it
  $old_term = array_pop($terms);
  $term = clone($old_term);
  $term->name = $node->title;
  $term->original = $old_term;

  $term = taxonomy_term_save($term, SUBSITE_VOCAB);
  return $term;
}

/**
 * Returns the term object associated with a subsite node
 * @param  $node  The subsite node object
 * @return  object | The term object or false
 */
function _get_subsite_term($node) {

  // The title is different. Load up term by term name
  $terms = taxonomy_get_term_by_name($node->title, SUBSITE_VOCAB);

  // Failed to get a term. Lets insert a new one
  if(!$terms) {
    return FALSE;
  }

  return array_pop($terms);
}

/**
 * @param  $bundle  The bundle this instance belongs to
 * @return  Array - an array describing the instance of the reference field
 */

function _get_ref_field_instance($bundle) {

  if(!$bundle) { return false; }

  $ret = array();
  $ret['entity_type'] = "node";
  $ret['bundle'] = $bundle;
  $ret['field_name'] = SUBSITE_REF_FIELD;
  $ret['label'] = t('Subsite');
  $ret['widget']['type'] = "options_select";

  return $ret;
}


/**
 * @param  $bundle  The bundle this instance belongs to
 * @return  Array - an array describing the instance of the reference field
 */

function _get_tax_field_instance($bundle) {

  if(!$bundle) { return false; }

  $ret = array();
  $ret['entity_type'] = "node";
  $ret['bundle'] = $bundle;

  $ret['field_name'] = SUBSITE_TAGS_FIELD;
  $ret['label'] = t('Subsite Tags');
  $ret['widget']['type'] = "taxonomy_autocomplete";
  $ret['widget']['settings']['size'] = 60;
  $ret['widget']['settings']['autocomplete_path'] = "taxonomy/autocomplete";

  return $ret;
}

/**
 * _set_subsite_workingspace
 * Sets the active working space for subsites. Right now only sets the default
 * subsite on node/add
 * @param  $nid  The nid of the new active subsite for the working space
 */

function _set_subsite_workingspace($nid) {
  $lifetime = time() + (60 * 60 * 24 * 7); // One week lifetime
  setcookie('sws_subsite_workspace', $nid, $lifetime);
}

/**
 * _get_subsite_workingspace
 * Gets the active working space for subsites. \
 * @return  $nid  The nid of the active subsite for the working space or false
 */

function _get_subsite_workingspace() {

  // if a cookie is available
  if(isset($_COOKIE['sws_subsite_workspace']) &&
    is_numeric($_COOKIE['sws_subsite_workspace'])) {
    return check_plain($_COOKIE['sws_subsite_workspace']);
  }

  // Not available
  return FALSE;
}




