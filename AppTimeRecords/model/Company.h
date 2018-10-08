/* 
 * File:      model/Company.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 2, 2018, 6:54 PM
 */

#ifndef COMPANY_H
#define COMPANY_H

#include <boost/uuid/uuid.hpp>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace model {
  class Company;
}  // namespace model

namespace Wt {
namespace Dbo {

template<> 
struct dbo_traits<model::Company>: public dbo_default_traits {
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

class Company {
public:
  Company( );
  virtual ~Company( );
  
  boost::uuids::uuid id_company;
  std::string sName;
  
  dbo::collection< dbo::ptr<Account> > accounts;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, id_company, "id_company" );
    dbo::field( a, sName, "name" );
    dbo::hasMany( a, accounts, dbo::ManyToOne, "id_company" );
  }
  
protected:
private:
  
  void Init();

};

}  // namespace model

#endif /* COMPANY_H */

