#include "authenticator.hpp"

authenticator::authenticator(dbinfo dbInfo, logger *_logger)
{
    log = _logger;
    driver = get_driver_instance();
    con = driver->connect(dbInfo.host, dbInfo.user, dbInfo.pass);
    con->setSchema(dbInfo.name);
}

authenticator::~authenticator()
{
    con->close();
}

int authenticator::checkCreds(std::string username, std::string password)
{
    if(username.size() == 0 && password.size() == 0) return 255;
    std::string checkStmt = "SELECT * FROM users WHERE username = '";
    checkStmt.append(sql_escape_string(username));
    checkStmt.append("';");
    //std::cout << checkStmt << std::endl;
    sql::Statement *checkStmtM = con->createStatement();
    sql::ResultSet *result;
    sql::ResultSetMetaData *meta;
    result = checkStmtM->executeQuery(checkStmt);
    meta = result->getMetaData();
    if(result->next())
    {
        std::stringstream logmsgs;
        if(result->getString("password") != md5(password))
        {
            if(result->getInt("status") == 1) logmsgs << "User '";
            else if(result->getInt("status") == 2) logmsgs << "Admin '";
            logmsgs << "User '" << username << "' (" << result->getString("realname") << ") tried logging in using a wrong password.";
            log->addLog(LOGAUTH, logmsgs.str().data());
            checkStmtM->close();
            return 2;
        }
        switch(result->getInt("status"))
        {
        case 0:
            logmsgs << "User '" << username << "' (" << result->getString("realname") << ") tried logging in (existing but disabled).";
            log->addLog(LOGAUTH, logmsgs.str().data());
            checkStmtM->close();
            return 3;
        case 1:
            logmsgs << "User '" << username << "' (" << result->getString("realname") << ") logged in.";
            log->addLog(LOGAUTH, logmsgs.str().data());
            checkStmtM->close();
            return 0;
        case 2:
            logmsgs << "Admin '" << username << "' (" << result->getString("realname") << ") logged in.";
            log->addLog(LOGAUTH, logmsgs.str().data());
            checkStmtM->close();
            return 0;
        }
    } else {
        log->addLog(LOGAUTH, "User '%s' tried logging in but doesn't exists.", username.c_str());
        checkStmtM->close();
        return 1;
    }
}

std::string authenticator::sql_escape_string(std::string sqlstmt)
{
        for(unsigned int i = 0; i < sqlstmt.size(); i++)
        {
                if(sqlstmt.substr(i, 1) == "'")
                {
                        sqlstmt.insert(i, 1, '\'');
                        i++;
                }
                else if(sqlstmt.substr(i, 1) == "\"")
                {
                        sqlstmt.insert(i, 1, '\\');
                        i++;
                }
                else if(sqlstmt.substr(i, 2) == "\\n")
                {
                        sqlstmt.insert(i, 1, '\\');
                        i += 2;
                }
                else if(sqlstmt.substr(i, 2) == "\\r")
                {
                        sqlstmt.insert(i, 1, '\\');
                        i += 2;
                }
                else if(sqlstmt.substr(i, 1) == "\\")
                {
                        sqlstmt.insert(i, 1, '\\');
                        i++;
                }
                else if(sqlstmt.substr(i, 4) == "\\x00")
                {
                        sqlstmt.insert(i, 1, '\\');
                        i += 4;
                }
                else if(sqlstmt.substr(i, 4) == "\\x1a")
                {
                        sqlstmt.insert(i, 1, '\\');
                        i += 4;
                }
        }
        return sqlstmt;
}
