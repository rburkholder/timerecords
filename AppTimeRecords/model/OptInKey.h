/* 
 * File:   OptInKey.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 2, 2018, 6:21 PM
 */

#ifndef OPTINKEY_H
#define OPTINKEY_H

#include <boost/uuid/uuid.hpp>

#include <Wt/WDateTime.h>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace model {
  class OptInKey;
}  // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::OptInKey>: public dbo_default_traits {
  //static const char* surrogateIdField() { return "key_opt_in"; }
  typedef std::string IdType;
  static IdType invalidId() { return std::string(); }
  static const char* surrogateIdField() { return 0; }
  static const char* versionField() { return 0; }
};

} // namespace Wt
} // namespace Dbo

namespace model {

namespace dbo = Wt::Dbo;

class Login;

class OptInKey {
public:
  OptInKey( );
  virtual ~OptInKey( );
  
  std::string sKeyOptIn;
  Wt::WDateTime dtExpiry;
  
  dbo::ptr<Login> login;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, sKeyOptIn, "key_opt_in" );
    dbo::belongsTo( a, login, ">id_login" );
    dbo::field( a, dtExpiry, "dt_expiry" );
  }
  
protected:
private:

};

}  // namespace model

#endif /* OPTINKEY_H */

