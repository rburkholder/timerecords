/* 
 * File:      Server.h
 * Author:    raymond@burkholder.net
 * copyright: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 22, 2018, 12:30 PM
 */

#ifndef SERVER_H
#define SERVER_H

#include <Wt/WServer.h>
#include <Wt/Dbo/FixedSqlConnectionPool.h>

namespace dbo = Wt::Dbo;

class Server: public Wt::WServer {
public:
  Server(
          dbo::FixedSqlConnectionPool& pool,
          const std::string &wtApplicationPath=std::string(), 
          const std::string &wtConfigurationFile=std::string()
          );
  Server(
          int argc, 
          char *argv[], 
          dbo::FixedSqlConnectionPool& pool,
          const std::string &wtConfigurationFile=std::string()
          );
  virtual ~Server();
  
  dbo::FixedSqlConnectionPool& GetConnectionPool( void );
  
protected:
private:
  dbo::FixedSqlConnectionPool& m_pool;
};

#endif /* SERVER_H */

