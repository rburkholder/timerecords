/* 
 * File:   ptime.h
 * Author:    raymond@burkholder.net
 * Copywrite: 2018 Raymond Burkholder
 * License:   GPL3
 *
 * Created on October 2, 2018, 3:56 PM
 * from https://github.com/rburkholder/nodestar/blob/master/SqlTraits.h
 */

#ifndef PTIME_H
#define PTIME_H

#include <Wt/Dbo/Dbo>

namespace Wt {
namespace Dbo {

inline const char *sql_value_traits<boost::posix_time::ptime, void>::type(SqlConnection *conn, int size) {
  return conn->dateTimeType(SqlDateTime);
}

inline void sql_value_traits<boost::posix_time::ptime, void>
::bind(const boost::posix_time::ptime& v, SqlStatement *statement, int column, int size) {
  if ( v.is_not_a_date_time() )
    statement->bindNull(column);
  else
    statement->bind(column, v, SqlDateTime);
}

inline bool sql_value_traits<boost::posix_time::ptime, void>
::read(boost::posix_time::ptime& v, SqlStatement *statement, int column, int size) {

  if (statement->getResult(column, &v, SqlDateTime)) {
    return true;
  } else {
    v = boost::posix_time::ptime();
    return false;
  }
}

}
}

#endif /* PTIME_H */

