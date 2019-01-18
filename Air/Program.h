#ifndef PROGRAM_H
#define PROGRAM_H
#include "FileIO.h"


class Program
{
private:

public:
	Program();
	~Program() {};

	void run();
	int input();
	void printMenu(FileIO& f);
};

#endif // !PROGRAM_H
