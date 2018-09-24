/* 
 * File:      AppManager.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 22, 2018, 11:52 AM
 */

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

void AppManager::Start() {
  
  try {

    //InitializeTables( pool );

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