/* 
 * File:      Main.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on September 22, 2018, 3:45 PM
 */

#ifndef START_H
#define START_H

#include <Wt/WLocalDateTime.h>
#include <Wt/WContainerWidget.h>
#include <Wt/Dbo/Session.h>

namespace page {

namespace dbo = Wt::Dbo;

class Main: public Wt::WContainerWidget {
public:
  Main( dbo::Session& );
  virtual ~Main( );
private:
  
  dbo::Session& m_session;
  
  Wt::WLocalDateTime m_dtStart;
  Wt::WLocalDateTime m_dtEnd;
  
  Wt::WText* m_textDateTimeCurrent; 
  Wt::WPushButton* m_btnStart;
  Wt::WPushButton* m_btnComplete;
  Wt::WPushButton* m_btnNext;
  Wt::WPushButton* m_btnCancel;
  Wt::WText* m_textDateTimeStart; 
  Wt::WText* m_textDateTimeEnd;
  Wt::WText* m_textDuration;
  Wt::WComboBox* m_cbAccount;
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

