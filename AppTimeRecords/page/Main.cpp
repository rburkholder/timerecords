/* 
 * File:      Main.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
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

// need to modify with state machine to handle start, stop, cancel (maybe pause)

Main::Main(  )
: Wt::WContainerWidget(  ), m_state( EState::Init )
{ 
  
  m_textDateTimeCurrent = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeCurrent->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);

  addWidget( std::make_unique<Wt::WBreak>() );
  
  // button start
  
  m_btnStart = addWidget( std::make_unique<Wt::WPushButton>("Start Task" ) );
  m_btnStart->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnStart->clicked().connect( [this] {
    TransitionTo( EState::InTask );
  } );
  
  //Wt::WLabel* labelStart = addWidget(std::make_unique<Wt::WLabel>("Start: "));
  //labelStart->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  
  m_textDateTimeStart = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeStart->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  //m_textDateTimeStart->setText( "date time start" );
  //m_textDateTimeStart->setMinimumSize( m_textDateTimeStart->maximumHeight(), 60 );
  
  addWidget( std::make_unique<Wt::WBreak>() );
  
  // button stop
  
  m_btnComplete = addWidget( std::make_unique<Wt::WPushButton>("End Task" ) );
  m_btnComplete->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnComplete->clicked().connect( [this] {
    TransitionTo( EState::Close );
  } );

  //Wt::WLabel* labelStop = addWidget(std::make_unique<Wt::WLabel>("Stop: "));
  //labelStop->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  
  m_textDateTimeStop = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeStop->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  //m_textDateTimeStop->setText( "date time stop" );
  //m_textDateTimeStop->setMinimumSize( m_textDateTimeStop->maximumHeight(), 60 );
  
  addWidget( std::make_unique<Wt::WBreak>() );
  
  // button next
  
  m_btnNext = addWidget( std::make_unique<Wt::WPushButton>("Next Task" ) );
  m_btnNext->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnNext->clicked().connect( [this] {
    TransitionTo( EState::Close );
    if ( EState::Free == m_state ) {
      TransitionTo( EState::InTask );
    }
    else {
      // prevented from performing state transition
    }
  } );

  addWidget( std::make_unique<Wt::WBreak>() );
  
  // buton cancel
  
  m_btnCancel = addWidget( std::make_unique<Wt::WPushButton>( "Cancel Task" ) );
  m_btnCancel->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_btnCancel->clicked().connect( [this] {
    TransitionTo( EState::Cancel );
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
  
  TransitionTo( Free );
  
  // gratuitus call for init
  HandleTimer();
}

Main::~Main( ) { }

void Main::TransitionTo( EState state ) {
  switch ( m_state ) {
    case EState::Init:  // holding state for startup only
      switch ( state ) {
        case EState::Free:
          m_state = EState::Transit;
          TransitionTo( EState::Free );
          break;
        default: {
            assert( 0 ); // Free is only allowed next state
          }
      }
      break;
    case EState::Free:  // holding state
      switch ( state ) {
        case EState::InTask:
          m_btnStart->setEnabled( false );
          m_btnComplete->setEnabled( true );
          m_btnNext->setEnabled( true );
          m_btnCancel->setEnabled( true );

          m_dtStart = Wt::WDateTime::currentDateTime();
          m_textDateTimeStart->setText( m_dtStart.toString() );
          m_textDateTimeStop->setText( "" );
          m_textResult->setText( "started: " + m_textDateTimeStart->text() + " " + m_textDateTimeStop->text() + " " + m_cbAccount->currentText() + " " +  m_lineBillingText->text() );

          m_state = EState::InTask;
          break;
        default: {
          assert( 0 ); // unhandled state
        }
      }
      break;
    case EState::InTask: // holding state
      switch ( state ) {
        case EState::Close:
          if ( m_lineBillingText->text().empty() ) {
            m_textResult->setText( "require some billing text" );
          }
          else {
            // disable buttons during persistence portion
            m_btnStart->setEnabled( false );
            m_btnComplete->setEnabled( false );
            m_btnNext->setEnabled( false );
            m_btnCancel->setEnabled( false );

            m_dtStop = Wt::WDateTime::currentDateTime();
            m_textDateTimeStop->setText( m_dtStop.toString() );
            m_textResult->setText( "completed: " + m_textDateTimeStart->text() + " " + m_textDateTimeStop->text() + " " + m_cbAccount->currentText() + " " +  m_lineBillingText->text() );
            m_lineBillingText->setText( "" );
            m_lineDetails->setText( "" );

            // TODO: perform persistence here
            
            // finalize with transition
            m_state = EState::Transit;
            TransitionTo( EState::Free );
          }
          break;
        case EState::Cancel:
          m_textDateTimeStart->setText( "" );
          m_textDateTimeStop->setText( "" );
          m_textResult->setText( "cancelled" );
          // skip any persistence
          // finalize with transition
          m_state = EState::Transit;
          TransitionTo( EState::Free );
          break;
        default: {
          assert( 0 ); // unhandled state
        }
      }
      break;
    case EState::Transit:  // common pre-state init for internal state transitions
      switch ( state ) {
        case EState::Free:
          m_btnStart->setEnabled( true );
          m_btnComplete->setEnabled( false );
          m_btnNext->setEnabled( false );
          m_btnCancel->setEnabled( false );
          m_state = EState::Free;
          break;
        default: {
          assert( 0 );  // not sure what other states arrive
        }
      }
      break;
    default: {
      assert( 0 );  // no other holding states allowed
      }
  }
}

void Main::HandleTimer() {  // called from two places, so not lambda material
  Wt::WLocalDateTime now;
  now = Wt::WLocalDateTime::currentServerDateTime();
  m_textDateTimeCurrent->setText( now.toString( "yyyy-MM-dd HH:mm" ) );
}

} // namespace page
