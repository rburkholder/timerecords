/* 
 * File:   Company.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on October 2, 2018, 6:54 PM
 */

#include <boost/uuid/uuid_generators.hpp>

#include "Company.h"

namespace model {

Company::Company( ) { }

Company::~Company( ) { }

void Company::Init() {
  static boost::uuids::random_generator uuidGenerator;
  id_company = uuidGenerator();
}

}  // namespace model