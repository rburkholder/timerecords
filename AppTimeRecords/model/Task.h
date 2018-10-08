/* 
 * File:      model/Task.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on September 24, 2018, 7:22 PM
 */

// 2018/10/03 TODO: don't use WDateTime as key field, as it does not have an << operator

#ifndef TASK_H
#define TASK_H

#include <string>

#include <Wt/WDateTime.h>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace model {
  class Task;
}  // namespace model

// https://www.webtoolkit.eu/wt/doc/tutorial/dbo.html#customizing

namespace Wt {
  namespace Dbo {

    template<>
    struct dbo_traits<model::Task> : public dbo_default_traits {
      static const char *surrogateIdField() { return "id_task"; }
      static const char *versionField() { return nullptr; }
    };
    
  } // namespace Dbo
} // namespace WT

namespace model {

namespace dbo = Wt::Dbo;

class Account;

class AccountTaskType;
class TeamTaskType;
class CompanyTaskType;

class Task {
public:
  Task( );
  virtual ~Task( );

//  Wt::WString m_sTaskType;
  Wt::WDateTime m_dtStart;
  Wt::WDateTime m_dtEnd;
  Wt::WString m_sBillingText;
  Wt::WString m_sTaskText;
  
  dbo::ptr<Account> m_account;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::belongsTo( a, m_account, ">id_account" );
//    dbo::field( a, m_sTaskType,    "task_type" );
    dbo::field( a, m_dtStart,      "dt_start" );
    dbo::field( a, m_dtEnd,        "dt_end" );
    dbo::field( a, m_sBillingText, "billing_text" );
    dbo::field( a, m_sTaskText,    "task_text" );
  }
  
protected:
private:

};

} // namespace model

#endif /* TASK_H */

