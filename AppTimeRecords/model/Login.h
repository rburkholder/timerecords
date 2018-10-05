/* 
 * File:   Login.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 2, 2018, 6:06 PM
 */

#ifndef LOGIN_H
#define LOGIN_H

#include <boost/uuid/uuid.hpp>

#include <Wt/Dbo/Dbo.h>

namespace model {
  class Login;
}  // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::Login>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return 0; }
  static const char* versionField() { return 0; }
};

} // namespace Wt
} // namespace Dbo

namespace model {

namespace dbo = Wt::Dbo;

class Account;
class OptInKey;

class Login {
public:
  
  Login( );
  virtual ~Login( );
  
  boost::uuids::uuid id_login;
  std::string sLogin;
  std::string sSalt;
  std::string sHashPassword;
  
  dbo::ptr<Account> account;
  dbo::collection< dbo::ptr<OptInKey> > OptInKeys;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, id_login, "id_login" );
    dbo::belongsTo( a, account, ">id_account" );
    dbo::field( a, sLogin, "login" );
    dbo::field( a, sSalt, "salt" );
    dbo::field( a, sHashPassword, "hash_password" );
    dbo::hasMany( a, OptInKeys, dbo::ManyToOne, "id_login" ); // really should only be one per login, previous should be deleted.
  }
  
protected:
private:
  
  void Init();

};

} // namespace model

#endif /* LOGIN_H */

