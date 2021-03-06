/* 
 * File:   model/KeyValue.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 3, 2018, 12:01 AM
 */

#ifndef KEYVALUE_H
#define KEYVALUE_H

#include <Wt/Dbo/Dbo.h>

namespace model {
  class KeyValue;
}  // namespace model

namespace Wt {
  namespace Dbo {

    template<>
    struct dbo_traits<model::KeyValue> : public dbo_default_traits {
      //static const char *surrogateIdField() {  return "key"; }
      typedef std::string IdType;
      static IdType invalidId() { return std::string(); }
      static const char *surrogateIdField() {  return nullptr; }
      static const char *versionField() { return nullptr; }
    };
    
  } // namespace Dbo
} // namespace Wt

namespace model {

namespace dbo = Wt::Dbo;

class KeyValue {
public:
  KeyValue( );
  virtual ~KeyValue( );
  
  std::string sKey;
  std::string sValue;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, sKey, "key" );
    dbo::field( a, sValue, "value" );
  }
protected:
private:

};

} // namespace model

#endif /* KEYVALUE_H */

