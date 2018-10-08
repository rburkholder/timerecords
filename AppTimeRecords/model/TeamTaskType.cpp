/* 
 * File:   TeamTaskType.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on October 8, 2018, 12:58 PM
 */

#include <boost/uuid/uuid_generators.hpp>

#include "TeamTaskType.h"

namespace model {

TeamTaskType::TeamTaskType( ) { }

TeamTaskType::~TeamTaskType( ) { }

void TeamTaskType::Init() {
  static boost::uuids::random_generator uuidGenerator;
  idType = uuidGenerator();
}

} // namespace model
