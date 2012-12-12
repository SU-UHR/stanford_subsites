<?php
/**
 * @file
 * Contains the php code argument validator plugin.
 */

/**
 * Provide code to validate whether or not an argument is ok.
 *
 * @ingroup views_argument_validate_plugins
 */
class views_plugin_argument_validate_subsite extends views_plugin_argument_validate {
  function option_definition() {
    $options = parent::option_definition();
   // $options['subsite'] = array('default' => '0');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    // $form['subsite'] = array(
    //   '#type' => 'textarea',
    //   '#title' => t('Subsite'),
    //   '#default_value' => $this->options['subsite'],
    //   '#description' => t('Use the active subsite'),
    // );

    // $this->check_access($form, 'subsite');
  }

  /**
   * Only let users with PHP block visibility permissions set/modify this
   * validate plugin.
   */
  function access() {
    return user_access('administer sws');
  }

  // function convert_options(&$options) {
  //   if (!isset($options['subsite']) && isset($this->argument->options['validate_argument_subsite'])) {
  //     $options['subsite'] = $this->argument->options['validate_argument_subsite'];
  //   }
  // }

  function validate_argument($argument) {
    // set up variables to make it easier to reference during the argument.
    $view = &$this->view;
    $handler = &$this->argument;
    $subsite = _get_active_subsite();

    ob_start();
    if(isset($subsite->nid)) {
      $result = $subsite->nid;
    }
    else {
      $result = 0;
    }
    ob_end_clean();
    return $result;
  }
}
