#include "pch.h"
#include "Program.h"
#include "FileIO.h"

Program::Program()
{
}

void Program::run()
{
	const std::string filename{ "tempdata2.csv" };
	FileIO fileio(filename);
	printMenu(fileio);
	
}

void Program::printMenu(FileIO& f)
{
	std::string date{};
	int sortBy{};
	bool Quit = false;
	do
	{
		// Open door, how long and when loongest.
		std::cout << "> MENU\n"
			<< "> 1. Search date\n"
			<< "> 2. Sort\n" // highest temp diff inside outside, hottest -> coldest day, dryest -> wet day, lowest -> highest mold risk.
			<< "> 3. Winter Date\n"
			<< "> 4. Autumn Date\n" // första dagen.
			<< "> 5. Print\n"
			<< "> 0. Quit\n";

		switch (input())
		{
		case 1:
			LOG("Search");
			std::cout << "> Enter date to search for\n"
				<< "> 'yyyy-mm-dd'\n> ";
			std::cin >> date;
			
			break;
		case 2:
			LOG("Sort\n> 1. Temp\n> 2. Humid\n> 3. Mold index\n> 4. Diff\n> 5. Date");
			sortBy = input();
			f.sortInside(sortBy);
			break;
		case 3:
			LOG("Winter");
			LOG(f.getMetro(false));
			break;
		case 4:
			LOG("Autumn");
			LOG(f.getMetro(true));
			break;
		case 5:
			LOG("Print");
			f.printMap();
			break;
		case 0:
			LOG("Quit");
			Quit = true;
			break;
		default:
			break;
		}
	} while (!Quit);
}

int Program::input()
{
	int choice{};
	std::cout << "> ";
	while (!(std::cin >> choice))
	{
		std::cin.clear();
		std::cin.ignore(INT_MAX, '\n');
		std::cerr << "<ERROR> Input numeric value.\n";
		std::cout << "> ";
	}
	return choice;
}



