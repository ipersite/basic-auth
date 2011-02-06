#include <cstdio>
#include <cstdlib>
#include <string>
#include <ctime>
#include <sys/stat.h> 

class logger
{
public:
	logger(std::string logPath);
	~logger();
	void addLog(std::string text);
	void forceFlush();
	
private:
	std::string format;
	int checkFileExists(std::string filename);
	FILE *logFile;
};
