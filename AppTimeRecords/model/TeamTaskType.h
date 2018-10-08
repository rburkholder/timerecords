/* 
 * File:   TeamTaskType.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 8, 2018, 12:58 PM
 */

#ifndef TEAMTASKTYPE_H
#define TEAMTASKTYPE_H

#include <boost/uuid/uuid.hpp>

#include <Wt/Dbo/Dbo.h>

namespace model {
  class TeamTaskType;
}  // namespace model

namespace Wt {
namespace Dbo {

template<> struct dbo_traits<model::TeamTaskType>: public dbo_default_traits {
  typedef boost::uuids::uuid IdType;
  static IdType invalidId() { return boost::uuids::uuid(); }
  static const char* surrogateIdField() { return nullptr; }
  static const char* versionField() { return nullptr; }
};

} // namesapce Dbo
} // namespace Wt

namespace model {

namespace dbo = Wt::Dbo;

class Task;

class TeamTaskType {
public:
  TeamTaskType( );
  virtual ~TeamTaskType( );

  boost::uuids::uuid idTaskType;
  std::string sTaskType;
  std::string sDescription;
  
  dbo::ptr<Task> task;
  
  template<class Action>
  void persist( Action& a ) {
    dbo::id( a, idTaskType, "id_task_type" );
    dbo::belongsTo( a, task, ">id_task" );
    dbo::field( a, sTaskType, "task_type" );
    dbo::field( a, sDescription, "description" );
  }
  
protected:
private:

  void Init();

};

} // namespace model

#endif /* TEAMTASKTYPE_H */

