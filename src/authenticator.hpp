#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <iostream>
#include <map>
#include "logger.hpp"
#include "include/yaml.h"
#include "md5.hpp"
#include <sqlite3.h>

class authenticator
{
public:
    authenticator(std::string _dbfile, logger *_logger);
    ~authenticator();
    int checkCreds(std::string username, std::string password);

private:
    sqlite3 *db;
    logger *log;
};

#endif
