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

namespace dbo = Wt::Dbo;

class Login {
public:
  
  Login( );
  virtual ~Login( );
  
  boost::uuids::uuid id_login;
  std::string sLogin;
  std::string sSalt;
  std::string sHashPassword;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, id_login, "id_login" );
    dbo::field( a, sLogin, "login" );
    dbo::field( a, sSalt, "salt" );
    dbo::field( a, sHashPassword, "hash_password" );
    
  }
  
protected:
private:
  
  void Init();

};

} // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::Login>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return 0; }
  static const char* versionField() { return 0; }
};

}
}

#endif /* LOGIN_H */

