<?php
/**
 * @file
 * stanford_subsites_user_settings.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function stanford_subsites_user_settings_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'user-user-field_stanford_subsite_usr_sub'
  $field_instances['user-user-field_stanford_subsite_usr_sub'] = array(
    'bundle' => 'user',
    'default_value' => NULL,
    'deleted' => 0,
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
      'weight' => 9,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Subsites');

  return $field_instances;
}
