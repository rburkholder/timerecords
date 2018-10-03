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

namespace dbo = Wt::Dbo;

class Email {
public:
  
  Email( );
  virtual ~Email( );
  
  boost::uuids::uuid id_email;
  std::string sEmail;
  std::string sDescription;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, id_email, "id_email" );
    dbo::field( a, sEmail, "email" );
    dbo::field( a, sDescription, "description" );
  }
protected:
private:

  void Init();

};

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

#endif /* EMAIL_H */

