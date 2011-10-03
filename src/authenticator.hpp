#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <iostream>
#include <map>
#include "logger.hpp"
#include "include/yaml.h"
#include "md5.hpp"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

typedef struct {
    std::string host;
    std::string user;
    std::string pass;
    std::string name;
} dbinfo;

class authenticator
{
public:
    authenticator(dbinfo dbInfo, logger *_logger);
    ~authenticator();
    int checkCreds(std::string username, std::string password);

private:
    std::string sql_escape_string(std::string sqlstmt);
    logger *log;
    sql::Driver *driver;
    sql::Connection *con;
};

#endif
