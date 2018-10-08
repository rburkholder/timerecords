/* 
 * File:      AppManager.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 22, 2018, 11:52 AM
 */

#include "model/DbVersion.h"
#include "model/KeyValue.h"
#include "model/Company.h"
#include "model/Account.h"
#include "model/Email.h"
#include "model/Login.h"
#include "model/OptInKey.h"
#include "model/Task.h"
#include "model/Team.h"

#include "AppTimeRecords.h"

#include "AppManager.h"

static std::unique_ptr<Wt::WApplication> CreateAppTimeRecords( const Wt::WEnvironment& env ) {
  //
  // Optionally, check the environment and redirect to an error page.
  //
  bool valid( true );
  std::unique_ptr<AppTimeRecords> app;
  if (!valid) {
    app = std::make_unique<AppTimeRecords>(env);
    app->redirect("error.html");
    app->quit();
  } else {
    // usually you will specialize your application class
    app = std::make_unique<AppTimeRecords>(env);
    //
    // Add widgets to app->root() and return the application object.
    //
  }
  return app;
}

AppManager::AppManager( int argc, char** argv, dbo::FixedSqlConnectionPool& pool ) 
: m_server(pool, argv[0])
{ 
    m_server.setServerConfiguration(argc, argv, WTHTTP_CONFIGURATION);
    m_server.addEntryPoint( Wt::EntryPointType::Application, CreateAppTimeRecords);
}

AppManager::~AppManager( ) { }

bool AppManager::InitializeData( dbo::Session& session ) {
  dbo::Transaction transaction( session );
  std::unique_ptr<model::Company> pCompany( new model::Company );
  pCompany->sName = "_unassigned_";
  dbo::ptr<model::Company> pdboCompany = session.add( std::move( pCompany ) );
  
  std::unique_ptr<model::Account> pAccount( new model::Account );
  pAccount->company = pdboCompany;
  pAccount->sFirstName = "_unassigned_";
  pAccount->sLastName = "_unassigned_";
  dbo::ptr<model::Account> pdboAccount = session.add( std::move( pAccount ) );
  return true;
}

bool AppManager::InitializeTables( dbo::FixedSqlConnectionPool& pool ) {
  
  bool bResult( true );
  
  namespace dbo = Wt::Dbo;

  dbo::Session session;

  session.setConnectionPool( pool );

  // will need to perform some sort of version control at some point (version control table?)
  
  session.mapClass<model::DbVersion>( "db_version" );
  session.mapClass<model::KeyValue>( "key_value" );
  session.mapClass<model::Account>( "account" );
  session.mapClass<model::Company>( "company" );
  session.mapClass<model::Email>( "email_address" );
  session.mapClass<model::Login>( "login" );
  session.mapClass<model::OptInKey>( "opt_in_key" );
  session.mapClass<model::AccountTask>( "acount_task" );
  session.mapClass<model::Team>( "team" );
  
  try {
    session.dropTables();
  }
  catch ( Wt::Dbo::Exception& exception ) {
    m_server.log( "info" ) << "dropTables: " << exception.what();
    bResult = false;
  }
  
  
  try {
    std::string sTableCreationSql = session.tableCreationSql();
    std::cerr << sTableCreationSql << std::endl;

    try {
      //session.dropTables();
      session.createTables();
      
      InitializeData( session );
    }
    catch( Wt::Dbo::Exception& exception ) {
      m_server.log( "info" ) << "createTables: " << exception.what();
      bResult = false;
    }
  }
  catch( Wt::Dbo::Exception& exception ) {
    m_server.log( "info" ) << "tableCreationSql: " << exception.what();
    bResult = false;
  }

  return bResult;
}

void AppManager::Start() {
  
  try {

    InitializeTables( m_server.GetConnectionPool() );

    //PopulateDatabase( pool );  // turn on when new file available, but convert to gui import function at some point

    //UserAuth::configureAuth();

    if (m_server.start()) {
      Wt::WServer::waitForShutdown();
      m_server.stop();
    }
  } 
  catch (Wt::WServer::Exception& e) {
    std::cerr << e.what() << std::endl;
  } 
  catch (std::exception &e) {
    std::cerr << "exception: " << e.what() << std::endl;
  }

}