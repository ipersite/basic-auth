#include "logger.h"

logger::logger(std::string logPath = NULL)
{
	char filename[FILENAME_MAX];
	do {
		sprintf(filename, "%sbasicauth_%d.log", logPath.data(), (int)time(NULL));
	} while(!checkFileExists(std::string(filename)));
	logFile = fopen(filename, "w");
	addLog(LOGINFO, "%s started.", PACKAGE_STRING);
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
	char prestring[30];
	sprintf(prestring, "[%d] %s: ", (int)time(NULL), types[type]);
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
