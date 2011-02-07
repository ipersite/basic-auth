#ifndef CONF
#define CONF

#include <string>

class configurator
{
public:
	configurator(char *confFile);
	~configurator();
	void resetData();
	std::string logPath, credsFile;

private:
	int loadConf();
	std::string logPathIn, credsFileIn;
};

#endif
