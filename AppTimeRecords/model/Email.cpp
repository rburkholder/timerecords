/* 
 * File:      model/email.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on October 2, 2018, 4:24 PM
 */

#include <boost/uuid/uuid_generators.hpp>

#include "Email.h"

namespace model {

Email::Email( ) { }

Email::~Email( ) { }

void Email::Init() {
  static boost::uuids::random_generator uuidGenerator;
  id_email = uuidGenerator();
}

}  // namespace model