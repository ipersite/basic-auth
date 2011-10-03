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
    std::string dbuser, dbpass, dbname, dbhost;
    doc["database"]["host"] >> dbhost;
    doc["database"]["username"] >> dbuser;
    doc["database"]["password"] >> dbpass;
    doc["database"]["database"] >> dbname;
    config.insert(std::pair<std::string,std::string>("db-name",dbname));
    config.insert(std::pair<std::string,std::string>("db-user",dbuser));
    config.insert(std::pair<std::string,std::string>("db-pass",dbpass));
    config.insert(std::pair<std::string,std::string>("db-host",dbhost));
    fin.close();
}

configurator::~configurator()
{
}
