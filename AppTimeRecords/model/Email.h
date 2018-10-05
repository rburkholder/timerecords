/* 
 * File:   email.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 2, 2018, 4:24 PM
 */

#ifndef EMAIL_H
#define EMAIL_H

#include <boost/uuid/uuid.hpp>

#include <Wt/Dbo/Dbo.h>

namespace model {
  class Email;
}  // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::Email>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return 0; }
  static const char* versionField() { return 0; }
};

} // namesapce Dbo
} // namespace Wt

namespace model {

namespace dbo = Wt::Dbo;

class Account;

class Email {
public:
  
  Email( );
  virtual ~Email( );
  
  boost::uuids::uuid id_email;
  bool bPrimary;
  std::string sEmailAddress;
  std::string sDescription;
  
  dbo::ptr<Account> account;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, id_email, "id_email_address" );
    dbo::belongsTo( a, account, ">id_account" );
    dbo::field( a, bPrimary, "is_primary" );
    dbo::field( a, sEmailAddress, "email_address" );
    dbo::field( a, sDescription, "description" );
  }
protected:
private:

  void Init();

};

}  // namespace model

#endif /* EMAIL_H */

