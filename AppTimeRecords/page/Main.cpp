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

#include <Wt/WPushButton.h>
#include <Wt/WText.h>

#include "Main.h"

namespace page {

Main::Main( Wt::WContainerWidget* pcw ) { 
  
  Wt::WPushButton *btnStart 
    = pcw->addWidget( std::make_unique<Wt::WPushButton>("Start" ) );
  
  Wt::WPushButton *btnStop
    = pcw->addWidget( std::make_unique<Wt::WPushButton>("Stop" ) );
  
  //btnStart->setMargin(10, Wt::::Left | Wt::Right);

  Wt::WText *out 
    = pcw->addWidget( std::make_unique<Wt::WText>( "" ) );
}

Main::~Main( ) { }

} // namespace page
