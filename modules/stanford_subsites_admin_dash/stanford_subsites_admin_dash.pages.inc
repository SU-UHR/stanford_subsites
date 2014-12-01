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

  // ---------------------------------------------------------------------------
  // ---------------------------------------------------------------------------

  // Main top region.
  // ---------------------------

  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_banner');
  $output['main_top']['subsite_banner'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  // Content region.
  // ----------------------------

  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_content');
  $output['content']['manage_content'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_blocks');
  $output['content']['manage_blocks'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_contexts');
  $output['content']['manage_contexts'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  // Sidebar right region.
  // ---------------------------

  // Create new block.
  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_create_new');
  $output['sidebar_second']['new_stuff'] = _block_get_renderable_array(_block_render_blocks(array($block)));

  $block = block_load('stanford_subsites_admin_dash', 'subsites_dashboard_edit_subs');
  $output['sidebar_second']['edit_stuff'] = _block_get_renderable_array(_block_render_blocks(array($block)));


  $output['#theme'] = "page_subsite_dashboard";
  return $output;
}
