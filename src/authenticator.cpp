#include "authenticator.h"

authenticator::authenticator(const char *credsfile = NULL, const char *logpath = NULL)
{
	credsFile = fopen(credsfile, "r");
	log = new logger(logpath);
	log->addLog(LOGINFO, "Authenticator initialized.");
	if(reloadCreds())
	{
		fprintf(stderr, "Unable to read credentials file.\n");
		exit(1);
	}
}

authenticator::~authenticator()
{
	log->addLog(LOGINFO, "Authenticator terminated.");
	fclose(credsFile);
	log->forceFlush();
	delete log;
}

int authenticator::reloadCreds()
{
	log->addLog(LOGINFO, "Reloading credentials...");
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
		log->addLog(LOGWARN, "No lines has been processes.");
		return 1;
	} else {
		log->addLog(LOGINFO, "%d lines has been processed.", lines);
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
	reloadCreds();
	int status;
	switch(status = compare(username, password))
	{
		case 0:
			log->addLog(LOGAUTH, "User %s has logged in.", username.data());
			return 0;
			break; // For security reasons
		case 1:
			log->addLog(LOGAUTH, "User %s doesn't exists.", username.data());
			return compare(username, password);
			break;
		case 2:
			log->addLog(LOGAUTH, "User %s exists, but supplied password is wrong.", username.data());
			break;
	}
	return status;
}
