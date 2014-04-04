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

  // Grab from global object first.
  if ($subsite) {
    return $subsite;
  }

  // Not found or set yet. Carry on.
  $subsite_node = FALSE;

  // First try from node.
  $a0 = arg(0);
  $a1 = arg(1);

  if ($a0 == "node" && is_numeric($a1)) {

    $node = node_load($a1);
    if (is_object($node)) {
      $subsite_node = _lookup_subsite_reference_by_node($node);
    }

  }


  // If the page being viewed is not a node then check the path.
  if (!$subsite_node) {
    $request_path = request_path();
    $subsite_node = _lookup_subsite_reference_by_path($request_path);
  }

  // Assign the global subsite variable and return the result.
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
  while ($result = $query->fetchAssoc()) {
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
  if ($node->type == SUBSITE_CONTENT_TYPE) {
    return $node;
  }

  // Node is of another type... Get parent.
  if (!isset($node->{SUBSITE_REF_FIELD}[$node->language][0]['target_id']) ||
  !is_numeric($node->{SUBSITE_REF_FIELD}[$node->language][0]['target_id'])) {
    return FALSE;
  }

  // This should always be a subsite content type based on field settings.
  $subsite_node = node_load($node->{SUBSITE_REF_FIELD}[$node->language][0]['target_id']);

  // But just in case someone mucked with them.
  if ($subsite_node->type !== SUBSITE_CONTENT_TYPE) {
    return FALSE;
  }

  return $subsite_node;
}

/**
 * _lookup_subsite_reference_by_path
 * @param  $path - String - The currently viewed url path
 * @return Mixed - A node object of the subsite node or false if none
 */

