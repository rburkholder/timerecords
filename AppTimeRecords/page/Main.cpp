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

#include <chrono>

#include <Wt/WLabel.h>
#include <Wt/WText.h>
#include <Wt/WBreak.h>
#include <Wt/WLineEdit.h>
#include <Wt/WPushButton.h>
#include <Wt/WComboBox.h>
#include <Wt/WTimer.h>
#include <Wt/WLocalDateTime.h>
#include <Wt/WHBoxLayout.h>
#include <Wt/WVBoxLayout.h>

#include "Main.h"

namespace page {

Main::Main(  )
: Wt::WContainerWidget(  )
{ 
  
  m_textDateTimeCurrent = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeCurrent->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);

  addWidget( std::make_unique<Wt::WBreak>() );
  
  // button start
  
  m_btnStart = addWidget( std::make_unique<Wt::WPushButton>("Start" ) );
  m_btnStart->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnStart->setEnabled( true );
  //m_btnStart->clicked().connect( this, &Main::HandleBtnStart );
  m_btnStart->clicked().connect( [this] {
    m_dtStart = Wt::WDateTime::currentDateTime();
    m_textDateTimeStart->setText( m_dtStart.toString() );
    m_textDateTimeStop->setText( "" );
    m_textResult->setText( "started: " + m_textDateTimeStart->text() + " " + m_textDateTimeStop->text() + " " + m_cbAccount->currentText() + " " +  m_lineBillingText->text() );
    m_btnStart->setEnabled( false );
    m_btnStop->setEnabled( true );
    m_btnNext->setEnabled( true );
    m_btnCancel->setEnabled( true );
  } );
  
  //Wt::WLabel* labelStart = addWidget(std::make_unique<Wt::WLabel>("Start: "));
  //labelStart->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  
  m_textDateTimeStart = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeStart->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  //m_textDateTimeStart->setText( "date time start" );
  //m_textDateTimeStart->setMinimumSize( m_textDateTimeStart->maximumHeight(), 60 );
  
  addWidget( std::make_unique<Wt::WBreak>() );
  
  // button stop
  
  m_btnStop = addWidget( std::make_unique<Wt::WPushButton>("Stop" ) );
  m_btnStop->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnStop->setEnabled( false );
  //m_btnStop->clicked().connect( this, &Main::HandleBtnStop );
  m_btnStop->clicked().connect( [this] {
    if ( m_lineBillingText->text().empty() ) {
      m_textResult->setText( "require some billing text" );
    }
    else {
      m_dtStop = Wt::WDateTime::currentDateTime();
      m_textDateTimeStop->setText( m_dtStop.toString() );
      m_textResult->setText( "stopped: " + m_textDateTimeStart->text() + " " + m_textDateTimeStop->text() + " " + m_cbAccount->currentText() + " " +  m_lineBillingText->text() );
      m_btnStart->setEnabled( true );
      m_btnStop->setEnabled( false );
      m_btnCancel->setEnabled( false );
      m_btnNext->setEnabled( false );
      m_lineBillingText->setText( "" );
      m_lineDetails->setText( "" );
    }
  } );

  //Wt::WLabel* labelStop = addWidget(std::make_unique<Wt::WLabel>("Stop: "));
  //labelStop->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  
  m_textDateTimeStop = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeStop->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  //m_textDateTimeStop->setText( "date time stop" );
  //m_textDateTimeStop->setMinimumSize( m_textDateTimeStop->maximumHeight(), 60 );
  
  addWidget( std::make_unique<Wt::WBreak>() );
  
  // button next
  
