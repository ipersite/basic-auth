#include "logger.h"

logger::logger(std::string logPath = NULL)
{
	char filename[FILENAME_MAX];
	do {
		sprintf(filename, "%sbasicauth_%d.log", logPath.data(), (int)time(NULL));
	} while(!checkFileExists(std::string(filename)));
	logFile = fopen(filename, "w");
	char logText[200];
	sprintf(logText, "%s started.", PACKAGE_STRING);
	addLog(LOGINFO, std::string(logText));
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

void logger::addLog(int type, std::string text)
{
	char types[][5] = { "INFO", "WARN", "ERR", "AUTH" };
	fprintf(logFile, "[%d] %s: %s\n", (int)time(NULL), types[type], text.data());
	fflush(logFile);
}

void logger::forceFlush()
{
	fflush(logFile);
}
