#pragma once
#include "FileIO.h"

class Program
{
private:

public:
	Program();
	~Program() {};

	void run();
	void printMenu(FileIO& f);
	void subMenu(int & caseNr);
	int input();
	
};

