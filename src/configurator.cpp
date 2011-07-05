#include "configurator.hpp"

configurator::configurator(std::string confFilePath = NULL)
{
    std::ifstream fin(confFilePath.c_str());
    YAML::Parser parser(fin);
    YAML::Node doc;
    parser.GetNextDocument(doc);
    // Do some checks on configuration file...
    std::string logPath;
    doc["log-path"] >> logPath;
    config.insert(std::pair<std::string,std::string>("logPath",logPath));
    std::string dbFile;
    doc["database"] >> dbFile;
    config.insert(std::pair<std::string,std::string>("dbFile",dbFile));
    fin.close();
}

configurator::~configurator()
{
}
