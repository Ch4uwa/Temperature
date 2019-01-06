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
			<< "> 2. Print Info\n" // highest temp diff inside outside, hottest -> coldest day, dryest -> wet day, lowest -> highest mold risk.
			<< "> 3. Winter Date\n"
			<< "> 4. Autumn Date\n"
			<< "> 5. Warnings\n"
			<< "> 0. Quit\n";

		switch (input())
		{
		case 1:
			LOG("Search");
			std::cout << "> Enter date to search for\n"
				<< "> 'yyyy-mm-dd'\n> ";
			std::cin >> date;

			f.searchMap(date);

			break;
		case 2:
			LOG("> Print Sort\n> 1. High to Low temp\n> 2. humid\n> 3. moldLevel\n");
			sortBy = input();
			f.sortInside(sortBy);
			f.printMap();

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
			LOG("Warnings");
			std::cout << ">  Show warnings\n"
				<< "> 1. All\n"
				<< "> 2. Inside\n"
				<< "> 3. Outside\n";
			switch (input())
			{
			case 1:
				f.printV(false, true, true);
				f.printV(false, false, true);
				break;
			case 2:
				f.printV(true, true, true);
				break;
			case 3:
				f.printV(true, false, true);
				break;
			default:
				break;
			}
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

void Program::subMenu(int& caseNr)
{
	switch (caseNr)
	{
	case 1:
		break;
	case 2:
		break;
	case 0:
		break;
	default:
		break;
	}
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



