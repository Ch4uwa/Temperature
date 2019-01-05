#include "pch.h"
#include "Program.h"
#include "FileIO.h"

Program::Program()
{
	
}


//const std::string filename{ "tempdata2.csv" };
//FileIO fileio(filename);
//std::cout << fileio.search("2016-11-04");
/*fileio.printVall();*/
//fileio.printVavg();
//fileio.printWarning();






void Program::run()
{
	const std::string filename{ "tempdata2.csv" };
	FileIO fileio(filename);
	fileio.printVavg();
}

void Program::printMenu()const
{
	// Open door, how long and when loongest.
	std::cout << "MENU\n"
		<< "1. Search date\n"
		<< "2. Sort Info\n" // highest temp diff inside outside, hottest -> coldest day, dryest -> wet day, lowest -> highest mold risk.
		<< "3. Winter Date\n"
		<< "4. Autumn Date\n"
		<< "5. Warnings\n";

}

char Program::input(std::string & choice)
{
	
	return char();
}
