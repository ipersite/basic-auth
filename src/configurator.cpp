#include "configurator.hpp"
#include "utils.hpp"

configurator::configurator(const char *confFilePath = NULL)
{
	confFile = fopen(confFilePath, "r");
	if(!confFile) exit(1);
	loadConf();
}

configurator::~configurator()
{
	fclose(confFile);
}

void configurator::resetData()
{
	credsFile = credsFileIn;
	logPath = logPathIn;
}

int configurator::loadConf()
{
	bool last = false;
	while(1)
	{
		std::string line = readFileLine(confFile, last), valueName, value;
		if(last) break;
		bool equal = false;
		for(int i = 0; i < line.size(); i++)
		{
			char curr = line.at(i);
			switch(curr)
			{
				case ' ':
					break;
				case '=':
					equal = true;
					break;
				default:
					if(!equal) valueName.push_back(curr);
					else value.push_back(curr);
					break;
			}
		}
		if(!valueName.compare("credentials_file")) credsFileIn = value;
		else if(!valueName.compare("log_path")) logPathIn = value;
		else; // nothing for now
		resetData();
	}
}
