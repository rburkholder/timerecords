/* 
 * File:      AppManager.h
 * Author:    raymond@burkholder.net
 * copyright: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 22, 2018, 11:52 AM
 */

#ifndef APPMANAGER_H
#define APPMANAGER_H

#include <Wt/Dbo/FixedSqlConnectionPool.h>
#include <Wt/Dbo/SqlConnection.h>

#include "Server.h"

// http://www.postgresql.org/docs/current/static/functions-net.html

namespace dbo = Wt::Dbo;

class AppManager {
public:
  AppManager( int argc, char** argv, dbo::FixedSqlConnectionPool& pool );
  virtual ~AppManager( );
  void Start();
private:
  
  Server m_server;
  
  bool InitializeData( dbo::Session& );
  bool InitializeTables( dbo::FixedSqlConnectionPool& pool );
  
};

#endif /* APPMANAGER_H */

