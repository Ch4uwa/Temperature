#include "pch.h"
#include "Program.h"

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
		LOG(f.getMetro());
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
			std::cout << "> Search for\n> 1. Inside data\n> 2. Outside data\n";
			switch (input())
			{
			case 1:
				std::cout << "> Enter date to search for\n"
					<< "> 'yyyy-mm-dd'\n> "; // TODO Check for valid date bfor entering function
				std::cin >> date;
				//TODO add search function for inside
				
				LOG(f.linearSearchInside(date));
				
				break;
			case 2:
				std::cout << "> Enter date to search for\n"
					<< "> 'yyyy-mm-dd'\n> ";
				std::cin >> date;
				//TODO add search function for outside
				break;
			default:
				std::cout << "Only (1) or (2) is a valid choice.\n";
				break;
			}
			break;
		case 2: // TODO Make this the print by instead of sort by.
			std::cout << "Sort\n> 1. Highest -> Lowest Temperature\n> 2. Lowest -> Highest Humidity\n"
				<< "> 3. Lowest -> Highest Moldrisk\n > 4. Highest -> Lowest Temperature Difference\n"
				<< "> 5. Date by order\n";
			sortBy = input();
			if (sortBy == 4)
			{
				f.sortInside(sortBy);
				f.sortOutside(sortBy);

			}
			std::cout << "> Sort\n> 1. Inside data\n> 2. Outside data\n";
			switch (input())
			{
			case 1:
				f.sortInside(sortBy);
				break;
			case 2:
				f.sortOutside(sortBy);
				break;
			default:
				break;
			}
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
		std::cin.ignore(STREAM_MAX, '\n');
		std::cerr << "<ERROR> Input numeric value.\n";
		std::cout << "> ";
	}
	return choice;
}



