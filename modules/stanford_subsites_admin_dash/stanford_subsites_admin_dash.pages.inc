<?php
/**
 * @file for page callbacks
 */

/**
 * Callback function for admin/config/subsites/dashboard.
 *
 * A page callback to display the administration dashboard page.
 *
 * @return array
 *   A render array of page content.
 */
function stanford_subsites_admin_dash_dashboard() {
  $output = array();
  $output["#attached"] = array(
    'css' => array(
      drupal_get_path('module', "stanford_subsites_admin_dash") . "/css/subsites.admin.dash.css",
    ),
  );

  // Center content column.
  // $output['content']["wrapper_top"]['#markup'] = "<div class=\"main-column-66\">";
  // $output['content']['manage_content']['#markup'] = "<h2>Manage Content</h2>";
  // $output['content']['manage_content']['#markup'] .= views_embed_view("stanford_subsites_admin_dash_content", "stanford_subsite_admin_dash_content_block");
  // $output['content']['manage_users']['#markup'] = "<h2>Manage Users</h2>";
  // $output['content']['manage_users']['#markup'] .= views_embed_view("stanford_subsites_admin_dash_users", "stanford_subsites_admin_dash_user_block");
  // $output['content']["wrapper_bottom"]['#markup'] = "</div>";



  // // Right sidebar column.
  // $output['sidebar_first']["wrapper_top"]['#markup'] = "<div class=\"sidebar-column-33\">";
  // if (module_exists("search")) {
  //   $block = block_load('search', 'search');
  //   $block->title = t("Search");
  //   $block->region = NULL;
  //   $output['sidebar_first']['search_blox'] = _block_get_renderable_array(_block_render_blocks(array($block)));
  // }

  // $block = block_load('stanford_subsites_admin_dash', 'stanford_subsites_quick_create');
  // $output['sidebar_first']['create_content'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  // $block = block_load('stanford_subsites_admin_dash', 'stanford_subsites_jump_block');
  // $output['sidebar_first']['manage_subsite'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  // $block = block_load('menu', 'menu-admin-dashboard-admin-tasks');
  // $output['sidebar_first']['admin_tasks'] = _block_get_renderable_array(_block_render_blocks(array($block)));
  // $output['sidebar_first']["wrapper_bottom"]['#markup'] = "</div>";

  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------

  // Main top region.
  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_banner');
  $output['main_top']['subsite_banner'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  // Content region.
  $output['content']['manage_content'] = array("#markup" => "<h2>Manage content to go here</h2>");

  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_blocks');
  $output['content']['manage_blocks'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_contexts');
  $output['content']['manage_contexts'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  // Sidebar right region.
  $output['sidebar_second']['new_stuff'] = array("#markup" => "<h2>Create new content menu</h2>");
  $output['sidebar_second']['edit_stuff'] = array("#markup" => "<h2>Edit stuff menu</h2>");

  $output['#theme'] = "page_subsite_dashboard";

  return $output;
}
