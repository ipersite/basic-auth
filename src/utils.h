const char *getDataDirectory()
{
	char exePath[FILENAME_MAX];
	readlink("/proc/self/exe", exePath, sizeof(exePath));
	std::string exePathStr = exePath;
	return exePathStr.substr(0, exePathStr.find_last_of("/")).data();
}

std::string readFileLine(FILE *file, bool &last)
{
	std::string line;
	char curr;
	do
	{
		curr = fgetc(file);
		if(curr == '\n') break;
		else line.push_back(curr);
	} while (curr != EOF);
	if(curr == EOF)
	{
		last = true;
		fseek(file, 0L, SEEK_SET);
	}
	//std::cout << line << "\n";
	return line;
}
