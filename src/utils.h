#ifndef UTILS
#define UTILS

#include <string>

const char *getDataDirectory();
std::string readFileLine(FILE *file, bool &last);

#endif
