#include "authenticator.hpp"

authenticator::authenticator(std::string _dbfile, logger *_logger)
{
    log = _logger;
    if(sqlite3_open_v2(_dbfile.data(), &db, SQLITE_OPEN_READONLY, NULL) != SQLITE_OK)
    {
        std::cerr << "Error: unable to open database file." << std::endl;
        exit(1);
    }
}

authenticator::~authenticator()
{
    sqlite3_close(db);
}

int authenticator::checkCreds(std::string username, std::string password)
{
    std::string checkStmt = "SELECT * FROM users WHERE username = '";
    checkStmt.append(sql_escape_string(username));
    checkStmt.append("';");
    std::cout << checkStmt << std::endl;
    sqlite3_stmt *checkStmtS;
    sqlite3_prepare_v2(db, checkStmt.c_str(), checkStmt.size()+1, &checkStmtS, NULL);
    if(sqlite3_step(checkStmtS) == SQLITE_ROW)
    {
        std::map<std::string,int> columns;
        for(unsigned int i = 0; i < sqlite3_column_count(checkStmtS); i++)
        {
            columns.insert(std::pair<std::string,int>(std::string(sqlite3_column_name(checkStmtS, i)), i));
        }
        /*for(std::map<std::string,int>::iterator i = columns.begin(); i != columns.end(); i++)
        {
            std::cout << i->first << " = " << i->second << std::endl;
        }*/
        std::stringstream logmsgs;
        if(std::string((const char*)sqlite3_column_text(checkStmtS, columns["password"])) != md5(password))
        {
            if(sqlite3_column_int(checkStmtS, columns["status"]) == 1) logmsgs << "User ";
            else if(sqlite3_column_int(checkStmtS, columns["status"]) == 2) logmsgs << "Admin ";
            logmsgs << username << " (" << sqlite3_column_text(checkStmtS, columns["realname"]) << ") tried logging in using a wrong password.";
            log->addLog(LOGAUTH, logmsgs.str().data());
            sqlite3_finalize(checkStmtS);
            return 2;
        }
        switch(sqlite3_column_int(checkStmtS, columns["status"]))
        {
        case 0:
            logmsgs << "User " << username << " (" << sqlite3_column_text(checkStmtS, columns["realname"]) << ") tried logging in (existing but disabled).";
            log->addLog(LOGAUTH, logmsgs.str().data());
            sqlite3_finalize(checkStmtS);
            return 3;
        case 1:
            logmsgs << "User " << username << " (" << sqlite3_column_text(checkStmtS, columns["realname"]) << ") logged in.";
            log->addLog(LOGAUTH, logmsgs.str().data());
            sqlite3_finalize(checkStmtS);
            return 0;
        case 2:
            logmsgs << "Admin " << username << " (" << sqlite3_column_text(checkStmtS, columns["realname"]) << ") logged in.";
            log->addLog(LOGAUTH, logmsgs.str().data());
            sqlite3_finalize(checkStmtS);
            return 0;
        }
    } else {
        log->addLog(LOGAUTH, "User %s tried logging in but doesn't exists.", username.c_str());
        sqlite3_finalize(checkStmtS);
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
                /*else if(sqlstmt.substr(i, 1) == "\"")
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
                }*/
        }
        return sqlstmt;
}
