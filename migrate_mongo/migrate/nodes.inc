<?php

/**
 * @file
 * Class to migrate nodes from mongo db.
 */

class MigrateMongoNodes extends Migration {

  public function __construct() {
    parent::__construct();

    $con = MongoDBConnection::_getMongoConnection();
    $db = $con->engtest;
    $collection = $db->rows;
    $fields = array(
      '_id' => 'Object ID',
      'title' => 'Node title',
      'uid' => 'Author ID',
      'body' => 'body',
      'created' => 'Node creation timestamp',
      'petition_status' => 'Petition status',
      'response_status' => 'response status',
      'published' => 'Node status',
      'reached_public' => 'Timestamp when available to public',
      'reached_ready' => 'Timestamp when ready',
      'signature_count' => 'Total signatures',
      'review_timeframe' => 'Review timeframe duration',
      'response_signatures' => 'Response signature',
      'public_signatures' => 'Public Signature',
      'nice_url' => 'Nice url',
      'short_url' => 'Short url',
      'title_keywords' => 'Title keywords',
      'body_keywords' => 'Body Keywords',
    );
    $query = array();
    $sort = array(
      '_id' => 1,
    );

    // Set the source.
    $this->source = new MigrateSourceMongoDB($collection, $query, $fields, $sort);
    // Set destination.
    $this->destination = new MigrateDestinationNode('mongo_data');

    // Set source map key.
    $source_key = array(
      '_id' => array(
        'type' => 'varchar',
        'length' => 24,
        'not null' => TRUE,
        'description' => 'MongoDB ID field.',
      ),
    );
    // Set map.
    $this->map = new MigrateSQLMap($this->machineName, $source_key, MigrateDestinationNode::getKeySchema());

    $this->addSimpleMappings(array('title', 'body', 'created', 'uid'));
    $this->addFieldMapping('field_petition_status', 'petition_status');
    $this->addFieldMapping('field_response_status', 'response_status');
    $this->addFieldMapping('field_reached_public', 'reached_public');
    $this->addFieldMapping('field_reached_ready', 'reached_ready');
    $this->addFieldMapping('field_signature_count', 'signature_count');
    $this->addFieldMapping('field_review_timeframe', 'review_timeframe');
    $this->addFieldMapping('field_response_signatures', 'response_signatures');
    $this->addFieldMapping('field_public_signatures', 'public_signatures');
    $this->addFieldMapping('field_nice_url', 'nice_url');
    $this->addFieldMapping('field_short_url', 'short_url');
    $this->addFieldMapping('status', 'published');
    $this->addFieldMapping('field_title_keywords', 'title_keywords');
    $this->addFieldMapping('field_body_keywords', 'body_keywords');
  }

  /**
   * Override prepare() method.
   * @param type $entity
   * @param stdClass $row
   */
  public function prepare($entity, stdClass $row) {
    $mongo_id = (array) $row->_id;
    $destination_uid = $this->handleSourceMigration('MigrateMongoUsers', $mongo_id['$id']);
    $entity->uid = $destination_uid;
  }
}


