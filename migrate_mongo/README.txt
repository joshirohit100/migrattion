
Module to migrate data from mongodb to drupal

Dependencies
------------------
1. Migrate
2. feature_mongo_migrate (Feature contains content type and some vocabs)
3. MongoClient PHP exetension

Steps
-----------------
1. Enable the module 'Mongo to Drupal'
2. Then first migrate taxonomies (MigrateMongoTerms)
3. Then migrate users (MigrateMongoUsers)
4. Then migrate nodes (MigrateMongoNodes)

This sequence is required as because users and nodes contains terms. So terms should be created first. Nodes contains user info so users should be migrated before nodes.

Assumptions are mentioned in ASSUPMTION.txt

Drush Not Supported
---------------------------
For mongodb to drupal migration, MongoClient PHP extension is required but drush is throwing errors as class 'Class not found' (Don't know why). 
So please use Migration UI to run migration. I have not added the dependency on the 'Migrate UI' module.
