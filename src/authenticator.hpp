#ifndef AUTH_H
#define AUTH_H

#include <string>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <unistd.h>
#include "logger.hpp"
#include "utils.hpp"

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
