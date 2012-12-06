<?php
/**
 * @file
 * Stanford Site Within a Site administrative functions
 */

/**
 * Implements hook_form().
 */
function stanford_subsites_admin_config_form($form, &$form_state) {

  // set the validate hook
  $form["#validate"][] = "stanford_subsites_admin_config_form_process_validate";


  // If the gotoconf variable is set then show the user the conf variable
  if(isset($form_state['values']['gotoconf']) && $form_state['values']['gotoconf'] == "true") {
    $form_state['rebuild'] = true;
    return confirm_form(
      $form,
      t("Are you sure you want to do this?"),
      'admin/config/subsites',
      t("You have marked a content type to be disabled. Any previously checked and now unchecked content types will have their subsite fields removed from them. This will destroy their subsite data and cannot be recovered. Click yes to confirm that you know the consequences and wish to proceed."),
      t('Yes, Proceed')
    );
  }

  // Trigger for going to confirmation form
  $form['gotoconf'] = array(
    '#type' => 'hidden',
    '#value' => "false"
  );

  // Content Types
  // ---------------------------------------------------------------------------
  //

  $form['sws'] = array(
    '#type' => "fieldset",
    '#title' => t('Content Types'),
    '#description' => t("Enabled content types that can be used within a subsite."),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
  );

  $type_names = node_type_get_names();
  $enabled_types = variable_get('stanford_subsite_content_types', array());

  // Remove subsite as option
  unset($type_names[SUBSITE_CONTENT_TYPE]);


  $form['sws']['stanford_subsite_content_types'] = array(
    '#title' => t("Check To Enable Content Type"),
    '#type' => 'checkboxes',
    '#options' => $type_names,
    '#default_value' => $enabled_types,
  );

  // Menu Block Placement
  // ---------------------------------------------------------------------------
  //

  $form['sws_menu'] = array(
    '#type' => "fieldset",
    '#title' => t('Subsite Menu Placement'),
    '#description' => t("Enable/Disable and configure menu creation and block placement."),
    '#collapsed' => FALSE,
    '#collapsible' => FALSE,
  );

  $form['sws_menu']['stanford_subsite_menu_block_enabled'] = array(
    '#title' => t("Check To Enable Menu and Menu Block Creation"),
    '#description' => t("Checking this box will enable menu and menu block creation and placement on the creation of new subsites only."),
    '#type' => 'checkbox',
    '#default_value' => variable_get('stanford_subsite_enabled_menus',false),
  );

  $mbtr = variable_get('stanford_subsite_mbtr', array());

  // We want to list out all enabled themes and provide their regions as options
  $themes = list_themes();
  foreach($themes as $k => $theme) {
    if(!$theme->status) { continue; }

    $regions = $theme->info['regions'];
    $regions['stanford_subsites_dnp'] = "- " . t("Do Not Place") . " -";

    $form["sws_menu"]['stanford_subsite_mbtr_' . $k] = array(
      '#title' => $theme->info['name'],
      '#type' => 'select',
      '#options' => $regions,
      '#default_value' => isset($mbtr[$k]) ? $mbtr[$k] : 'stanford_subsites_dnp',
    );

  }


  // Final bits
  // ---------------------------------------------------------------------------
  //

  drupal_set_message("WARNING: Any unchecked content types will have their Site Within A Site fields removed from them. This will delete all subsite data for that content type.", 'warning');

  return system_settings_form($form);
}

/**
 * Settings form custom validate actions. Handles redirecting the users to
 * confirmation forms, and setting up additional submit handlers
 * @param $form
 * @param $form_state
 */

