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
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>

#include "Main.h"

namespace page {

Main::Main(  )
: Wt::WContainerWidget(  )
{ 
  
  m_btnStart = addWidget( std::make_unique<Wt::WPushButton>("Start" ) );
  m_btnStart->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnStart->setEnabled( true );
  m_btnStart->clicked().connect( this, &Main::HandleBtnStart );
  
  m_btnStop = addWidget( std::make_unique<Wt::WPushButton>("Stop" ) );
  m_btnStop->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnStop->setEnabled( false );
  m_btnStop->clicked().connect( this, &Main::HandleBtnStop );

  m_btnNext = addWidget( std::make_unique<Wt::WPushButton>("Next" ) );
  m_btnNext->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnNext->setEnabled( false );
  m_btnNext->clicked().connect( this, &Main::HandleBtnNext );

  addWidget( std::make_unique<Wt::WBreak>() );
  
  m_textDateTimeStart = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeStart->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_textDateTimeStart->setText( "date time start" );
  //m_textDateTimeStart->setMinimumSize( m_textDateTimeStart->maximumHeight(), 60 );
  
  m_textDateTimeStop = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeStop->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_textDateTimeStop->setText( "date time stop" );
  //m_textDateTimeStop->setMinimumSize( m_textDateTimeStop->maximumHeight(), 60 );
  
  m_textDuration = addWidget( std::make_unique<Wt::WText>() );
  m_textDuration->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_textDuration->setMinimumSize( m_textDuration->minimumHeight(), 60 );
  
  m_cbAccount = addWidget( std::make_unique<Wt::WComboBox>() );
  m_cbAccount->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_cbAccount->addItem( "cust1");
  m_cbAccount->addItem( "break" );
  m_cbAccount->addItem( "email" );
  m_cbAccount->addItem( "movies" );
  m_cbAccount->addItem( "tradeframe" );
  m_cbAccount->addItem( "timerecords" );
  
  m_lineDescription = addWidget( std::make_unique<Wt::WLineEdit>() );
  m_lineDescription->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_lineDescription->setMaxLength( 400 );
  m_lineDescription->setTextSize( 80 );
  
  addWidget( std::make_unique<Wt::WBreak>() );
  
  m_textResult = addWidget( std::make_unique<Wt::WText>() );
}

Main::~Main( ) { }

void Main::HandleBtnStart() {
  m_textResult->setText( "started: " + m_textDateTimeStart->text() + " " + m_textDateTimeStop->text() + " " + m_cbAccount->currentText() + " " +  m_lineDescription->text() );
  m_btnStart->setEnabled( false );
  m_btnStop->setEnabled( true );
  m_btnNext->setEnabled( true );
}

void Main::HandleBtnStop() {
  m_textResult->setText( "stopped: " + m_textDateTimeStart->text() + " " + m_textDateTimeStop->text() + " " + m_cbAccount->currentText() + " " +  m_lineDescription->text() );
  m_btnStart->setEnabled( true );
  m_btnStop->setEnabled( false );
  m_btnNext->setEnabled( false );
  // validate existence of text
}

void Main::HandleBtnNext() {
  m_textResult->setText( "close & started: " + m_textDateTimeStart->text() + " " + m_textDateTimeStop->text() + " " + m_cbAccount->currentText() + " " +  m_lineDescription->text() );
  // validate existence of text
  //m_btnStart->setEnabled( true );
  //m_btnStop->setEnabled( false );
}

} // namespace page
