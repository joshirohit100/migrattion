<?php

/*
 * Implementation of hook_migrate_api().
 */
function migrate_mongo_migrate_api() {
  $api = array(
    'api' => 2,
    'migrations' => array(
      'MigrateMongoTerms' => array('class_name' => 'MigrateMongoTerms'),
      'MigrateMongoUsers' => array('class_name' => 'MigrateMongoUsers'),
      'MigrateMongoNodes' => array('class_name' => 'MigrateMongoNodes'),
    )
  );
  return $api;
}
