/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   Start.cpp
 * Author: rpb
 * 
 * Created on September 22, 2018, 3:45 PM
 */

#include <Wt/WText.h>
#include <Wt/WEvent.h>
#include <Wt/WPushButton.h>

#include "Main.h"

namespace page {

Main::Main(  )
: Wt::WContainerWidget(  )
{ 
  m_btnStart = addWidget( std::make_unique<Wt::WPushButton>("Start" ) );
  
  m_btnStop = addWidget( std::make_unique<Wt::WPushButton>("Stop" ) );
  
  //btnStart->setMargin(10, Wt::::Left | Wt::Right);

  m_textOut = addWidget( std::make_unique<Wt::WText>( "" ) );
  
  m_btnStart->clicked().connect( this, &Main::HandleBtnStart );
  m_btnStop->clicked().connect( this, &Main::HandleBtnStop );
}

Main::~Main( ) { }

void Main::HandleBtnStart() {
  m_textOut->setText( "started" );
}

void Main::HandleBtnStop() {
  m_textOut->setText( "stop" );
}

} // namespace page
