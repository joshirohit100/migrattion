<?php

class BookMarkFlagMigration extends Migration {

  protected $flag;
  const FLAG_LEGACY_FID = 1;
  const FLAG_MACHINE_NAME = 'bookmarks';

  public function __construct($arguments) {
    parent::__construct($arguments);
    $this->description = t('Bookmark Flag Migration');
    $query = $this->sourceDbConnection()
        ->select('flag_content', 'fc')
        ->fields('fc', array('fcid', 'fid', 'content_type', 'content_id', 'uid', 'timestamp'));
    $query->where('(fc.fid=:fid)', array(':fid' => self::FLAG_LEGACY_FID));

    $this->source = new MigrateSourceSQL($query);

    // Get the flag definition
    $this->flag = flag_get_flag(self::FLAG_MACHINE_NAME);

    // Uses Flags as a destination
    $this->destination = new MigrateDestinationFlagSimple($this->flag->fid);

    $this->map = new MigrateSQLMap($this->machineName, array(
      'fcid' => array('type' => 'int',
        'unsigned' => TRUE,
        'not null' => TRUE,
        'description' => 'Source Flag CID',
      )
        ), MigrateDestinationFlagSimple::getKeySchema()
    );


    // Content type
    $this->addFieldMapping('flagging_id', 'fcid');
    $this->addFieldMapping('fid', $this->flag->fid);
    $this->addFieldMapping('entity_type', 'content_type');


    $this->addFieldMapping('content_id', 'content_id');
    //->sourceMigration(array('LearningResource'));

    $this->addFieldMapping('content_type')
    ->defaultValue('node');

    $this->addFieldMapping('uid', 'uid');
    //->sourceMigration(array('PLLUser'));

    $this->addFieldMapping('timestamp', 'timestamp');

    $this->addFieldMapping('sid')->issueGroup(t('DNM'));
  }

  // get source db connection.
  protected function sourceDbConnection() {
    $query = Database::getConnection('default', 'legacy');
    return $query;
  }

}
