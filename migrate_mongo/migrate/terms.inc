<?php

/**
 * @file
 * Class to migrate terms from mongo db.
 */

class MigrateMongoTerms extends Migration {
  public function __construct() {
    parent::__construct();

    $con = MongoDBConnection::_getMongoConnection();
    $db = $con->engtest;
    $collection = $db->rows;
    $fields = array(
      '_id' => 'Object ID',
      'title_keywords' => t('Title keywords'),
//      'body_keywords' => t('Body keywords'),
//      'user_tags' => t('User tags'),
//      'issues' => t('Issues'),
//      'abuse_flags' => t('Abuse flags'),
    );
    $query = array();
    $sort = array(
      '_id' => 1,
    );
    $this->source = new MigrateSourceMongoDB($collection, $query, $fields, $sort);
    // Set destination.
    $this->destination = new MigrateDestinationTerm('title_keywords');
    // Set map.
    $source_key = array(
      '_id' => array(
        'type' => 'varchar',
        'length' => 24,
        'not null' => TRUE,
        'description' => 'MongoDB ID field.',
      ),
    );
    $this->map = new MigrateSQLMap($this->machineName, $source_key, MigrateDestinationTerm::getKeySchema());
    $this->addFieldMapping('name', 'title_keywords')
     ->separator(',');
  }

  /**
   * override the prepareRow() method.
   * @param type $row
   */
  public function prepareRow($row) {
//    /parent::prepareRow($row);
    $row->title_keywords = implode(',', $row->title_keywords);
//    $vocabs = taxonomy_vocabulary_get_names();
//    // Create title_keywords terms.
//    $this->_mongoCreateTerm($vocabs['title_keywords'], $row->title_keywords);
}

  /**
   * Method to create the taxonomy term for a given vocabulary.
   * @param type $vocab
   * @param type $term_array
   */
  protected function _mongoCreateTerm($vocab, $term_array) {
    if (is_array($term_array) && !empty($term_array)) {
      foreach ($term_array as $index => $tname) {
       $term_exist = taxonomy_get_term_by_name($tname, $vocab->machine_name);
       if (!$term_exist && !empty($tname)) {
         $term = new stdClass();
         $term->name = $tname;
         $term->vid = $vocab->vid;
         taxonomy_term_save($term);
        }
      }
    }
  }

  /**
   * Override rollback method to delete all terms for vocabs, used in migration.
   * This is done here because terms are not deleted automatically on rollback.
   */
  public function rollback() {
    parent::rollback();
    $my_vocabs_list = array('title_keywords', 'body_keywords', 'user_tags', 'abuse_flags', 'issue');
    $vocabs = taxonomy_vocabulary_get_names();
    foreach ($vocabs as $vname => $varray) {
      if (in_array($vname, $my_vocabs_list)) {
        $taxonomy_tree = taxonomy_get_tree($varray->vid);
        foreach ($taxonomy_tree as $term) {
          taxonomy_term_delete($term->tid);
        }
      }
    }
  }
}
