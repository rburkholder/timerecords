/* 
 * File:   CompanyTaskType.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 8, 2018, 12:58 PM
 */

#ifndef COMPANYTASKTYPE_H
#define COMPANYTASKTYPE_H

#include <boost/uuid/uuid.hpp>

#include <Wt/Dbo/Dbo.h>

namespace model {
  class CompanyTaskType;
}  // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::CompanyTaskType>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return nullptr; }
  static const char* versionField() { return nullptr; }
};

} // namesapce Dbo
} // namespace Wt

namespace model {

namespace dbo = Wt::Dbo;

class Company;

class CompanyTaskType {
public:
  CompanyTaskType( );
  virtual ~CompanyTaskType( );

  boost::uuids::uuid idType;
  int ix; // Orders the codes
  std::string sCode;
  std::string sDescription;
  
  dbo::ptr<Company> company;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, idType, "id_type" );
    dbo::belongsTo( a, company, ">id_company" );
    dbo::field( a, ix, "order" );
    dbo::field( a, sCode, "code" );
    dbo::field( a, sDescription, "description" );
  }
  
protected:
private:

  void Init();

};

} // namespace model

#endif /* COMPANYTASKTYPE_H */

