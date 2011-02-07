#include <iostream>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include "configurator.h"
#include "authenticator.h"

int main(int argc, char *argv[])
{
	if(argc < 2)
	{
		fprintf(stderr, "No credentials file given.\n");
		exit(1);
	}
	FILE *test = fopen(argv[1], "r");
	if(test == NULL)
	{
		fprintf(stderr, "Unable to open given file.\n");
		exit(1);
	}
	authenticator auth(argv[1]);
	while(1)
	{
		std::string username, password;
		std::cin >> username >> password;
		switch(auth.checkCreds(username, password))
		{
			case 0:
				std::cout << "OK\n";
				break;
			case 1: // Username doesn't exist.
				std::cout << "ERR\n";
				break;
			case 2: // Invalid password
				std::cout << "ERR\n";
				break;
			case 255: // Empty username and password
				exit(0);
				break;
			default:
				std::cout << "Non riconosciuto...\n";
				break;
		}
	}
	return 0;
}
