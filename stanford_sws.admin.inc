<?php
/**
 * @file
 * Stanford Site Within a Site administrative functions
 */

/**
 * Implements hook_form().
 */
function stanford_sws_admin_config_form($form, &$form_state) {

  $form['sws'] = array(
    '#type' => "fieldset",
    '#title' => t('Content Types'),
    '#description' => t("Enabled content types that can be used within a subsite."),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
  );

  $type_names = node_type_get_names();
  $enabled_types = variable_get('sws_content_types', array());

  // Remove subsite as option
  unset($type_names[SUBSITE_CONTENT_TYPE]);


  $form['sws']['sws_content_types'] = array(
    '#title' => t("Check To Enable Content Type"),
    '#type' => 'checkboxes',
    '#options' => $type_names,
    '#default_value' => $enabled_types,
    );

  $form['warning'] = array(
    '#type' => 'markup',
    '#markup' => "<span class=\"error\">" . t("WARNING: Any unchecked content types will have their Site Within A Site fields removed from them. This will delete all subsite data for that content type.") . "</span>",
  );

  $form['#validate'][] = 'stanford_sws_admin_config_form_validate';
  $form['#submit'][] = 'stanford_sws_admin_config_form_submit';
  return system_settings_form($form);
}

/**
 * Settings form custom validate actions
 * @param $form
 * @param $form_state
 *
 */

function stanford_sws_admin_config_form_validate($form, $form_state) {
// Nothing to do here. Please move along
}


/**
 * settings form custom submit actions
 * @param $form
 * @param $form_state
 *
 */

function stanford_sws_admin_config_form_submit($form, $form_state) {

  $values = $form_state['values'];
  $disabled_types = array_filter($values['sws_content_types'], 'give_zero_values');

  // Loop through the disabled content types and remove their field instances
  foreach($disabled_types as $type => $nothing) {

  $ref_instance = field_read_instance('node', SUBSITE_REF_FIELD, $type);
  $tax_instance = field_read_instance('node', SUBSITE_TAGS_FIELD, $type);

    if($ref_instance) {
      $instance = _get_ref_field_instance($type);
      field_delete_instance($instance, FALSE);
    }

    if($tax_instance) {
      $instance = _get_tax_field_instance($type);
      field_delete_instance($instance, FALSE);
    }

  }

  // Remove content types from the list that arent enabled and then
  // store the values of the form
  $filtered = array_filter($values['sws_content_types'], 'remove_zero_values');
  $keys = array_keys($filtered);
  variable_set('sws_content_types', $keys);


  // We now have a list of content types (bundles) that we need to attach an
  // instance of the fields to. Loop through them and attach them
  $ref_field = field_info_field(SUBSITE_TAGS_FIELD);
  $ref_instance = field_read_instance('node', SUBSITE_TAGS_FIELD, 'page');

  foreach($keys as $k => $v) {

  $ref_instance = field_read_instance('node', SUBSITE_REF_FIELD, $v);
  $tax_instance = field_read_instance('node', SUBSITE_TAGS_FIELD, $v);

    if(!$ref_instance) {
      // Create it
      $instance = _get_ref_field_instance($v);
      field_create_instance($instance);
    }

    if(!$tax_instance) {
      // Create it
      $instance = _get_tax_field_instance($v);
      field_create_instance($instance);
    }

  }

  // Clear all the caches
  drupal_flush_all_caches();

}


/**
 * remove_zero_values
 * Helper function to remove items from an assoc array with value == 0
 * @param  $input the input array
 * @return  boolean true if value is valid | false if value is 0
 */

function remove_zero_values($input) {
  if($input === 0 ||
     $input === FALSE ||
     strlen($input) == 0 ||
     $input === "0")
  {
    return FALSE;
  }
  return TRUE;
}


/**
 * give_zero_values
 * Helper function to remove items from an assoc array with value == 0
 * @param  $input the input array
 * @return  boolean true if value is valid | false if value is 0
 */

function give_zero_values($input) {
  if($input === 0 ||
     $input === FALSE ||
     strlen($input) == 0 ||
     $input === "0")
  {
    return TRUE;
  }
  return FALSE;
}
