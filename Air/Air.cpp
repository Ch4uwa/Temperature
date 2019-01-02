#include "pch.h"
#include "FileIO.h"


int main()
{
	const std::string filename{ "tempdata2.csv" };
	FileIO fileio(filename);
	fileio.printVall();
	std::cin.get();
}

