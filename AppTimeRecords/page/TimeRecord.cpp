/*
 * File:      page/TimeRecord.cpp
 * Author:    raymond@burkholder.net
 * copyright: 2018 Raymond Burkholder
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

#include "../model/Account.h"
#include "../model/Task.h"

#include <Wt/Dbo/Session.h>

#include "TimeRecord.h"

namespace {
  static const std::string sDateFormat( "yyyy-MM-dd" );
  static const std::string sTimeFormat( "HH:mm:ss" );
  static const std::string sDateTimeFormat( sDateFormat + " " + sTimeFormat );
}

namespace page {

TimeRecord::TimeRecord( dbo::Session& session )
: Wt::WContainerWidget(  ),
  m_state( EState::Init ),
  m_session( session ),
  m_time_zone_offset( 0 )
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

  m_textDateTimeEnd = addWidget( std::make_unique<Wt::WText>() );
  m_textDateTimeEnd->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
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

  {
    Wt::WLength width( 130 );
    m_btnStart->setWidth( width );
    m_btnComplete->setWidth( width );
    m_btnNext->setWidth( width );
    m_btnCancel->setWidth( width );
  }

  addWidget( std::make_unique<Wt::WBreak>() );

  m_textDuration = addWidget( std::make_unique<Wt::WText>() );
  m_textDuration->setMargin(10,  Wt::Side::Left |  Wt::Side::Right);
  m_textDuration->setMinimumSize( m_textDuration->minimumHeight(), 60 );

  addWidget( std::make_unique<Wt::WBreak>() );

  auto fields = addWidget( std::make_unique<Wt::WContainerWidget>() );
  auto hl = fields->setLayout( std::make_unique<Wt::WHBoxLayout>() );

  auto layoutLeft = hl->addLayout( std::make_unique<Wt::WVBoxLayout>() );

  m_cbAccount = layoutLeft->addWidget( std::make_unique<Wt::WComboBox>() );
  m_cbAccount->setMargin(10, Wt::Side::Left | Wt::Side::Right);
  m_cbAccount->addItem( "ross");
  m_cbAccount->addItem( "yenom-fixed");
  m_cbAccount->addItem( "yenom-hourly");
  m_cbAccount->addItem( "tradeframe" );
  m_cbAccount->addItem( "email" );
  m_cbAccount->addItem( "break" );
  m_cbAccount->addItem( "cust1");
  m_cbAccount->addItem( "cust2");
  m_cbAccount->addItem( "project1");
  m_cbAccount->addItem( "project2");
  m_cbAccount->addItem( "project3");
  m_cbAccount->addItem( "timerecords" );
  m_cbAccount->setStyleClass( "classBlock" );

  m_textTimeInTask = layoutLeft->addWidget( std::make_unique<Wt::WText>( " " ) );
  m_textTimeInTask->setStyleClass( "classBlock classCenter" );

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

  Wt::WLocalDateTime dt = Wt::WLocalDateTime::currentDateTime();
  m_time_zone_offset = dt.timeZoneOffset();

  {
    dbo::Transaction transaction( m_session );
    try {
      m_account = m_session.find<model::Account>().where( "name_first=? and name_last=?" ).bind( "_unassigned_" ).bind( "_unassigned_" );
    }
    catch ( Wt::Dbo::Exception& exception ) {
      std::cerr << exception.what() << std::endl;
    }
  }

  auto timer = addChild(std::make_unique<Wt::WTimer>());
  timer->setInterval( std::chrono::seconds( 1 ) );
  timer->timeout().connect(this, &TimeRecord::HandleTimer );
  timer->start();

  TransitionTo( Free );

  // gratuitus call for init
  HandleTimer();
}

TimeRecord::~TimeRecord( ) { }

void TimeRecord::TransitionTo( EState state ) {
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

          {
            m_dtStart = std::chrono::system_clock::now();
            time_point_t dtStartLocal = m_dtStart + std::chrono::duration<int,std::ratio<60> >( m_time_zone_offset );
            Wt::WDateTime dtStart( dtStartLocal );
            m_textDateTimeStart->setText( dtStart.toString( sDateTimeFormat ) );
          }

          m_textDateTimeEnd->setText( "" );
          m_textResult->setText( "started: " + m_textDateTimeStart->text() + " " + m_textDateTimeEnd->text() + " " + m_cbAccount->currentText() + " " +  m_lineBillingText->text() );

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

            {
              m_dtEnd = std::chrono::system_clock::now();
              time_point_t dtEndLocal = m_dtEnd + std::chrono::duration<int,std::ratio<60> >( m_time_zone_offset );
              Wt::WDateTime dtEnd( dtEndLocal );
              m_textDateTimeEnd->setText( dtEnd.toString( sDateTimeFormat ) );
            }

            PersistTask();

            m_textResult->setText( "completed: " + m_textDateTimeStart->text() + " " + m_textDateTimeEnd->text() + " " + m_cbAccount->currentText() + " " +  m_lineBillingText->text() );
            m_lineBillingText->setText( "" );
            m_lineDetails->setText( "" );
            m_textTimeInTask->setText( " " );

            // finalize with transition
            m_state = EState::Transit;
            TransitionTo( EState::Free );
          }
          break;
        case EState::Cancel:
          m_textDateTimeStart->setText( "" );
          m_textDateTimeEnd->setText( "" );
          m_textTimeInTask->setText( " " );
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

void TimeRecord::HandleTimer() {  // called from two places, so not lambda material

  time_point_t utcNow = std::chrono::system_clock::now();

  time_point_t localNow = utcNow + std::chrono::duration<int,std::ratio<60> >( m_time_zone_offset );
  Wt::WDateTime dtStart( localNow );
  m_textDateTimeCurrent->setText( dtStart.toString( sDateTimeFormat ) );  // but this isn't local time

  if ( EState::InTask == m_state ) {
    auto dur = utcNow - m_dtStart;

    typedef decltype(dur) dur_t;

    auto seconds = (dur.count() * dur_t::period::num) / dur_t::period::den;

    static const Wt::WTime time( 0, 0, 0 );

    m_textTimeInTask->setText( time.addSecs( seconds ).toString( sTimeFormat ) );

  }
}

void TimeRecord::PersistTask() {

  namespace dbo = Wt::Dbo;

  Wt::WDateTime dtStart( m_dtStart );
  Wt::WDateTime dtEnd( m_dtEnd );

  dbo::Transaction transaction( m_session );

  std::unique_ptr<model::Task> pTask( new model::Task );
  pTask->m_sCode = m_cbAccount->currentText();
  pTask->m_sCodeOrigin = "account";
  pTask->m_account = m_account;
  pTask->m_dtStart = dtStart;
  pTask->m_dtEnd = dtEnd;
  pTask->m_sBillingText = m_lineBillingText->text();
  pTask->m_sTaskText = m_lineDetails->text();

  dbo::ptr<model::Task> pdboTask = m_session.add( std::move( pTask ) );
  transaction.commit();

}

} // namespace page