function stanford_subsites_admin_config_form_process_validate(&$form, &$form_state) {

  // Store the values of the submission for later submit hooks
  foreach($form_state['values'] as $k => $v) {
    $form_state['storage'][$k] = $v;
  }

  // compare enabled content types to the form submission
  $disabled = _has_disabled_types($form_state);

  // There are disabled types and the form hasnt been confirmed
  // Boot the user over to a confirm form
  if($disabled
    && !isset($form_state['values']['confirm'])) {
    form_set_value($form['gotoconf'], "true", $form_state);
    $form_state['rebuild'] = TRUE;
    return;
    // we are going to a cofirm form. End here so that additional submit handles
    // do not get added
  }

  // There are disabled types but the user has confirmed they want to process
  if($disabled && !empty($form_state['values']['confirm'])) {
    $form["#submit"][] = "stanford_subsites_admin_config_form_process_submit";
  }

  // No disabled types lets process and save
  if(!$disabled) {
    $form["#submit"][] = "stanford_subsites_admin_config_form_process_submit";
  }


  // All is good with the content types. Add in the submit hanlder for the menu
  // and block stuff

  $form["#submit"][] = "stanford_subsites_admin_config_form_process_menu_submit";

}


/**
 * settings form custom submit actions for processing the content types
 * @param $form
 * @param $form_state
 *
 */

function stanford_subsites_admin_config_form_process_submit($form, &$form_state) {

  $values = array_merge($form_state['values'], $form_state['storage']);
  $disabled_types = array_filter($values['stanford_subsite_content_types'], '_give_zero_values');

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
    variable_set('pathauto_update_action', 1);

    // add a bulk update operation
    pathauto_node_update_alias_multiple($nids, 'bulkupdate');

    // Restore original setting
    variable_set('pathauto_update_action', $alias_action);

  }

  // Remove content types from the list that arent enabled and then
  // store the values of the form
  $filtered = array_filter($values['stanford_subsite_content_types'], '_remove_zero_values');
  $keys = array_keys($filtered);
  variable_set('stanford_subsite_content_types', $keys);


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
 * submit handler for the configuration page menu and menu block options
 * @param  [type] $form       [description]
 * @param  [type] $form_state [description]
 */
function stanford_subsites_admin_config_form_process_menu_submit($form, &$form_state) {

  $values = array_merge($form_state['values'], $form_state['storage']);

  // Enable / Disable checkbox
  variable_set('stanford_subsite_enabled_menus', $values['stanford_subsite_menu_block_enabled']);


  // Save the theme/region configuration
  $mbtr = array();
  $themes = list_themes();
  foreach($themes as $k => $theme) {
    if(!$theme->status) { continue; }
    $mbtr[$k] = $values['stanford_subsite_mbtr_' . $k];
  }

  variable_set('stanford_subsite_mbtr', $mbtr);

}


// HELPER FUNCTIONS
////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////

/**
 * _remove_zero_values
 * Helper function to remove items from an assoc array with value == 0
 * @param  $input the input array
 * @return  boolean true if value is valid | false if value is 0
 */

function _remove_zero_values($input) {
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
 * _give_zero_values
 * Helper function to remove items from an assoc array with value == 0
 * @param  $input the input array
 * @return  boolean true if value is valid | false if value is 0
 */

function _give_zero_values($input) {
  if($input === 0 ||
     $input === FALSE ||
     strlen($input) == 0 ||
     $input === "0")
  {
    return TRUE;
  }
  return FALSE;
}


/**
 * Checks the form_state array against the saved enabled content types
 * for disabled types
 * @param  array  $form_state | The form state_array
 * @return boolean             false if there are no disabled types
 */
function _has_disabled_types($form_state) {

  $enabled_types = variable_get('stanford_subsite_content_types', array());
  $values = array_merge($form_state['values'], $form_state['storage']);
  $filtered = array_filter($values['stanford_subsite_content_types'], '_remove_zero_values');
  $keys = array_keys($filtered);

  // Loop through current enabled types and check for it being enabled in the
  // submitted values
  foreach($enabled_types as $k => $name) {
    if(!in_array($name, $keys)) {
      return true;
    }
  }

  // Nothing disabled :)
  return false;
}

