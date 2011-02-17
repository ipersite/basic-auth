#ifndef AUTH
#define AUTH

#include <string>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "logger.h"
#include "utils.h"

class authenticator
{
public:
	authenticator(const char *credsfile, const char *logpath);
	~authenticator();
	void forceReload();
	int checkCreds(std::string username, std::string password);
	
private:
	typedef struct {
	std::string username;
	std::string password;
	} credentials;
	std::vector<credentials> *credsList;
	int reloadCreds();
	FILE *credsFile;
	int compare(std::string username, std::string password);
	logger *log;
};

#endif
