#include "logger.hpp"

logger::logger(std::string logPath = NULL)
{
    if(logPath.at(logPath.size()-1) != '/')
    {
        logPath.push_back('/');
    }
    char filename[FILENAME_MAX];
    unsigned int vnum = 0;
    do {
        sprintf(filename, "%sbasicauth-%d-%d.log", logPath.data(), (unsigned int)time(NULL), vnum);
        vnum++;
    } while(!checkFileExists(std::string(filename)));
    logFile = fopen(filename, "w");
    addLog(LOGINFO, "%s started with pid %u.", PACKAGE_STRING, getpid());
}

logger::~logger()
{
    addLog(LOGINFO, "Logger terminated.");
    fclose(logFile);
}

int logger::checkFileExists(std::string filename)
{
    struct stat stFileInfo;
    int fileStatus = stat(filename.data(), &stFileInfo);
    if(fileStatus == 0)
        return 0;
    else
        return 1;
}

void logger::addLog(int type, const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    char types[][5] = { "INFO", "WARN", "ERR", "AUTH" };
    char prestring[60];
    time_t rawtime;
    time(&rawtime);
    std::string curr(ctime(&rawtime));
    curr = curr.substr(0, curr.size()-1);
    sprintf(prestring, "[%s] %s: ", curr.c_str(), types[type]);
    std::string format = prestring;
    format.append(fmt);
    format.push_back('\n');
    char message[500];
    vsprintf(message, format.data(), args);
    fprintf(logFile, "%s", message);
    fflush(logFile);
    va_end(args);
}

void logger::forceFlush()
{
    fflush(logFile);
}
