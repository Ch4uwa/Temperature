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
		LOG(f.metroWinter());
		LOG(f.metroAutumn());
		// Open door, how long and when loongest.
		std::cout << "> MENU\n"
			<< "> 1. Search date\n"
			<< "> 2. Print\n"
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
		case 2:
			LOG("Print");
			f.printMap();
			//TODO Print the 5 highest and lowest Temperatures
			//TODO Print the 5 driest and wet days
			//TODO Print Highest and lowest risk for mold
			//TODO Print Biggest and smallest temperature diff
			//TODO Print time door open and what happens
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



