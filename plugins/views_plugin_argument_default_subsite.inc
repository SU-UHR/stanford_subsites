<?php
/**
 * @file
 * Contains the subsite argument default plugin.
 */

/**
 * Default argument plugin to provide a subsite as an option.
 */
class views_plugin_argument_default_subsite extends views_plugin_argument_default {
  function option_definition() {
    $options = parent::option_definition();
    $options['subsite'] = array('default' => '0');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
    $form['subsite'] = array(
      '#type' => 'checkbox',
      '#title' => t('Use active subsite'),
      '#default_value' => $this->options['subsite'],
      '#description' => t('Check this box to use whatever is the currently active subsite as the argument default. When no subsite defaults to 0.'),
    );

    // Only do this if using one simple standard form gadget
    $this->check_access($form, 'subsite');
  }

  function convert_options(&$options) {
    if (!isset($options['subsite']) && isset($this->argument->options['default_argument_subsite'])) {
      $options['subsite'] = $this->argument->options['default_argument_subsite'];
    }
  }

  /**
   * Only let users with administer sws permissions set/modify this
   * default plugin.
   */
  function access() {
    return user_access('administer sws');
    //return user_access('administer views');
  }

  function get_argument() {
    // set up variables to make it easier to reference during the argument.
    $view = &$this->view;
    $argument = &$this->argument;
    ob_start();
    global $subsite;

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
