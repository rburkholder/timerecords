/* 
 * File:      model/Login.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on October 2, 2018, 6:06 PM
 */

#include <boost/uuid/uuid_generators.hpp>

#include "Login.h"

namespace model {

Login::Login( ) { }

Login::~Login( ) { }

void Login::Init() {
  static boost::uuids::random_generator uuidGenerator;
  id_login = uuidGenerator();
}

} // namespace model