/* 
 * File:   Version.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3*
 * Created on October 2, 2018, 7:12 PM
 */

// this info should actually be in a build file somewhere?

#ifndef VERSION_H
#define VERSION_H

#include <string>

#include <Wt/Dbo/Dbo.h>
#include <Wt/Dbo/WtSqlTraits.h>

namespace model {

namespace dbo = Wt::Dbo;

class DbVersion {
public:
  DbVersion( );
  virtual ~DbVersion( );
  
  int nVersionMajor;
  int nVersionMinor;
  std::string sDescription;
  std::string sBuildAbsolute; // to build current db
  std::string sBuildDifference; // difference to previous
  std::string sBuildRollback;  // to roll back to previous

  template<class Action>
  void persist( Action& a ) {
    dbo::field( a, nVersionMajor, "version_major" );
    dbo::field( a, nVersionMinor, "version_minor" );
    dbo::field( a, sDescription, "description" );
    dbo::field( a, sBuildAbsolute, "build_absolute" );
    dbo::field( a, sBuildDifference, "build_difference" );
    dbo::field( a, sBuildRollback, "build_rollback" );
  }
  
protected:
private:

};

}  // namespace model

namespace Wt {
  namespace Dbo {

    template<>
    struct dbo_traits<model::DbVersion> : public dbo_default_traits {
      static const char *surrogateIdField() { return "id_db_version"; }
      static const char *versionField() { return 0; }
    };
    
  } // namespace Dbo
} // namespace Wt


#endif /* VERSION_H */

