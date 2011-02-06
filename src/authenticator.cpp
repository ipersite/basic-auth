#include <iostream>
#include "authenticator.h"
#include "utils.h"

authenticator::authenticator(const char *credsfile = NULL, bool logger = false)
{
	credsFile = fopen(credsfile, "r");
	loggerActive = logger;
	if(loggerActive)
	{
		char logFilePath[FILENAME_MAX];
		sprintf(logFilePath, "%s/log/log_%d.txt", getDataDirectory(), (int)time(NULL));
		logFile = fopen(logFilePath, "w");
		if(logFile == NULL)
		{
			fprintf(stderr, "Unable to open log file.\n");
			exit(1);
		}
		addLog("INFO: Program started.");
	}
	if(reloadCreds())
	{
		fprintf(stderr, "Unable to read credentials file.\n");
		exit(1);
	}
}

authenticator::~authenticator()
{
	fclose(credsFile);
	if(loggerActive) fclose(logFile);
}

void authenticator::addLog(std::string text)
{
	if(loggerActive)
	{
		fprintf(logFile, "[%d] %s\n", (int)time(NULL), text.data());
		fflush(logFile);
	}
}

int authenticator::reloadCreds()
{
	addLog("INFO: Reloading credentials...");
	//if(credsList != NULL) delete credsList;
	credsList = new std::vector<credentials>;
	int lines = 0;
	bool go = true;
	do
	{
		bool last;
		std::string line = readFileLine(credsFile, last);
		go = !last;
		lines++;
		std::string username, password;
		int seppos = line.find(":");
		username = line.substr(0, seppos);
		password = line.substr(seppos+1);
		credsList->push_back((credentials){username, password});
	} while(go);
	if(lines == 0)
	{
		addLog("ERROR: No lines has been processes.");
		return 1;
	}
	return 0;
}

void authenticator::forceReload()
{
	reloadCreds();
}

int authenticator::compare(std::string username, std::string password)
{
	int status = 0;
	if(username == "" && password == "") return 255;
	for(unsigned int i = 0; i < credsList->size(); i++)
	{
		if(!username.compare(credsList->at(i).username))
			if(!password.compare(credsList->at(i).password))
			{
				status = 0;
				break;
			} else {
				status = 2;
				break;
			}
		else status = 1;
	}
	return status;
}

int authenticator::checkCreds(std::string username, std::string password)
{
	switch(compare(username, password))
	{
		case 0:
			return 0;
			break; // For security reasons
		case 1:
			reloadCreds();
			return compare(username, password);
			break;
		case 2:
			reloadCreds();
			return compare(username, password);
			break;
		default:
			return compare(username, password);
	}
}
