/* 
 * File:   AccountTaskType.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on October 8, 2018, 12:57 PM
 */

#include <boost/uuid/uuid_generators.hpp>

#include "AccountTaskType.h"

namespace model {

AccountTaskType::AccountTaskType( ) { }

AccountTaskType::~AccountTaskType( ) { }

void AccountTaskType::Init() {
  static boost::uuids::random_generator uuidGenerator;
  idTaskType = uuidGenerator();
}

} // namespace model
