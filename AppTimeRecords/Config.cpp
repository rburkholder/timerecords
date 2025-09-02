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
 * File:    Config.cpp
 * Author:  raymond@burkholder.net
 * Project: AppTimeRecords
 * Created: September 2, 2025 16:14:15
 */

#include <fstream>
#include <exception>

#include <boost/log/trivial.hpp>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include "Config.hpp"

namespace {

  static const std::string sChoice_sAccount( "account" );

  template<typename T>
  bool parse( const std::string& sFileName, po::variables_map& vm, const std::string& name, bool bRequired, T& dest ) {
    bool bOk = true;
    if ( 0 < vm.count( name ) ) {
      dest = std::move( vm[name].as<T>() );
      if constexpr( std::is_same<T, config::Choices::vAccount_t>::value ) {
        for ( const auto& item: dest ) {
          BOOST_LOG_TRIVIAL(info) << name << " = " << item;
        }
      }
      else {
        BOOST_LOG_TRIVIAL(info) << name << " = " << dest;
      }
    }
    else {
      if ( bRequired ) {
        BOOST_LOG_TRIVIAL(error) << sFileName << " missing '" << name << "='";
        bOk = false;
      }
    }
  return bOk;
  }
}

namespace config {

bool Load( const std::string& sFileName, Choices& choices ) {

  bool bOk( true );

  try {

    po::options_description config( "time records config" );
    config.add_options()

    ( sChoice_sAccount.c_str(), po::value<Choices::vAccount_t>( &choices.m_vAccount ), "billing account" )
    ;
    po::variables_map vm;

    std::ifstream ifs( sFileName.c_str() );
    if ( !ifs ) {
      BOOST_LOG_TRIVIAL(error) << "time records config file " << sFileName << " does not exist";
      bOk = false;
    }
    else {
      po::store( po::parse_config_file( ifs, config), vm );

      bOk &= parse<Choices::vAccount_t>( sFileName, vm, sChoice_sAccount, true, choices.m_vAccount );
    }

  }
  catch( const std::exception& e ) {
    BOOST_LOG_TRIVIAL(error) << sFileName << " config parse error: " << e.what();
    bOk = false;
  }
  catch(...) {
    BOOST_LOG_TRIVIAL(error) << sFileName << " config unknown error";
    bOk = false;
  }

  return bOk;

}

} // namespace config