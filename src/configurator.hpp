#ifndef CONF_H
#define CONF_H

#include <string>
#include <map>
#include <fstream>
#include "include/yaml.h"

class configurator
{
public:
        configurator(std::string confFilePath);
	~configurator();
        std::map<std::string,std::string> config;
};

#endif
