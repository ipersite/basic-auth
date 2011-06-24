#ifndef CONF_H
#define CONF_H

#include <string>
#include <cstdio>
#include <cstdlib>

class configurator
{
public:
	configurator(const char *confFilePath);
	~configurator();
	void resetData();
	std::string logPath, credsFile;

private:
	int loadConf();
	std::string logPathIn, credsFileIn;
	FILE *confFile;
};

#endif
