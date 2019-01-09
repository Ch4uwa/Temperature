#include "pch.h"
#include "FileIO.h"

// Constructor
FileIO::FileIO(const std::string& filename)
{
	vInsideAvgInfo.reserve(vReserveAmountSplit);
	vOutsideAvgInfo.reserve(vReserveAmountSplit);
	// 350003
	myMapInside.reserve(150001);
	myMapOutside.reserve(150001);
	myMapAvg.reserve(401);

	std::ifstream inFile(filename);
	if (inFile)
	{
		std::string file{};
		while (getline(inFile, file))
		{
			if (file.find("Inne") != std::string::npos)
			{
				AirInfo airinfo(file);
				myMapInside.emplace(std::make_pair(airinfo.getDate(), airinfo));
				countIn++;
			}
			else
			{
				AirInfo airinfo(file);
				myMapOutside.emplace(std::make_pair(airinfo.getDate(), airinfo));
				countOut++;
			}
		}
		inFile.close();
		std::cout << "Done Reading " << countIn + countOut << " Rows, From " << filename << "\n";
		std::cout << "Running avgVals.\n";
		avgVals(myMapInside, vInsideAvgInfo);
		std::cout << "Done making average values.\n"
			<< myMapInside.size() << " Days from inside sensor\n" << vInsideAvgInfo.size();
		avgVals(myMapOutside, vOutsideAvgInfo);
		std::cout << "Done making average values.\n"
			<< myMapOutside.size() << " Days from outside sensor\n" << vOutsideAvgInfo.size();
	}
	else
	{
		std::cerr << "ERROR reading file: " << filename << "\n";
	}
}
// Destructor
FileIO::~FileIO()
{
}

// Make average values
void FileIO::avgVals(std::unordered_multimap<std::string, AirInfo>& Map, std::vector<AirInfo>& toVec)
{
	auto i = Map.begin();
	do
	{
		double tempTemp{};
		double humidTemp{};
		auto itr = Map.equal_range(i->second.getDate());
		auto it = itr.first;
		for (; it != itr.second; it++)
		{
			humidTemp += (it->second.getHumidity());
			tempTemp += (it->second.getTemp());
		}
		humidTemp = humidTemp / Map.count(i->second.getDate());
		tempTemp = tempTemp / Map.count(i->second.getDate());
		toVec.emplace_back(i->second.getDate(), i->second.getPlace(), tempTemp, humidTemp);
		i = itr.second;
	} while (i != Map.end());
	tempDiff();
}

//Sort
// TODO Sort by temp diff inside outside
// TODO sort by door open time

void FileIO::tempDiff()
{
	auto it = vInsideAvgInfo.begin();
	auto oit = vOutsideAvgInfo.begin();
	auto itend = vInsideAvgInfo.end();
	auto oitend = vOutsideAvgInfo.end();

	for (; it != itend; it++, oit++)
	{
		it->setDiff((it->getAvgTemp() - oit->getAvgTemp()));
		oit->setDiff((it->getAvgTemp() - oit->getAvgTemp()));
	}
}


void FileIO::sortInside(int sortBy)
{
	auto it = vInsideAvgInfo.begin();
	auto itend = vInsideAvgInfo.end();

	switch (sortBy)
	{
	case 1: // Sort by avg temperature
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgTemp() > rhs.getAvgTemp();
			});
		break;
	case 2: // Sort by avg humidity
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgHumid() > rhs.getAvgHumid();
			});
		break;
	case 3: // Sort by avg moldrisk
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getRiskLevel() > rhs.getRiskLevel();
			});
		break;
	case 4:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getTempDiff() > rhs.getTempDiff();
			});
		break;
	}
}

void FileIO::sortOutside(int sortBy)
{
	auto it = vOutsideAvgInfo.begin();
	auto itend = vOutsideAvgInfo.end();

	switch (sortBy)
	{
	case 1:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgTemp() > rhs.getAvgTemp();
			});
		break;
	case 2:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgHumid() > rhs.getAvgHumid();
			});
		break;
	case 3:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getRiskLevel() > rhs.getRiskLevel();
			});
		break;
	case 4:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getTempDiff() > rhs.getTempDiff();
			});
		break;
	}
}

// Search TODO choose inside or outside, Move print to function
void FileIO::searchMap(const std::string & searchWord)
{
	auto itr = myMapInside.equal_range(searchWord);
	for (auto it = itr.first; it != itr.second; it++)
		LOG(it->first << "\n" << it->second.avgToString());
}

// Print function
void FileIO::printMap() // Prints everything inside the map
{
	for (const auto& n : myMapInside)
	{
		auto itr = myMapInside.equal_range(n.second.getDate());
		for (auto it = itr.first; it != itr.second; it++)
		{
		}
		std::cout << n.second.toString();
	}
}

// bool avg sets average values(true) or all values(false), 
// bool in sets inside(true) or outside(false), bool warnings sets warnings true false
void FileIO::printV(bool avg, bool in, bool warnings) // Print Vector
{
	if (avg)
	{
		if (warnings&&avg)
		{
			for (const auto& ele : in ? vInsideAvgInfo : vOutsideAvgInfo)
			{
				if (ele.getRiskLevel() > 0)
				{
					ele.toString();
				}
			}
		}
		else
		{
			for (const auto& ele : in ? vInsideAvgInfo : vOutsideAvgInfo)
			{
				std::cout << ele.avgToString();
			}
		}
	}
	/*else
	{
		if (warnings)
		{
			for (const auto& ele : in ? vInfoInside : vInfoOutside)
			{
				if (ele.getRiskLevel() > 0)
				{
					ele.toString();
				}
			}
		}
		else
		{
			for (const auto& ele : in ? vInfoInside : vInfoOutside)
			{
				std::cout << ele.toString();
			}
		}
	}*/
}

// Metrology Winter(false) Autumn(true)
std::string FileIO::getMetro(bool Autumn)const
{
	const int days{ 5 }, wTemp{ 0 }, aTemp{ 10 };
	int i{ 0 };
	int wDays{}, aDays{};
	// Metro Winter, Autumn
	for (; (Autumn ? aDays : wDays) < days && i < vOutsideAvgInfo.size(); i++)
	{
		if (!Autumn && (vOutsideAvgInfo[i].getAvgTemp() >= wTemp))
		{
			wDays = 0;
		}
		if (!Autumn && (vOutsideAvgInfo[i].getAvgTemp() < wTemp))
		{
			wDays++;
		}
		if (Autumn && (vOutsideAvgInfo[i].getAvgTemp() >= aTemp))
		{
			aDays = 0;
		}
		if (Autumn && (vOutsideAvgInfo[i].getAvgTemp() < aTemp) && (vOutsideAvgInfo[i].getAvgTemp() > wTemp))
		{
			aDays++;
		}
	}
	return (Autumn ? aDays : wDays) == days ? vOutsideAvgInfo[i - 5].avgToString() : "Not yet!\n";
}



//int FileIO::hash(const std::string& date)
//{
//	int hash{};
//	for (size_t i = 0; i < date.length(); i++)
//	{
//		hash += date[i] * (1 + i);
//	}
//	return (hash % 199);
//}
