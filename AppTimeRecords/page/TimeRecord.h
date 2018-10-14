/* 
 * File:      page/TimeRecord.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 22, 2018, 3:45 PM
 */

#ifndef START_H
#define START_H

#include <chrono>

#include <Wt/WLocalDateTime.h>
#include <Wt/WContainerWidget.h>
//#include <Wt/Dbo/Session.h>

#include "../model/Account.h"

namespace page {

namespace dbo = Wt::Dbo;

class TimeRecord: public Wt::WContainerWidget {
public:
  TimeRecord( dbo::Session& );
  virtual ~TimeRecord( );
private:
  
  int m_time_zone_offset;
  
  dbo::Session& m_session;
  
  dbo::ptr<model::Account> m_account;
  
  typedef std::chrono::time_point<std::chrono::system_clock> time_point_t;
  
  time_point_t m_dtStart;
  time_point_t m_dtEnd;
  
  Wt::WText* m_textDateTimeCurrent; 
  Wt::WPushButton* m_btnStart;
  Wt::WPushButton* m_btnComplete;
  Wt::WPushButton* m_btnNext;
  Wt::WPushButton* m_btnCancel;
  Wt::WText* m_textDateTimeStart; 
  Wt::WText* m_textDateTimeEnd;
  Wt::WText* m_textDuration;
  Wt::WComboBox* m_cbAccount;
  Wt::WText* m_textTimeInTask;
  Wt::WLineEdit* m_lineBillingText;
  Wt::WLineEdit* m_lineDetails;
  Wt::WText* m_textResult;
  
  enum EState { Init, Free, InTask, Close, Cancel, Transit };
  EState m_state;
  
  void HandleTimer();
  void TransitionTo( EState );
  
  void PersistTask();
};

} // namespace page

#endif /* START_H */

