/* 
 * File:   Team.cpp
  * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 * 
 * Created on October 2, 2018, 6:40 PM
 */

#include <boost/uuid/uuid_generators.hpp>

#include "Team.h"

namespace model {

Team::Team( ) { 
  Init();
}

Team::~Team( ) { }

void Team::Init() {
  static boost::uuids::random_generator uuidGenerator;
  id_team = uuidGenerator();
}

}  // namespace model