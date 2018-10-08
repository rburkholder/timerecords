/* 
 * File:   CompanyTaskType.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on October 8, 2018, 12:58 PM
 */

#include <boost/uuid/uuid_generators.hpp>

#include "CompanyTaskType.h"

namespace model {

CompanyTaskType::CompanyTaskType( ) { }

CompanyTaskType::~CompanyTaskType( ) { }

void CompanyTaskType::Init() {
  static boost::uuids::random_generator uuidGenerator;
  idTaskType = uuidGenerator();
}

} // namespace model
