/* 
 * File:   Account.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 2, 2018, 1:31 PM
 */

#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <Wt/WDateTime.h>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

#include "sqltraits/uuid.h"

namespace model {
  class Account;
}  // namespace model

namespace Wt {
namespace Dbo {

template<> 
struct dbo_traits<model::Account>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return nullptr; }
  static const char* versionField() { return nullptr; }
};

}
}

namespace model {

namespace dbo = Wt::Dbo;

class Email;
class Login;
class Task;
class Team;
class Company;

class Account {
public:
  
  Account( );
  virtual ~Account( );
  
  boost::uuids::uuid id_account;
  std::string sFirstName;
  std::string sLastName;
  Wt::WDateTime dtCreation;
  
  dbo::ptr<Company> company;
  
  dbo::collection< dbo::ptr<Task> > tasks;
  dbo::collection< dbo::ptr<Email> > email_addresses;
  dbo::collection< dbo::ptr<Login> > logins;
  dbo::collection< dbo::ptr<Team> > teams;

  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, id_account, "id_account" );
    dbo::belongsTo( a, company, ">id_company" );
    dbo::field( a, sFirstName, "name_first" );
    dbo::field( a, sLastName, "name_last" );
    dbo::field( a, dtCreation, "dt_creation" );
    dbo::hasMany( a, tasks, dbo::ManyToOne, "id_account" );
    dbo::hasMany( a, email_addresses, dbo::ManyToOne, "id_account" );
    dbo::hasMany( a, logins, dbo::ManyToOne, "id_account" );
    dbo::hasMany( a, teams, dbo::ManyToMany, "team_account" );
  }

protected:
private:
  
  void Init();
  
};

} // namespace model

#endif /* ACCOUNT_H */

