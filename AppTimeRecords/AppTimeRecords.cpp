/* 
 * File:      AppTimeRecords.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on September 22, 2018, 12:40 PM
 */

#include "AppTimeRecords.h"

AppTimeRecords::AppTimeRecords( const Wt::WEnvironment& env )
: Wt::WApplication( env ), 
  m_pServer( nullptr )
{ 
  m_pServer = dynamic_cast<Server*>( env.server() );
  
  //m_session.setConnectionPool( m_pServer->GetConnectionPool() );

  //internalPathChanged().connect( this, &AppNodeStar::HandleInternalPathChanged );
  //internalPathInvalid().connect( this, &AppNodeStar::HandleInternalPathInvalid );
}

AppTimeRecords::~AppTimeRecords( ) { }

void AppTimeRecords::initialize() {
}

void AppTimeRecords::finalize() {
}