function _lookup_subsite_reference_by_path($path) {

  // First get all of the subsite paths.
  $subsite_paths = _get_subsite_paths();

  // Check raw string for path... :( needs optimization.
  foreach ($subsite_paths as $nid => $site_path) {
    if (stripos($path, $site_path . "/") !== FALSE) {
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

  // If cache isnt set then we need to generate it.
  if (!$paths) {
    $paths = array();
    $query = db_select('node', 'n')
              ->fields('n', array('nid'))
              ->condition('type', SUBSITE_CONTENT_TYPE)
              ->execute();

    while ($path_string = $query->fetchAssoc()) {
      $paths[$path_string['nid']] = drupal_get_path_alias("node/" . $path_string['nid']);
    }
    cache_set('stanford_subsites_subsite_paths', $paths);
    return $paths;
  }

  // Cached version.
  return $paths->data;
}

/**
 * Generate a term for the subsite vocabulary
 * @param  object $node the subsite node
 * @return Object   the new term object or false if failed
 */
function _insert_subsite_term($node) {
  $term = new stdClass();
  $term->name = $node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'];
  $term->description = "Vocabulary term for " . $node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'] .  " subsite";
  $term->vocabulary_machine_name = SUBSITE_VOCAB;
  $term->format = "filtered_html";

  $vocabulary = taxonomy_vocabulary_machine_name_load(SUBSITE_VOCAB);
  $term->vid = $vocabulary->vid;


  $status = taxonomy_term_save($term, SUBSITE_VOCAB);
  if ($status) {
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

  // New node has been saved but we can still get the old node from cache.
  $old_node = node_load($node->nid);

  // Check if the title of the node changed.
  if ($old_node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'] == $node->{SUBSITE_NAME_FIELD}[$node->language][0]['value']) {
    // They are the same. Nothing to do here.
    return;
  }

  // The title is different. Load up term by term name.
  $terms = taxonomy_get_term_by_name($old_node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'], SUBSITE_VOCAB);

  // Failed to get a term. Lets insert a new one.
  if (!$terms) {
    $term = _insert_subsite_term($node);
    return;
  }

  // Change the name and save it.
  $old_term = array_pop($terms);
  $term = clone($old_term);
  $term->name = $node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'];
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
  $terms = taxonomy_get_term_by_name($node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'], SUBSITE_VOCAB);

  // Failed to get a term. Lets insert a new one.
  if (!$terms) {
    return FALSE;
  }

  return array_pop($terms);
}

/**
 * @param  $bundle  The bundle this instance belongs to
 * @return  Array - an array describing the instance of the reference field
 */

function _get_ref_field_instance($bundle) {

  if (!$bundle) {
    return FALSE;
  }

  $ret = array();
  $ret['entity_type'] = "node";
  $ret['bundle'] = $bundle;
  $ret['field_name'] = SUBSITE_REF_FIELD;
  $ret['label'] = t('Subsite');
  $ret['widget']['type'] = "options_select";
  $ret['display']['default']['type'] = "hidden";
  $ret['display']['teaser']['type'] = "hidden";

  return $ret;
}


/**
 * @param  $bundle  The bundle this instance belongs to
 * @return  Array - an array describing the instance of the reference field
 */

function _get_tax_field_instance($bundle) {

  if (!$bundle) {
    return FALSE;
  }

  $ret = array();
  $ret['entity_type'] = "node";
  $ret['bundle'] = $bundle;
  $ret['field_name'] = SUBSITE_TAGS_FIELD;
  $ret['label'] = t('Subsite Tags');
  $ret['widget']['type'] = "taxonomy_autocomplete";
  $ret['widget']['settings']['size'] = 60;
  $ret['widget']['settings']['autocomplete_path'] = "taxonomy/autocomplete";
  $ret['display']['default']['type'] = "hidden";
  $ret['display']['teaser']['type'] = "hidden";

  return $ret;
}

/**
 * _set_subsite_workingspace
 * Sets the active working space for subsites. Right now only sets the default
 * subsite on node/add
 * @param  $nid  The nid of the new active subsite for the working space
 */

function _set_subsite_workingspace($nid) {

  // Set it
  $lifetime = time() + (60 * 60 * 24 * 7); // One week lifetime
  setcookie('stanford_subsite_workspace', $nid, $lifetime, "/"); // <--need path

}

/**
 * Removes the active subsite working space
 * @return [type] [description]
 */

function _clear_subsite_workingspace() {
  $lifetime = time() - (60 * 60 * 24 * 7); // One week lifetime
  setcookie('stanford_subsite_workspace', 0, $lifetime, "/"); // <--need path
}


/**
 * _get_subsite_workingspace
 * Gets the active working space for subsites. \
 * @return  $nid  The nid of the active subsite for the working space or false
 */

function _get_subsite_workingspace() {

  // If a cookie is available.
  if (isset($_COOKIE['stanford_subsite_workspace']) &&
    is_numeric($_COOKIE['stanford_subsite_workspace'])) {
    return check_plain($_COOKIE['stanford_subsite_workspace']);
  }

  // Not available.
  return FALSE;
}

/**
 * Creates and places a new menu and menu block specifically for this subsite
 * In the new menu a 'home' link is created to the subsite
 * menu block theme/region placement is controlled by the settings page
 * Tasks:
 *  1. Create menu
 *  2. Add subsite node as a link
 *  3. Create menu block from new menu
 *  4. Place menu block via context into region
 *
 * @param  object $node the newly created subsite node (node_insert hook)
 * @return array | menu => the menu, menu_block => the menu block object
 */
function _create_subsite_menu_and_menublock($node) {

  // Create menu ---------------------------------------------------------------

  $menu_name = _get_subsite_menu_name($node);

  $menu = array(
    'menu_name' => $menu_name,
    'title' => t('Subsite Menu') . ": " . substr($node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'], 0, 64),
    'description' => t("Menu for all of this subsites links"),
  );

  // Save it.
  menu_save($menu);

  // Create menu link ----------------------------------------------------------

  // Add a link to this subsite in the new menu.
  $menu_link = array(
    "link_path" => drupal_get_normal_path('node/'.$node->nid),
    "link_title" => t("Home"),
    "menu_name" => $menu_name,
  );

  // Save it!
  menu_link_save($menu_link);

  // Let the user know with a nice message.
  drupal_set_message("A Menu for this subsite was successfully created. " . l("Edit the menu here »", "admin/structure/menu/manage/".$menu_name));

  // Create menu block ---------------------------------------------------------

  // Now create a menu block and place it.
  $menu_block = array();
  $block_ids = variable_get('menu_block_ids', array());
  $delta = empty($block_ids) ? 1 : max($block_ids) + 1;
  // Save the new array of blocks IDs.
  $block_ids[] = $delta;
  variable_set('menu_block_ids', $block_ids);

  $menu_block['delta'] = $delta;
  $menu_block['module'] = "menu_block";
  $menu_block['delta'] = $delta;
  $menu_block['title'] = "<none>";
  $menu_block['display_options'] = "advanced";
  $menu_block['title_link'] = 0;
  $menu_block['admin_title'] = t('Subsite Menu Block: ') . $menu_name;
  $menu_block['menu_name'] = $menu_name;
  $menu_block['level'] = 1;
  $menu_block['follow'] = 0;
  $menu_block['follow_parent'] = "active";
  $menu_block['depth'] = "1";
  $menu_block['expanded'] = 0;
  $menu_block['sort'] = 0;
  $menu_block['parent_mlid'] = $menu_name . ":0";
  $menu_block['regions'] = array();
  $menu_block['visibility'] = "0";
  $menu_block['pages'] = "";
  $menu_block['roles'] = array();
  $menu_block['custom'] = "0";
  $menu_block['types'] = array();
  $menu_block['visibility__active_tab'] = "edit-path";
  $menu_block['parent'] = $menu_name . ":0";

  menu_block_block_save($delta, $menu_block);

  // Run the normal new block submission
  // (borrowed from block_add_block_form_submit).
  $query = db_insert('block')->fields(array(
    'visibility',
    'pages',
    'custom',
    'title',
    'module',
    'theme',
    'region',
    'status',
    'weight',
    'delta',
    'cache'
  ));

  foreach (list_themes() as $key => $theme) {
    if ($theme->status) {
      $region = !empty($menu_block['regions'][$theme->name]) ? $menu_block['regions'][$theme->name] : BLOCK_REGION_NONE;
      $query->values(array(
        'visibility' => (int) $menu_block['visibility'],
        'pages' => trim($menu_block['pages']),
        'custom' => (int) $menu_block['custom'],
        'title' => $menu_block['title'],
        'module' => $menu_block['module'],
        'theme' => $theme->name,
        'region' => ($region == BLOCK_REGION_NONE ? '' : $region),
        'status' => 0,
        'status' => (int) ($region != BLOCK_REGION_NONE),
        'weight' => 0,
        'delta' => $delta,
        'cache' => DRUPAL_NO_CACHE,
      ));
    }
  }
  $query->execute();

  $query = db_insert('block_role')->fields(array('rid', 'module', 'delta'));
  foreach (array_filter($menu_block['roles']) as $rid) {
    $query->values(array(
      'rid' => $rid,
      'module' => $menu_block['module'],
      'delta' => $delta,
    ));
  }
  $query->execute();

  drupal_set_message(t('The Menu block has been created.'));

  return array(
    'menu' => $menu,
    'menu_block' => $menu_block,
  );

}
/**
 * Enable the menu for use on all subsite enabled content types
 * @param  $menu - a fully loaded menu object
 *
 */
function _enable_menu_for_subsite_content_types($menu) {

  // Get all enabled content types from the settings form array.
  $enabled_types = variable_get('stanford_subsite_content_types', array());

  // Loop through the enabled types and add the new menu to their settings array.
  foreach ($enabled_types as $k => $type) {
    $opts = variable_get('menu_options_' . $type, array('main-menu'));
    $opts[] = $menu['menu_name'];
    variable_set('menu_options_' . $type, $opts);
  }

  // Also do subsite content types by default...
  $opts = variable_get('menu_options_' . SUBSITE_CONTENT_TYPE, array('main-menu'));
  $opts[] = $menu['menu_name'];
  variable_set('menu_options_' . SUBSITE_CONTENT_TYPE, $opts);

}


/**
 * Create subsite context
 * @param   $node the fully saved and/or loaded subsite node object
 * @param   $args a misc array of arguments to pass in
 *           menu => (optional) the menu associated with the subsite
 *           menu_block => (optional) the menu_block associated with the subsite
 */

function _create_subsite_context($node, $args) {

  $menu = isset($args['menu']) ? $args['menu'] : FALSE;
  $menu_block = isset($args['menu_block']) ? $args['menu_block'] : FALSE;
  $delta = isset($args['menu_block']) ? $menu_block['delta'] : 0;

  // We can cheat here a bit and re-use the menu name function.
  $context_name = _get_subsite_menu_name($node);

  // Find out what region we are suspposed to be placing the menu block in by
  // getting the theme from the subsite node and comparing it to the subsite
  // configuration settings.

  $the_theme = variable_get('theme_default');
  $theme_region = FALSE;

  if (isset($node->{SUBSITE_THEME_FIELD}[$node->language][0]['value']) && $node->{SUBSITE_THEME_FIELD}[$node->language][0]['value'] !== "default") {
    $the_theme = $node->{SUBSITE_THEME_FIELD}[$node->language][0]['value'];
  }

  // Settings from admin/config/subsites/.
  $settings = variable_get('stanford_subsite_mbtr', array());

  if (isset($settings[$the_theme]) && $settings[$the_theme] !== "stanford_subsites_dnp") {
    $theme_region = $settings[$the_theme];
  }


  $context = new stdClass();
  $context->name = $context_name;
  $context->description = "Subsite Context for " . substr($node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'], 0, 210);
  $context->tag = "Stanford Subsites";
  $context->conditions = array(
    'active_subsite' => array(
      'values' => array(
        $node->nid => $node->nid,
      ),
    ),
  );

  if ($theme_region) {
    $context->reactions = array(
      'block' => array(
        'blocks' => array(
          "menu_block-" . $delta => array(
            'module' => "menu_block",
            'delta' => $delta,
            'region' => $theme_region,
            'weight' => -10,
          ),
        ),
      ),
    );
  }
  $context->condition_mode = 0;
  $context->table = "context";
  $context->type = "Normal";
  $context->export_type = 1;

  context_save($context);
  cache_clear_all();

  drupal_set_message("A subsite context was created for you. " . l(t("Edit it here") . " »", "admin/structure/context/list/" . $context_name . "/edit"));

}

/**
 * Generates the machine name for the drupal menu for a subsite node
 * @param  $node A subsite node
 * @return string | The machine name of the menu for the subsite
 */
function _get_subsite_menu_name($node) {
  $filter = array(' ' => '-', '/' => '-', '[' => '-', ']' => '-');
  $menu_name = strtolower(drupal_clean_css_identifier($node->{SUBSITE_NAME_FIELD}[$node->language][0]['value'], $filter));

  // Max length of menu name is 32 chars.
  $menu_name = substr($menu_name, 0, 32);

  return $menu_name;
}
