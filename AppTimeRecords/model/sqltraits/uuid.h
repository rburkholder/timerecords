/* 
 * File:   uuid.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 2, 2018, 3:50 PM
 * From https://github.com/rburkholder/nodestar/blob/master/SqlTraits.h
 */

#ifndef UUID_H
#define UUID_H

#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/uuid/uuid_io.hpp>

#include <Wt/Dbo/Dbo>
#include <Wt/Dbo/WtSqlTraits>

namespace Wt {
namespace Dbo {

template<>
struct sql_value_traits<boost::uuids::uuid, void> {
  static const bool specialized = true;

  static const char *type(SqlConnection *conn, int size);
  static void bind(const boost::uuids::uuid& v, SqlStatement *statement, int column, int size);
  static bool read(boost::uuids::uuid& v, SqlStatement *statement, int column, int size);
};

// return a type for postgresql
inline const char *sql_value_traits<boost::uuids::uuid, void>::type(SqlConnection *conn, int size) {
//  return "uuid not null";
  return "uuid";
}

inline void sql_value_traits<boost::uuids::uuid, void>::bind(const boost::uuids::uuid& v, SqlStatement *statement, int column, int size) {
  statement->bind(column, boost::uuids::to_string( v ) );
//  if (v.isNull())
//    statement->bindNull(column);
//  else
//    statement->bind(column, v.toPosixTime(), SqlDateTime);
}

inline bool sql_value_traits<boost::uuids::uuid, void>::read(boost::uuids::uuid& v, SqlStatement *statement, int column, int size) {

  std::string d;
  if (statement->getResult(column, &d, size)) {
    boost::uuids::string_generator gen;
    v = gen(d);
    return true;
  } 
  else {
    boost::uuids::nil_generator gen; 
    v = gen();
    return false;
  }
}

} // namespace Dbo
} // namespace Wt

#endif /* UUID_H */

