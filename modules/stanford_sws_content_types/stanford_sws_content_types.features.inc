<?php
/**
 * @file
 * stanford_sws_content_types.features.inc
 */

/**
 * Implements hook_node_info().
 */
function stanford_sws_content_types_node_info() {
  $items = array(
    'sub_site' => array(
      'name' => t('Sub Site'),
      'base' => 'node_content',
      'description' => t('The landing page and configuration page for a site within a site. This content type allows content authors to select a new theme, logo, and site name through the content type. Users can then create content that reference sub site nodes in order to have those settings applied to them. '),
      'has_title' => '1',
      'title_label' => t('Page Title'),
      'help' => '',
    ),
  );
  return $items;
}
