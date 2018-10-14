/* 
 * File:      page/EditTaskType.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 10, 2018, 4:07 PM
 */

#ifndef EDITTASKTYPE_H
#define EDITTASKTYPE_H

#include <Wt/Dbo/Dbo.h>
//#include <Wt/Dbo/WtSqlTraits.h>

namespace page {

namespace dbo = Wt::Dbo;

template<typename TaskType>
class EditTaskType {
public:
  
  typedef dbo::collection< dbo::ptr<TaskType> > TaskTypes;
  
  EditTaskType( );
  virtual ~EditTaskType( );
  
protected:
private:

};

template<typename TaskType>
EditTaskType<TaskType>::EditTaskType() {
}

template<typename TaskType>
EditTaskType<TaskType>::~EditTaskType() {
}

} // namespace page

#endif /* EDITTASKTYPE_H */

