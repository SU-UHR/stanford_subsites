<?php
/**
 * @file
 * stanford_subsites_user_settings.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function stanford_subsites_user_settings_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_stanford_subsite_usr_sub'
  $field_bases['field_stanford_subsite_usr_sub'] = array(
    'active' => 1,
    'cardinality' => -1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_stanford_subsite_usr_sub',
    'foreign keys' => array(
      'node' => array(
        'columns' => array(
          'target_id' => 'nid',
        ),
        'table' => 'node',
      ),
    ),
    'indexes' => array(
      'target_id' => array(
        0 => 'target_id',
      ),
    ),
    'locked' => 0,
    'module' => 'entityreference',
    'settings' => array(
      'handler' => 'base',
      'handler_settings' => array(
        'behaviors' => array(
          'views-select-list' => array(
            'status' => 0,
          ),
        ),
        'sort' => array(
          'direction' => 'ASC',
          'field' => 'body:value',
          'property' => 'title',
          'type' => 'property',
        ),
        'target_bundles' => array(
          'stanford_subsite' => 'stanford_subsite',
        ),
      ),
      'handler_submit' => 'Change handler',
      'target_type' => 'node',
    ),
    'translatable' => 0,
    'type' => 'entityreference',
  );

  return $field_bases;
}
