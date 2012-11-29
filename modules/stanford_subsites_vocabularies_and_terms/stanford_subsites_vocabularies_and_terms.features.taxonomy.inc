<?php
/**
 * @file
 * sws_vocabularies_and_terms.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function stanford_subsites_vocabularies_and_terms_taxonomy_default_vocabularies() {
  return array(
    'sws_sub_sites' => array(
      'name' => 'Subsites',
      'machine_name' => 'sws_sub_sites',
      'description' => 'Subsites Vocabulary',
      'hierarchy' => '0',
      'module' => 'taxonomy',
      'weight' => '0',
      'rdf_mapping' => array(
        'rdftype' => array(
          0 => 'skos:ConceptScheme',
        ),
        'name' => array(
          'predicates' => array(
            0 => 'dc:title',
          ),
        ),
        'description' => array(
          'predicates' => array(
            0 => 'rdfs:comment',
          ),
        ),
      ),
    ),
  );
}
