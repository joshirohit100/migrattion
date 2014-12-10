<?php

/**
 * @file
 * Class return db connection object for mongodb.
 */

class MongoDBConnection {
  public static function _getMongoConnection() {
    $db_string = 'mongodb://acquia:U3aGuRpqiBjtJRAaMF)D4bvXANgkxD@dharma.mongohq.com:10019/engtest';
    $db_string = 'mongodb://localhost:27017';
    return new MongoClient($db_string);
  }
}
