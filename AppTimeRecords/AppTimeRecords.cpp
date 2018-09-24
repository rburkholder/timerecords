/* 
 * File:      AppTimeRecords.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on September 22, 2018, 12:40 PM
 */

//#include <Wt/WApplication.h>
//#include <Wt/WLogger.h>
//#include <Wt/WContainerWidget.h>
#include <Wt/WAnchor.h>
//#include <Wt/WText.h>

#include "AppTimeRecords.h"

// https://www.webtoolkit.eu/wt/doc/reference/html/classWt_1_1WApplication.html

AppTimeRecords::AppTimeRecords( const Wt::WEnvironment& env )
: Wt::WApplication( env ), 
  m_pServer( nullptr )
{ 
  m_pServer = dynamic_cast<Server*>( env.server() );
  
  useStyleSheet("style/tr.css");
  
  internalPathChanged().connect( this, &AppTimeRecords::HandleInternalPathChanged );
  internalPathInvalid().connect( this, &AppTimeRecords::HandleInternalPathInvalid );
  
  namespace ph = std::placeholders;
  RegisterPath( "/", std::bind( &AppTimeRecords::HomeRoot, this, ph::_1 ) );
  
  //m_session.setConnectionPool( m_pServer->GetConnectionPool() );

  struct callback {
    void operator()( Wt::WContainerWidget* pcw ) {
      
    }
  };
    
  namespace ph = std::placeholders;
  TemplatePage( root(), [this](Wt::WContainerWidget* pcw){
    //m_pMain = std::make_unique<page::Main>();
    ShowMainMenu( pcw );
  } );
  //TemplatePage( root(), callback() );
}

AppTimeRecords::~AppTimeRecords( ) { }

void AppTimeRecords::initialize() {
  Wt::WApplication::log( "info" ) << "AppTimeRecords::initialize()";
}

void AppTimeRecords::finalize() {
  Wt::WApplication::log( "info" ) << "AppTimeRecords::finalize()";
}

void AppTimeRecords::HandleInternalPathChanged( const std::string& sPath ) {
  root()->clear();
  std::string sMessage;
  sMessage += "HandleInternalPathChanged: ";
  sMessage += sPath;
  mapInternalPathChanged_t::const_iterator iter = m_mapInternalPathChanged.find( sPath );
  if ( m_mapInternalPathChanged.end() != iter ) {
    sMessage += "iter";
    iter->second( root() );
  }
  else {
    // default home page, or error page, and register a default page
    sMessage += "root";
    Home( root() );
  }
  Wt::WApplication::log( "info" ) << sMessage;
}

void AppTimeRecords::HandleInternalPathInvalid( const std::string& s ) {
  Wt::WApplication::log( "warn" ) << "*** HandleInternalPathInvalid: " << s;
}
  
void AppTimeRecords::RegisterPath( const std::string& sPath, const slotInternalPathChanged_t& slot ) {
  mapInternalPathChanged_t::const_iterator iter = m_mapInternalPathChanged.find( sPath );
  if ( m_mapInternalPathChanged.end() != iter ) 
    std::runtime_error( "path exists" );
  m_mapInternalPathChanged.insert( mapInternalPathChanged_t::value_type( sPath, slot ) );
}

void AppTimeRecords::UnRegisterPath( const std::string& sPath ) {
  mapInternalPathChanged_t::const_iterator iter = m_mapInternalPathChanged.find( sPath );
  if ( m_mapInternalPathChanged.end() == iter ) 
    std::runtime_error( "path not found" );
  m_mapInternalPathChanged.erase( iter );
}

