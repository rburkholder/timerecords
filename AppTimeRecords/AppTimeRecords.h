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

#include <map>
#include <functional>

#include <boost/signals2.hpp>

#include <Wt/WEnvironment.h>
#include <Wt/WApplication.h>
#include <Wt/Dbo/backend/Postgres.h>

#include "Server.h"

namespace dbo = Wt::Dbo;

class AppTimeRecords: public Wt::WApplication {
public:
  
  typedef boost::signals2::signal<void (Wt::WContainerWidget*)> signalInternalPathChanged_t;
  typedef signalInternalPathChanged_t::slot_type slotInternalPathChanged_t;
   
  AppTimeRecords( const Wt::WEnvironment& );
  virtual ~AppTimeRecords( );
  
  virtual void initialize( void ); // Initializes the application, post-construction. 
  virtual void finalize( void ); // Finalizes the application, pre-destruction.
  
  void RegisterPath( const std::string& sPath, const slotInternalPathChanged_t& slot );
  void UnRegisterPath( const std::string& sPath );
   
private:
  
  typedef std::function<void(Wt::WContainerWidget*)> fTemplate_t;
  
  typedef std::map<const std::string, const slotInternalPathChanged_t> mapInternalPathChanged_t;
  mapInternalPathChanged_t m_mapInternalPathChanged;  
  
  Server* m_pServer; // object managed by wt
  //dbo::Session m_session;
  
  void AddLink( Wt::WContainerWidget*, const std::string& sClass, const std::string& sPath, const std::string& sAnchor );

  void HandleInternalPathChanged( const std::string& );
  void HandleInternalPathInvalid( const std::string& );
  
  void ShowMainMenu( Wt::WContainerWidget* );

  void HomeRoot( Wt::WContainerWidget* );
  void Home( Wt::WContainerWidget* );
  
  
  void TemplatePage( Wt::WContainerWidget*, fTemplate_t );
};

#endif /* APPTIMERECORDS_H */

