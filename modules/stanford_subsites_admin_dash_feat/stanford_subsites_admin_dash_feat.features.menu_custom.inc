<?php
/**
 * @file
 * stanford_subsites_admin_dash_feat.features.menu_custom.inc
 */

/**
 * Implements hook_menu_default_menu_custom().
 */
function stanford_subsites_admin_dash_feat_menu_default_menu_custom() {
  $menus = array();

  // Exported menu: menu-admin-dashboard-admin-tasks.
  $menus['menu-admin-dashboard-admin-tasks'] = array(
    'menu_name' => 'menu-admin-dashboard-admin-tasks',
    'title' => 'Admin Dashboard Admin Tasks',
    'description' => 'Common Tasks for Administrators',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Admin Dashboard Admin Tasks');
  t('Common Tasks for Administrators');


  return $menus;
}
