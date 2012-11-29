<?php
/**
 * @file
 * stanford_subsites_user_settings.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function stanford_subsites_user_settings_field_default_fields() {
  $fields = array();

  // Exported field: 'user-user-field_stanford_subsite_usr_sub'.
  $fields['user-user-field_stanford_subsite_usr_sub'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
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
      'locked' => '0',
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
            'sub_site' => 'sub_site',
          ),
        ),
        'handler_submit' => 'Change handler',
        'target_type' => 'node',
      ),
      'translatable' => '0',
      'type' => 'entityreference',
    ),
    'field_instance' => array(
      'bundle' => 'user',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'entityreference',
          'settings' => array(
            'link' => FALSE,
          ),
          'type' => 'entityreference_label',
          'weight' => 2,
        ),
      ),
      'entity_type' => 'user',
      'field_name' => 'field_stanford_subsite_usr_sub',
      'label' => 'Subsites',
      'required' => 0,
      'settings' => array(
        'user_register_form' => 1,
      ),
      'widget' => array(
        'active' => 1,
        'module' => 'entityreference',
        'settings' => array(
          'match_operator' => 'CONTAINS',
          'path' => '',
          'size' => 60,
        ),
        'type' => 'entityreference_autocomplete',
        'weight' => '9',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Subsites');

  return $fields;
}
