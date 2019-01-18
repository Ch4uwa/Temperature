#include "pch.h"
#include "Program.h"

Program::Program()
{
}

void Program::run()
{
	const std::string filename{ "tempdata4.csv" };
	FileIO fileio(filename);
	printMenu(fileio);
	LOG(filename);
}

void Program::printMenu(FileIO& f)
{
	std::string date{};
	int sortBy{};
	bool Quit = false;

	do
	{

		std::cout << "\n> =============================="
			<< "\n> " << f.getMetroAutumn()
			<< "\n> " << f.getMetroWinter()
			<< "\n> ==============================\n"
			<< "> MENU\n"
			<< "> 1. Search date\n"
			<< "> 2. Print\n"
			<< "> 0. Quit\n"
			<< "> ==============================\n";

		switch (input())
		{
		case 1:
			std::cout << "> Search for\n> 1. Inside data\n> 2. Outside data\n";
			switch (input())
			{
			case 1:
				std::cout << "> 1. Use binary search\n"
					<< "> 2. Use linear search\n"
					<< "> 3. Use hash search\n";
				switch (input())
				{
				case 1: // BINARY
					std::cout << "> Enter date to search for\n"
						<< "> 'yyyy-mm-dd'\n> ";
					std::cin >> date;
					while (!(date.length() == 10))
					{
						std::cout << "> Date format 'yyyy-mm-dd'\n> ";
						std::cin >> date;
						std::cin.ignore();
					}

					f.sortInside(5);
					std::cout << f.binarySearchInside(date);
					break;
				case 2: // LINEAR
					std::cout << "> Enter date to search for\n"
						<< "> 'yyyy-mm-dd'\n> ";
					std::cin >> date;
					while (!(date.length() == 10))
					{
						std::cout << "> Date format 'yyyy-mm-dd'\n> ";
						std::cin >> date;
						std::cin.ignore();
					}

					std::cout << f.linearSearchInside(date);
					break;
				case 3: // HASH
					std::cout << "> Enter date to search for\n"
						<< "> 'yyyy-mm-dd'\n> ";
					std::cin >> date;
					while (!(date.length() == 10))
					{
						std::cout << "> Date format 'yyyy-mm-dd'\n> ";
						std::cin >> date;
						std::cin.ignore();
					}
					std::cout << f.searchMapInside(date);
					break;

				default:
					std::cerr << "Only (1) - (3) is a valid choice.\n";
					break;
				}

				break;
			case 2:
				std::cout << "> 1. Use binary search\n"
					<< "> 2. Use linear search\n"
					<< "> 3. Use hash search\n";
				switch (input())
				{
				case 1:
					std::cout << "> Enter date to search for\n"
						<< "> 'yyyy-mm-dd'\n> ";
					std::cin >> date;
					while (!(date.length() == 10))
					{
						std::cout << "> Date format 'yyyy-mm-dd'\n> ";
						std::cin >> date;
						std::cin.ignore();
					}
					std::cout << f.binarySearchOutside(date);
					break;
				case 2:
					std::cout << "> Enter date to search for\n"
						<< "> 'yyyy-mm-dd'\n> ";
					std::cin >> date;
					while (!(date.length() == 10))
					{
						std::cout << "> Date format 'yyyy-mm-dd'\n> ";
						std::cin >> date;
						std::cin.ignore();
					}

					std::cout << f.linearSearchOutside(date);
					break;
				case 3:
					std::cout << "> Enter date to search for\n"
						<< "> 'yyyy-mm-dd'\n> ";
					std::cin >> date;
					while (!(date.length() == 10))
					{
						std::cout << "> Date format 'yyyy-mm-dd'\n> ";
						std::cin >> date;
						std::cin.ignore();
					}
					std::cout << f.searchMapInside(date);
					break;

				default:
					std::cerr << "Only (1) - (3) is a valid choice.\n";
					break;
				}

				break;
			default:
				std::cerr << "Only (1) or (2) is a valid choice.\n";
				break;
			}
			break;
		case 2:
			std::cout << "> Print\n> 1. Inside data\n> 2. Outside data\n> 3. Top 5 Temp difference\n";

			switch (input())
			{
			case 1:// Inside
				std::cout << "> Print by\n"
					<< "> 1. High to low temp\n"
					<< "> 2. Dry to humid\n"
					<< "> 3. High to low mold risk\n"
					<< "> 4. Date\n";

				sortBy = input();
				/*std::cin.ignore(STREAM_MAX, '\n');*/
				switch (sortBy)
				{
				case 1:// Temp
					f.sortInside(sortBy);
					break;
				case 2:// Humid
					f.sortInside(sortBy);
					break;
				case 3:// Mold
					f.sortInside(sortBy);
					break;
				case 4:// Date
					f.sortInside(sortBy);
					break;

				default:
					std::cerr << "Only (1) - (4) is a valid choice.\n";
					break;
				}
			case 2:// Outside
				std::cout << "> Print by\n"
					<< "> 1. High to low temp\n"
					<< "> 2. Dry to humid\n"
					<< "> 3. High to low mold risk\n"
					<< "> 4. Date\n";

				sortBy = input();
				/*std::cin.ignore(STREAM_MAX, '\n');*/
				switch (sortBy)
				{
				case 1:// Temp
					f.sortOutside(sortBy);
					break;
				case 2:// Humid
					f.sortOutside(sortBy);
					break;
				case 3:// Mold
					f.sortOutside(sortBy);
					break;
				case 4:// Date
					f.sortOutside(sortBy);
					break;

				default:
					std::cerr << "Only (1) - (4) is a valid choice.\n";
					break;
				}
			case 3:
				f.printTempDiff();
				break;
			default:
				std::cerr << "Only (1) - (3) is a valid choice.\n";
				break;
			}

			//TODO Print time door open and what happens
			break;
		case 0:
			Quit = true;
			// Write to file
			break;
		default:
			std::cout << "Make a valid choice.\n";
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

