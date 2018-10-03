/* 
 * File:   Version.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3*
 * Created on October 2, 2018, 7:12 PM
 */

#ifndef VERSION_H
#define VERSION_H

#include <Wt/Dbo/Dbo.h>

namespace model {

namespace dbo = Wt::Dbo;

class Version {
public:
  Version( );
  virtual ~Version( );
  
  unsigned int nVersionMajor;
  unsigned int nVersionMinor;
  std::string sDescription;

  template<class Action>
  void persist( Action& a ) {
    dbo::field( a, nVersionMajor, "version_major" );
    dbo::field( a, nVersionMinor, "version_minor" );
    dbo::field( a, sDescription, "description" );
  }
  
protected:
private:

};

}  // namespace model

namespace Wt {
  namespace Dbo {

    template<>
    struct dbo_traits<model::Version> : public dbo_default_traits {
      static const char *surrogateIdField() { 
        return "id_version";
        }
      static const char *versionField() {
        return 0;
      }
    };
    
  } // namespace Dbo
} // namespace Wt

#endif /* VERSION_H */

