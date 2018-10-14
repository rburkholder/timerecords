/* 
 * File:   AccountTaskType.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 8, 2018, 12:57 PM
 */

#ifndef ACCOUNTTASKTYPE_H
#define ACCOUNTTASKTYPE_H

#include <boost/uuid/uuid.hpp>

#include <Wt/Dbo/Dbo.h>

namespace model {
  class AccountTaskType;
}  // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::AccountTaskType>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return nullptr; }
  static const char* versionField() { return nullptr; }
};

} // namesapce Dbo
} // namespace Wt

namespace model {

namespace dbo = Wt::Dbo;

class Account;

class AccountTaskType {
public:
  AccountTaskType( );
  virtual ~AccountTaskType( );

  boost::uuids::uuid idType;
  int ix; // Orders the codes
  std::string sCode;
  std::string sDescription;
  
  dbo::ptr<Account> account;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, idType, "id_type" );
    dbo::belongsTo( a, account, ">id_account" );
    dbo::field( a, ix, "order" );
    dbo::field( a, sCode, "code" );
    dbo::field( a, sDescription, "description" );
  }
  
protected:
private:

  void Init();

};

} // namespace model

#endif /* ACCOUNTTASKTYPE_H */

