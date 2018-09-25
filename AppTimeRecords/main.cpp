/* 
 * File:      main.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 21, 2018, 6:25 PM
 */

#include <iostream>

#include <Wt/Dbo/FixedSqlConnectionPool.h>
#include <Wt/Dbo/backend/Postgres.h>

#include "AppManager.h"

/*
 * Debian/Ubuntu:
 * sudo su - postgres
 * create role timerecords login password 'tr';
 * create database timerecords with owner timerecords;
 */

// http://www.webtoolkit.eu/wt/doc/reference/html/InstallationUnix.html
// https://www.webtoolkit.eu/wt/doc/reference/html/overview.html

// cp -r ../libs-build/wt/resources web/

int main( int argc, char** argv ) {
  
  namespace dbo = Wt::Dbo;

  std::unique_ptr<dbo::SqlConnection> pSqlConnection;

  std::string sConnection( "host=127.0.0.1 user=timerecords password=tr port=5432 dbname=timerecords" );

  bool bOk( false );  
  try {
    pSqlConnection = std::make_unique<dbo::backend::Postgres>(sConnection);
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


