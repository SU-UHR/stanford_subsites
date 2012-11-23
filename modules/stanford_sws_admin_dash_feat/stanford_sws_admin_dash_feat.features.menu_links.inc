<?php
/**
 * @file
 * stanford_sws_admin_dash_feat.features.menu_links.inc
 */

/**
 * Implements hook_menu_default_menu_links().
 */
function stanford_sws_admin_dash_feat_menu_default_menu_links() {
  $menu_links = array();

  // Exported menu link: menu-admin-dashboard-admin-tasks:admin/people/create
  $menu_links['menu-admin-dashboard-admin-tasks:admin/people/create'] = array(
    'menu_name' => 'menu-admin-dashboard-admin-tasks',
    'link_path' => 'admin/people/create',
    'router_path' => 'admin/people/create',
    'link_title' => 'New User',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a new user account',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-49',
  );
  // Exported menu link: menu-admin-dashboard-admin-tasks:admin/structure/block/add-menu-block
  $menu_links['menu-admin-dashboard-admin-tasks:admin/structure/block/add-menu-block'] = array(
    'menu_name' => 'menu-admin-dashboard-admin-tasks',
    'link_path' => 'admin/structure/block/add-menu-block',
    'router_path' => 'admin/structure/block/add-menu-block',
    'link_title' => 'New Menu Block',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a new menu block',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-48',
  );
  // Exported menu link: menu-admin-dashboard-admin-tasks:admin/structure/context
  $menu_links['menu-admin-dashboard-admin-tasks:admin/structure/context'] = array(
    'menu_name' => 'menu-admin-dashboard-admin-tasks',
    'link_path' => 'admin/structure/context',
    'router_path' => 'admin/structure/context',
    'link_title' => 'Edit Contexts',
    'options' => array(
      'attributes' => array(
        'title' => 'Create and Edit contexts',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '5',
  );
  // Exported menu link: menu-admin-dashboard-admin-tasks:admin/sws/subsites
  $menu_links['menu-admin-dashboard-admin-tasks:admin/sws/subsites'] = array(
    'menu_name' => 'menu-admin-dashboard-admin-tasks',
    'link_path' => 'admin/sws/subsites',
    'router_path' => 'admin/sws/subsites',
    'link_title' => 'Edit Subsites',
    'options' => array(
      'attributes' => array(
        'title' => '',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '10',
  );
  // Exported menu link: menu-admin-dashboard-admin-tasks:node/add/sub-site
  $menu_links['menu-admin-dashboard-admin-tasks:node/add/sub-site'] = array(
    'menu_name' => 'menu-admin-dashboard-admin-tasks',
    'link_path' => 'node/add/sub-site',
    'router_path' => 'node/add/sub-site',
    'link_title' => 'New Subsite',
    'options' => array(
      'attributes' => array(
        'title' => 'Create a new Sub Site',
      ),
    ),
    'module' => 'menu',
    'hidden' => '0',
    'external' => '0',
    'has_children' => '0',
    'expanded' => '0',
    'weight' => '-50',
  );
  // Translatables
  // Included for use with string extractors like potx.
  t('Edit Contexts');
  t('Edit Subsites');
  t('New Menu Block');
  t('New Subsite');
  t('New User');


  return $menu_links;
}
