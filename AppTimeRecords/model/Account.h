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

#include <boost/uuid/uuid.hpp>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace model {

namespace dbo = Wt::Dbo;

class Account {
public:
  
  Account( );
  virtual ~Account( );
  
  boost::uuids::uuid id_account;
  std::string sFirstName;
  std::string sLastName;
  Wt::WDateTime dtCreation;

  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, id_account, "id_account" );
    dbo::field( a, sFirstName, "name_first" );
    dbo::field( a, sLastName, "name_last" );
    dbo::field( a, dtCreation, "dt_creation" );
  }

protected:
private:
  
  void Init();
  
};

} // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::Account>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return 0; }
  static const char* versionField() { return 0; }
};

}
}

#endif /* ACCOUNT_H */

