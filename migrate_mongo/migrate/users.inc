<?php

/**
 * @file
 * Class to migrate users from mongo db.
 */

class MigrateMongoUsers extends Migration {
  public function __construct() {
    parent::__construct();

    $con = MongoDBConnection::_getMongoConnection();
    $db = $con->engtest;
    $collection = $db->rows;
    $fields = array(
      '_id' => 'Object ID',
      'uid' => t('User ID'),
      'user_tags' => t('User tags'),
      'issues' => t('Issues'),
      'abuse_flags' => t('Abuse flags'),
      'abuse_count' => t('Abuse Count'),
    );
    $query = array();
    $sort = array(
      '_id' => 1,
    );
    $this->source = new MigrateSourceMongoDB($collection, $query, $fields, $sort);
    // Set destination.
    $this->destination = new MigrateDestinationUser();
    // Set map.
    $source_key = array(
      '_id' => array(
        'type' => 'varchar',
        'length' => 24,
        'not null' => TRUE,
        'description' => 'MongoDB ID field.',
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $source_key, MigrateDestinationUser::getKeySchema());

    //Field Mapping
    $this->addFieldMapping('name', 'uid')
        ->dedupe('users', 'name');
    $this->addFieldMapping('mail', 'uid')
        ->dedupe('users', 'name');
    $this->addFieldMapping('pass', 'uid');
    $this->addFieldMapping('status')
        ->defaultValue(1);
    $this->addFieldMapping('field_user_tags', 'user_tags');
    $this->addFieldMapping('field_issues', 'issues');
    $this->addFieldMapping('field_abuse_flags', 'abuse_flags');
    $this->addFieldMapping('field_abuse_count', 'abuse_count');
  }
}
