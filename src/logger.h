#ifndef LOGGER
#define LOGGER
#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <sys/stat.h> 
#include <config.h>
#include <cstdarg>

#define LOGINFO 0
#define LOGWARN 1
#define LOGERR 2
#define LOGAUTH 3

class logger
{
public:
	logger(std::string logPath);
	~logger();
	void addLog(int type, const char *fmt, ...);
	void forceFlush();
	
private:
	std::string format;
	int checkFileExists(std::string filename);
	FILE *logFile;
};

#endif
