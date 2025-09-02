/*
 * File:      main.cpp
 * Project:   AppTimeRecords
 * Author:    raymond@burkholder.net
 * copyright: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 21, 2018, 6:25 PM
 */

// in terminal, in build:
//    cmake --build . --target clean

#include <iostream>

#include <Wt/Dbo/backend/Sqlite3.h>
//#include <Wt/Dbo/backend/Postgres.h>
#include <Wt/Dbo/FixedSqlConnectionPool.h>

#include "AppManager.h"

/*
 * Debian/Ubuntu:
 * sudo su - postgres
 * psql
 * #create role timerecords login password 'tr';
 * #create database timerecords with owner timerecords;
 */

// run application in ./x64
// add the following command line parameters:
//   --docroot=web;/favicon.ico,/resources,/style,/image --http-address=0.0.0.0 --http-port=8082 --config=etc/wt_config.xml

// http://www.webtoolkit.eu/wt/doc/reference/html/InstallationUnix.html
// https://www.webtoolkit.eu/wt/doc/reference/html/overview.html

// cp -r ../libs-build/wt/resources web/

int main( int argc, char** argv ) {

  namespace dbo = Wt::Dbo;

  std::unique_ptr<dbo::SqlConnection> pSqlConnection;

  //std::string sConnection( "host=127.0.0.1 user=timerecords password=tr port=5432 dbname=timerecords" );

  bool bOk( false );
  try {
    //pSqlConnection = std::make_unique<dbo::backend::Postgres>(sConnection);
    pSqlConnection = std::make_unique<dbo::backend::Sqlite3>( "timerecords.db");
    bOk = true;
  }
  catch(...) {
    std::cout << "can not make connection to database" << std::endl;
  }

  if ( bOk ) {

    pSqlConnection->setProperty( "show-queries", "true" );

    dbo::FixedSqlConnectionPool pool( std::move( pSqlConnection ), 4 );

    AppManager manager( argc, argv, pool );

    manager.Start();
  }

  return 0;
}


