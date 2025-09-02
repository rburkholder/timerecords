/************************************************************************
 * Copyright(c) 2025, One Unified. All rights reserved.                 *
 * email: info@oneunified.net                                           *
 *                                                                      *
 * This file is provided as is WITHOUT ANY WARRANTY                     *
 *  without even the implied warranty of                                *
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.                *
 *                                                                      *
 * This software may not be used nor distributed without proper license *
 * agreement.                                                           *
 *                                                                      *
 * See the file LICENSE.txt for redistribution information.             *
 ************************************************************************/

/*
 * File:    Config.hpp
 * Author:  raymond@burkholder.net
 * Project: AppTimeRecords
 * Created: September 2, 2025 16:14:15
 */

#pragma once

#include <string>
#include <vector>

namespace config {

struct Choices {

  using vAccount_t = std::vector<std::string>;
  vAccount_t m_vAccount; // tracking multiple billings

};

bool Load( const std::string& sFileName, Choices& );

} // namespace config
