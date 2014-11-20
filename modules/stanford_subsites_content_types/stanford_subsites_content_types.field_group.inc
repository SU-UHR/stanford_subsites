<?php
/**
 * @file
 * stanford_subsites_content_types.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function stanford_subsites_content_types_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_subs_theme_options|node|stanford_subsite|form';
  $field_group->group_name = 'group_subs_theme_options';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'stanford_subsite';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Theme options',
    'weight' => '0',
    'children' => array(
      0 => 'field_stanford_subsite_front',
      1 => 'field_stanford_subsite_logo',
      2 => 'field_stanford_subsite_slogan',
      3 => 'field_stanford_subsite_sname',
      4 => 'field_stanford_subsite_theme',
      5 => 'field_stanford_subsite_sub_tags',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'label' => 'Theme options',
      'instance_settings' => array(
        'required_fields' => 1,
        'classes' => 'group-subs-theme-options field-group-fieldset',
        'description' => 'Options to control the sub site\'s look and feel.',
      ),
      'formatter' => 'collapsible',
    ),
  );
  $export['group_subs_theme_options|node|stanford_subsite|form'] = $field_group;

  return $export;
}
