<?php
/**
 * @file
 * feature_mongo_migrate.features.inc
 */

/**
 * Implements hook_node_info().
 */
function feature_mongo_migrate_node_info() {
  $items = array(
    'mongo_data' => array(
      'name' => t('Mongo Data'),
      'base' => 'node_content',
      'description' => t('Contains data from Mongo DB'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  drupal_alter('node_info', $items);
  return $items;
}
