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

#include <Wt/Dbo/Dbo.h>
#include <Wt/WDateTime.h>

namespace model {

namespace dbo = Wt::Dbo;
class OptInKey {
public:
  OptInKey( );
  virtual ~OptInKey( );
  
  std::string sOptInKey;
  boost::uuids::uuid id_login;
  Wt::WDateTime dtExpiry;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, sOptInKey, "key_optin" );
    dbo::field( a, id_login, "id_login" ); // foreign key
    dbo::field( a, dtExpiry, "dt_expiry" );
  }
  
protected:
private:

};

}  // namespace model

#endif /* OPTINKEY_H */

