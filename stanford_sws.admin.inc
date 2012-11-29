<?php
/**
 * @file
 * Stanford Site Within a Site administrative functions
 */

/**
 * Implements hook_form().
 */
function stanford_sws_admin_config_form($form, &$form_state) {

  // If the gotoconf variable is set then show the user the conf variable
  if(isset($form_state['values']['gotoconf'])) {
    $form_state['rebuild'] = true;
    return confirm_form(
      $form,
      t("Are you sure you want to do this?"),
      'admin/config/site-within-site',
      t("Any previously checked and now unchecked content types will have their subsite fields removed from them. This will destroy their subsite data. Click yes to confirm that you wish to proceed."),
      t('Yes, Proceed')
    );
  }

  // Trigger for going to confirmation form
  $form['gotoconf'] = array(
    '#type' => 'hidden',
    '#value' => "true"
  );

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

  // $form['warning'] = array(
  //   '#type' => 'markup',
  //   '#markup' => "<span class=\"error\">" . t("WARNING: Any unchecked content types will have their Site Within A Site fields removed from them. This will delete all subsite data for that content type.") . "</span>",
  // );

  drupal_set_message("WARNING: Any unchecked content types will have their Site Within A Site fields removed from them. This will delete all subsite data for that content type.", 'warning');

  // $form['#action'] = url("admin/config/site-within-site/confirm");
  // $form['#validate'][] = 'stanford_sws_admin_config_form_validate';
  // $form['#submit'][] = 'stanford_sws_admin_config_form_submit';
  return system_settings_form($form);
}

/**
 * Settings form custom validate actions
 * @param $form
 * @param $form_state
 *
 */

function stanford_sws_admin_config_form_validate($form, &$form_state) {

  // Store the values of the submission for later submit hooks
  foreach($form_state['values'] as $k => $v) {
    $form_state['storage'][$k] = $v;
  }

  // If not confirmed then rebuild the form and skip submit
  if(!$form_state['values']['confirm']) {
    $form_state['rebuild'] = TRUE;
  }

}


/**
 * settings form custom submit actions
 * @param $form
 * @param $form_state
 *
 */

function stanford_sws_admin_config_form_submit($form, $form_state) {

  // dont process on a non confirm submit
  if(!$form_state['values']['confirm']) {
    return;
  }

  $values = array_merge($form_state['values'], $form_state['storage']);
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

    // Get all the nids of the disabled content type and update the alias
    $q = db_select('node', "n")
        ->fields("n", array('nid'))
        ->condition("type", $type)
        ->execute();

    $nids = array();
    while($result = $q->fetchAssoc()) {
      $nids[] = $result['nid'];
    }

    // Save current action for new aliases and change it to update and
    // preserve old one.
    $alias_action = variable_get('pathauto_update_action', 0);
    variable_set('pathauto_update_action', PATHAUTO_UPDATE_ACTION_LEAVE);

    // add a bulk update operation
    pathauto_node_update_alias_multiple($nids, 'bulkupdate');

    // Restore original setting
    variable_set('pathauto_update_action', $alias_action);

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
