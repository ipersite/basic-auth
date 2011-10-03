#include <iostream>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include "configurator.hpp"
#include "authenticator.hpp"

int main(int argc, char *argv[])
{
    if(argc < 2)
    {
        fprintf(stderr, "Error: no configuration file given.\n");
        exit(1);
    }
    FILE *test = fopen(argv[1], "r");
    if(test == NULL)
    {
        fprintf(stderr, "Error: unable to open given file.\n");
        exit(1);
    }
    fclose(test);
    configurator conf(argv[1]);
    logger log(conf.config["logPath"]);
    dbinfo dbi;
    dbi.host = conf.config["db-host"];
    dbi.name = conf.config["db-name"];
    dbi.user = conf.config["db-user"];
    dbi.pass = conf.config["db-pass"];
    authenticator auth(dbi, &log);
    while(1)
    {
        std::string username, password;
        std::cin >> username >> password;
        switch(auth.checkCreds(username, password))
        {
        case 0:
            std::cout << "OK" << std::endl;
            break;
        case 1: // Username doesn't exist.
            std::cout << "ERR" << std::endl;
            break;
        case 2: // Invalid password
            std::cout << "ERR" << std::endl;
            break;
        case 3: // User disabled
            std::cout << "ERR" << std::endl;
            break;
        case 255: // Empty username and password
            return 0;
        }
    }
    return 0;
}
