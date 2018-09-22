/* 
 * File:      AppTimeRecords.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 22, 2018, 12:40 PM
 */

#ifndef APPTIMERECORDS_H
#define APPTIMERECORDS_H

#include <Wt/WEnvironment.h>
#include <Wt/WApplication.h>
#include <Wt/Dbo/backend/Postgres.h>

#include "Server.h"

namespace dbo = Wt::Dbo;

class AppTimeRecords: public Wt::WApplication {
public:
   
  AppTimeRecords( const Wt::WEnvironment& );
  virtual ~AppTimeRecords( );
  
  virtual void initialize( void ); // Initializes the application, post-construction. 
  virtual void finalize( void ); // Finalizes the application, pre-destruction.
   
private:
  
  Server* m_pServer; // object managed by wt
  //dbo::Session m_session;

};

#endif /* APPTIMERECORDS_H */

