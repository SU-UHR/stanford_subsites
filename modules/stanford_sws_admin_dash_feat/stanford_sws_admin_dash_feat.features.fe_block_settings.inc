<?php
/**
 * @file
 * stanford_sws_admin_dash_feat.features.fe_block_settings.inc
 */

/**
 * Implements hook_default_fe_block_settings().
 */
function stanford_sws_admin_dash_feat_default_fe_block_settings() {
  $export = array();

  $export['version'] = '1.0';

  // Theme independent visibility settings.
  $export['visibility'] = array(
    'menu-menu-admin-dashboard-admin-tasks' => array(
      'delta' => 'menu-admin-dashboard-admin-tasks',
      'module' => 'menu',
    ),
    'views-34e251e5a5cd14871575d573f82d758c' => array(
      'delta' => '34e251e5a5cd14871575d573f82d758c',
      'module' => 'views',
    ),
    'views-fd28bb6192af416e4c1c8610fbac7e19' => array(
      'delta' => 'fd28bb6192af416e4c1c8610fbac7e19',
      'module' => 'views',
    ),
  );

  // Exported block settings for Bartik.
  $theme = array();

  $theme['menu-menu-admin-dashboard-admin-tasks'] = array(
    'module' => 'menu',
    'delta' => 'menu-admin-dashboard-admin-tasks',
    'theme' => 'bartik',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Admin Tasks',
    'cache' => -1,
  );

  $theme['views-34e251e5a5cd14871575d573f82d758c'] = array(
    'module' => 'views',
    'delta' => '34e251e5a5cd14871575d573f82d758c',
    'theme' => 'bartik',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-fd28bb6192af416e4c1c8610fbac7e19'] = array(
    'module' => 'views',
    'delta' => 'fd28bb6192af416e4c1c8610fbac7e19',
    'theme' => 'bartik',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Manage Content',
    'cache' => -1,
  );

  $export['theme']['bartik'] = $theme;

  // Exported block settings for Open Framework.
  $theme = array();

  $theme['menu-menu-admin-dashboard-admin-tasks'] = array(
    'module' => 'menu',
    'delta' => 'menu-admin-dashboard-admin-tasks',
    'theme' => 'open_framework',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Admin Tasks',
    'cache' => -1,
  );

  $theme['views-34e251e5a5cd14871575d573f82d758c'] = array(
    'module' => 'views',
    'delta' => '34e251e5a5cd14871575d573f82d758c',
    'theme' => 'open_framework',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-fd28bb6192af416e4c1c8610fbac7e19'] = array(
    'module' => 'views',
    'delta' => 'fd28bb6192af416e4c1c8610fbac7e19',
    'theme' => 'open_framework',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Manage Content',
    'cache' => -1,
  );

  $export['theme']['open_framework'] = $theme;

  // Exported block settings for Seven.
  $theme = array();

  $theme['menu-menu-admin-dashboard-admin-tasks'] = array(
    'module' => 'menu',
    'delta' => 'menu-admin-dashboard-admin-tasks',
    'theme' => 'seven',
    'status' => '1',
    'weight' => '-10',
    'region' => 'dashboard_sidebar',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Admin Tasks',
    'cache' => -1,
  );

  $theme['views-34e251e5a5cd14871575d573f82d758c'] = array(
    'module' => 'views',
    'delta' => '34e251e5a5cd14871575d573f82d758c',
    'theme' => 'seven',
    'status' => '1',
    'weight' => '-10',
    'region' => 'dashboard_main',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-fd28bb6192af416e4c1c8610fbac7e19'] = array(
    'module' => 'views',
    'delta' => 'fd28bb6192af416e4c1c8610fbac7e19',
    'theme' => 'seven',
    'status' => '1',
    'weight' => '-11',
    'region' => 'dashboard_main',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Manage Content',
    'cache' => -1,
  );

  $export['theme']['seven'] = $theme;

  // Exported block settings for Stanford Basic.
  $theme = array();

  $theme['menu-menu-admin-dashboard-admin-tasks'] = array(
    'module' => 'menu',
    'delta' => 'menu-admin-dashboard-admin-tasks',
    'theme' => 'stanford_basic',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Admin Tasks',
    'cache' => -1,
  );

  $theme['views-34e251e5a5cd14871575d573f82d758c'] = array(
    'module' => 'views',
    'delta' => '34e251e5a5cd14871575d573f82d758c',
    'theme' => 'stanford_basic',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-fd28bb6192af416e4c1c8610fbac7e19'] = array(
    'module' => 'views',
    'delta' => 'fd28bb6192af416e4c1c8610fbac7e19',
    'theme' => 'stanford_basic',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Manage Content',
    'cache' => -1,
  );

  $export['theme']['stanford_basic'] = $theme;

  // Exported block settings for Stanford Framework.
  $theme = array();

  $theme['menu-menu-admin-dashboard-admin-tasks'] = array(
    'module' => 'menu',
    'delta' => 'menu-admin-dashboard-admin-tasks',
    'theme' => 'stanford_framework',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Admin Tasks',
    'cache' => -1,
  );

  $theme['views-34e251e5a5cd14871575d573f82d758c'] = array(
    'module' => 'views',
    'delta' => '34e251e5a5cd14871575d573f82d758c',
    'theme' => 'stanford_framework',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-fd28bb6192af416e4c1c8610fbac7e19'] = array(
    'module' => 'views',
    'delta' => 'fd28bb6192af416e4c1c8610fbac7e19',
    'theme' => 'stanford_framework',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Manage Content',
    'cache' => -1,
  );

  $export['theme']['stanford_framework'] = $theme;

  // Exported block settings for Stanford Jordan.
  $theme = array();

  $theme['menu-menu-admin-dashboard-admin-tasks'] = array(
    'module' => 'menu',
    'delta' => 'menu-admin-dashboard-admin-tasks',
    'theme' => 'stanford_jordan',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Admin Tasks',
    'cache' => -1,
  );

  $theme['views-34e251e5a5cd14871575d573f82d758c'] = array(
    'module' => 'views',
    'delta' => '34e251e5a5cd14871575d573f82d758c',
    'theme' => 'stanford_jordan',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => '',
    'cache' => -1,
  );

  $theme['views-fd28bb6192af416e4c1c8610fbac7e19'] = array(
    'module' => 'views',
    'delta' => 'fd28bb6192af416e4c1c8610fbac7e19',
    'theme' => 'stanford_jordan',
    'status' => 0,
    'weight' => '0',
    'region' => '',
    'custom' => '0',
    'visibility' => '0',
    'pages' => '',
    'title' => 'Manage Content',
    'cache' => -1,
  );

  $export['theme']['stanford_jordan'] = $theme;

  $theme_default = variable_get('theme_default', 'bartik');
  $themes = list_themes();
  foreach ($export['theme'] as $theme_key => $settings) {
    if ($theme_key != $theme_default && empty($themes[$theme_key]->status)) {
      unset($export['theme'][$theme_key]);
    }
  }
  return $export;
}