void AppTimeRecords::AddLink( Wt::WContainerWidget* pcw, const std::string& sClass, const std::string& sPath, const std::string& sAnchor ) {
  Wt::WContainerWidget* pContainer
    = pcw->addWidget( std::make_unique<Wt::WContainerWidget>() );
  
  pContainer->setStyleClass( sClass );
  
  // https://www.webtoolkit.eu/wt/doc/reference/html/classWt_1_1WAnchor.html
  Wt::WLink link( Wt::LinkType::InternalPath, sPath );
  
  Wt::WAnchor* pAnchor
    = pContainer->addWidget( std::make_unique<Wt::WAnchor>( link, sAnchor ) );
  
  // WApplication::instance()->internalPathChanged().connect(this, &DocsListWidget::onInternalPathChange);
}

void AppTimeRecords::ShowMainMenu( Wt::WContainerWidget* pcw ) {
  
  // still need to show the widget, and there needs to be a click event so when 
  //  logged in we can refresh
  // so devote a page to the login, clean out main menu,
  // but still need an event on when logged in is successful
  //   because nothing else happens on the page
/*  
  if ( m_pAuth->LoggedIn() ) {

    AddLink( pcw, "member", "/show/addresses", "Address List" );
    AddLink( pcw, "member", "/admin/tables/upload", "Upload" );
    
    // <a id="ov7qcp1" 
    //    href="admin/tables/populate/mysql?wtd=jLpA57e4vgIIoYxI" 
    //    class="Wt-rr"><span id="ov7qcp0">Populate Tables: MySQL sourced</span>
    //    </a>
    auto pMenu = new Wt::WContainerWidget( pcw );
    // test against database, and figure out which can be shown, particularily the tables/init one
    pMenu->setList(true); // ==> sub WContainerWidget added as <li> elements
    AddLink( pMenu, "admin", "/admin/tables/init", "Init Tables" );
    AddLink( pMenu, "admin", "/admin/tables/populate/basics", "Populate Tables: Basics" );
    // use the Upload class to do this one:
    AddLink( pMenu, "admin", "/ad min/tables/populate/mysql",  "Populate Tables: MySQL sourced" );
    // use the Upload class to do this one:
    AddLink( pMenu, "admin", "/admin/tables/populate/smcxml", "Populate Tables: SMC XML sourced" );
    
  }
  else {
    
  }
  */
  // sample button code, but now implemented as a link
  //Wt::WPushButton* pBtn = new Wt::WPushButton( "Show Addresses" );
  //pBtn->clicked().connect(this, &AppNodeStar::HandleShowAddresses );
  //pcw->addWidget( pBtn );
  
  pcw->addWidget( std::make_unique<page::Main>() );
  
}

void AppTimeRecords::HomeRoot( Wt::WContainerWidget* pcw ) {
  std::cout << "root home" << std::endl;
  
  namespace ph = std::placeholders;
  TemplatePage( pcw, std::bind( &AppTimeRecords::ShowMainMenu, this, ph::_1 ) );
}

void AppTimeRecords::Home( Wt::WContainerWidget* pcw ) {
  
  namespace ph = std::placeholders;
  TemplatePage( pcw, std::bind( &AppTimeRecords::ShowMainMenu, this, ph::_1 ) );
}

void AppTimeRecords::TemplatePage(Wt::WContainerWidget* pcw, fTemplate_t f) {
  
  std::string sTitle( "Time Records" );
  setTitle( sTitle );
  
  //auto pTitle( new Wt::WText( sTitle ) );
  //pTitle->setStyleClass( "MainTitle" );
  
  //pcw->addWidget( pTitle );
  
    // should show up to the right of the title
  //if ( this->internalPathMatches( "/auth/signin" ) ) {
    // don't show sign in status
  //}
  //else {
//    if ( m_pAuth->LoggedIn() ) {
//      //pcw->addWidget( m_pAuth->NewAuthWidget() );
//      AddLink( pcw, "member", "/auth/signout", "Sign Out" );
//      AddLink( pcw, "member", "/member/home", "Home" );
//    }
//    else {
//      AddLink( pcw, "admin", "/auth/signin", "Sign In" );
//      AddLink( pcw, "default", "/home", "Home" );
//    }
    
//  }

  f( pcw );
}