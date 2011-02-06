#include <string>
#include <vector>
#include <ctime>
#include <cstdio>
#include <cstdlib>
#include <unistd.h>

class authenticator
{
public:
	authenticator(const char *credsfile, bool logger);
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
	FILE *credsFile, *logFile;
	bool loggerActive;
	void addLog(std::string text);
	int compare(std::string username, std::string password);
};
