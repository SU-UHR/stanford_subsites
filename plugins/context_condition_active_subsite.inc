<?php

/**
 * Expose active subsite properties as a context condition.
 */
class context_condition_active_subsite extends context_condition {
  function condition_values() {
    $values = array();

    // Get all subsite nodes
    $query = db_select('node','n')
              ->fields('n', array('nid', 'title'))
              ->condition('type', SUBSITE_CONTENT_TYPE)
              ->execute();

    while($result = $query->fetchAssoc()) {
      $values[$result['nid']] = check_plain($result['title']);
    }

    return $values;
  }

  function execute() {

      // Grab subsites array
      $subsite = _get_active_subsite();
      if(!$subsite) { return; }

      // Loop through contexts with nid value and assert condition met
      foreach ($this->get_contexts($subsite->nid) as $context) {
      //  if(in_array($subsite->nid, $context->conditions['active_subsite']['values'])) {
          $this->condition_met($context, $subsite->nid);
      //  }
      }

    }


}