  m_btnNext = addWidget( std::make_unique<Wt::WPushButton>("Next" ) );
  m_btnNext->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnNext->setEnabled( false );
  //m_btnNext->clicked().connect( this, &Main::HandleBtnNext );
  m_btnNext->clicked().connect( [this] {
    if ( m_lineBillingText->text().empty() ) {
      m_textResult->setText( "require some billing text" );
    }
    else {
      // close out one record
      m_dtStop = Wt::WDateTime::currentDateTime();
      m_textDateTimeStop->setText( m_dtStop.toString() );
      // start next record
      m_dtStart = Wt::WDateTime::currentDateTime();
      m_textDateTimeStart->setText( m_dtStart.toString() );
      m_textResult->setText( "close & started: " + m_textDateTimeStart->text() + " " + m_textDateTimeStop->text() + " " + m_cbAccount->currentText() + " " +  m_lineBillingText->text() );
      m_textDateTimeStop->setText( "" );
      m_lineBillingText->setText( "" );
      m_lineDetails->setText( "" );
    }
  } );

  addWidget( std::make_unique<Wt::WBreak>() );
  
  m_btnCancel = addWidget( std::make_unique<Wt::WPushButton>( "Cancel" ) );
  m_btnCancel->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnCancel->setEnabled( false );
  m_btnCancel->clicked().connect( [this] {
    m_btnStart->setEnabled( true );
    m_btnStop->setEnabled( false );
    m_btnNext->setEnabled( false );
    m_textDateTimeStart->setText( "" );
    m_textDateTimeStop->setText( "" );
    m_textResult->setText( "cancelled" );
  });
  
  
  addWidget( std::make_unique<Wt::WBreak>() );
  
  m_textDuration = addWidget( std::make_unique<Wt::WText>() );
  m_textDuration->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_textDuration->setMinimumSize( m_textDuration->minimumHeight(), 60 );
  
  addWidget( std::make_unique<Wt::WBreak>() );
  
  auto fields = addWidget( std::make_unique<Wt::WContainerWidget>() );
  auto hl = fields->setLayout( std::make_unique<Wt::WHBoxLayout>() );
  
  auto layoutLeft = hl->addLayout( std::make_unique<Wt::WVBoxLayout>() );
  
  m_cbAccount = layoutLeft->addWidget( std::make_unique<Wt::WComboBox>() );
  m_cbAccount->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_cbAccount->addItem( "cust1");
  m_cbAccount->addItem( "break" );
  m_cbAccount->addItem( "email" );
  m_cbAccount->addItem( "movies" );
  m_cbAccount->addItem( "tradeframe" );
  m_cbAccount->addItem( "timerecords" );
  
  auto filler = layoutLeft->addWidget( std::make_unique<Wt::WText>( " " ) );
  
  //auto fieldsLeft = hl->addWidget( std::make_unique<Wt::WContainerWidget>() );
  
  auto vl = hl->addLayout( std::make_unique<Wt::WVBoxLayout>(), 1 );
  
  //fieldsLeft->setContentAlignment(  Wt::AlignmentFlag::Left );
  //auto fieldsRight = fields->addWidget( std::make_unique<Wt::WContainerWidget>() );
  //fieldsRight->setContentAlignment(  Wt::AlignmentFlag::Right );
  
  m_lineBillingText = vl->addWidget( std::make_unique<Wt::WLineEdit>() );
  m_lineBillingText->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_lineBillingText->setMaxLength( 400 );
  m_lineBillingText->setTextSize( 80 );
  
  //fieldsRight->addWidget( std::make_unique<Wt::WBreak>() );
  
  m_lineDetails = vl->addWidget( std::make_unique<Wt::WLineEdit>() );
  m_lineDetails->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_lineDetails->setMaxLength( 400 );
  m_lineDetails->setTextSize( 80 );
  
  addWidget( std::make_unique<Wt::WBreak>() );
  
  m_textResult = addWidget( std::make_unique<Wt::WText>() );
  
  auto timer = addChild(std::make_unique<Wt::WTimer>());
  timer->setInterval( std::chrono::seconds( 59 ) );
  timer->timeout().connect(this, &Main::HandleTimer );
  timer->start();
  
  // gratuitus call for init
  HandleTimer();
}

Main::~Main( ) { }

void Main::HandleTimer() {  // called from two places, so not lambda material
  Wt::WLocalDateTime now;
  now = Wt::WLocalDateTime::currentServerDateTime();
  m_textDateTimeCurrent->setText( now.toString( "yyyy-MM-dd HH:mm" ) );
}

} // namespace page
