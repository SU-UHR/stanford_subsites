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
    // $options['subsite'] = array('default' => '0');

    return $options;
  }

  function options_form(&$form, &$form_state) {
    parent::options_form($form, $form_state);
  }

  /**
   * Only let users with administer sws permissions set/modify this
   * default plugin.
   */
  function access() {
    return user_access('administer sws');
  }

  function get_argument() {
    // Set up variables to make it easier to reference during the argument.
    $view = &$this->view;
    $argument = &$this->argument;
    ob_start();
    $subsite = _get_active_subsite();

    ob_start();
    if (isset($subsite->nid)) {
      $result = $subsite->nid;
    }
    else {
      $result = 0;
    }
    ob_end_clean();
    return $result;
  }
}
