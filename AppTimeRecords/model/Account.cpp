/* 
 * File:   Account.cpp
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on October 2, 2018, 1:31 PM
 */

#include <boost/uuid/uuid_generators.hpp>

#include "Account.h"

namespace model {

Account::Account( ) { 
  Init();
}

Account::~Account( ) { }

void Account::Init() {
  static boost::uuids::random_generator uuidGenerator;
  id_account = uuidGenerator();
  }

} // namespace model