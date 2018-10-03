/* 
 * File:   Team.h
  * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 2, 2018, 6:40 PM
 */

#ifndef TEAM_H
#define TEAM_H

#include <boost/uuid/uuid.hpp>

#include <Wt/Dbo/Dbo.h>

namespace model {

namespace dbo = Wt::Dbo;

class Team {
public:
  Team( );
  virtual ~Team( );
  
  boost::uuids::uuid id_team;
  std::string sName;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, id_team, "id_team" );
    dbo::field( a, sName, "name" );
  }
  
protected:
private:
  
  void Init();

};

}  // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::Team>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return 0; }
  static const char* versionField() { return 0; }
};

} // namesapce Dbo
} // namespace Wt

#endif /* TEAM_H */

