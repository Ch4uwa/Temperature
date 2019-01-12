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
	//myMapAvg.reserve(401);


	auto time1 = CSTART;
	std::ifstream inFile(filename);

	if (inFile)
	{
		std::string holder{};
		std::string date{};
		std::string place{};
		int hour{};
		int minute{};
		int seconds{};
		double temperature{};
		int humidity{};

		while (getline(inFile, date, ' '))
		{
			//getline(inFile, date, ' ');
			getline(inFile, holder, ':');
			hour = std::stoi(holder);
			getline(inFile, holder, ':');
			minute = std::stoi(holder);
			getline(inFile, holder, ',');
			seconds = std::stoi(holder);
			getline(inFile, place, ',');
			getline(inFile, holder, ',');
			temperature = stod(holder);
			getline(inFile, holder);
			humidity = stoi(holder);

			if (place == "Inne")
			{
				AirInfo airinfo(date, place, hour, minute, seconds, temperature, humidity);
				myMapInside.insert(std::make_pair(airinfo.getDate(), airinfo));
				countIn++;
			}
			else if (place == "Ute")
			{
				AirInfo airinfo(date, place, hour, minute, seconds, temperature, humidity);
				myMapOutside.insert(std::make_pair(airinfo.getDate(), airinfo));
				countOut++;
			}
		}
		inFile.close();

		avgVals(myMapInside, vInsideAvgInfo);
		avgVals(myMapOutside, vOutsideAvgInfo);

		tempDiff();

		auto end = CSTART;
		auto durStartUp = CDURATION(end - time1);

		LOG("Time taken: " << (durStartUp) << " microseconds\n");

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
	auto i = Map.find(Map.begin()->second.getDate());
	do
	{
		double tempTemp{}, humidTemp{};

		auto itr = Map.equal_range(i->second.getDate());
		auto it = itr.first;

		for (; it != itr.second; it++)
		{
			humidTemp += (it->second.getHumidity());
			tempTemp += (it->second.getTemp());
		}

		humidTemp = humidTemp / Map.count(i->second.getDate());
		tempTemp = tempTemp / Map.count(i->second.getDate());

		AirInfo airinfo(i->second.getDate(), i->second.getPlace(), tempTemp, humidTemp);
		toVec.emplace_back(airinfo);

		if (itr.second != Map.end())
		{
			std::advance(i, Map.count(i->second.getDate()));
		}
		else
		{
			i = Map.end();
		}
	} while (i != Map.end());
}

//Sort

// TODO sort by door open time

void FileIO::tempDiff()
{
	auto it = vInsideAvgInfo.begin();
	auto oit = vOutsideAvgInfo.begin();
	auto itend = vInsideAvgInfo.end();
	auto oitend = vOutsideAvgInfo.end();

	for (; it != itend; it++, oit++)
	{
		if (it->getDate() == oit->getDate())
		{
			it->setDiff((it->getAvgTemp() - oit->getAvgTemp()));
			oit->setDiff((it->getAvgTemp() - oit->getAvgTemp()));
		}
	}
}

// using stable sort from std lib, using mergesort.
void FileIO::sortInside(int sortBy)
{
	auto start = CSTART;
	auto it = vInsideAvgInfo.begin();
	auto itend = vInsideAvgInfo.end();

	switch (sortBy)
	{
	case eTEMP:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgTemp() > rhs.getAvgTemp();
			});
		break;
	case eHUMID:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgHumid() < rhs.getAvgHumid();
			});
		break;
	case eMOLD:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getRiskLevel() > rhs.getRiskLevel();
			});
		break;
	case eTEMPDIFF:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getTempDiff() > rhs.getTempDiff();
			});
		break;
	case eDATE:
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getDate() < rhs.getDate();
			});
		break;
	}
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG("Sort time taken: " << dur << " milliseconds");
}

void FileIO::sortOutside(int sortBy)
{
	auto start = CSTART;
	auto it = vOutsideAvgInfo.begin();
	auto itend = vOutsideAvgInfo.end();

	switch (sortBy)
	{
	case eTEMP:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgTemp() > rhs.getAvgTemp();
			});
		break;
	case eHUMID:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgHumid() < rhs.getAvgHumid();
			});
		break;
	case eMOLD:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getRiskLevel() > rhs.getRiskLevel();
			});
		break;
	case eTEMPDIFF:
		std::stable_sort(it, itend, [&](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getTempDiff() > rhs.getTempDiff();
			});
		break;
	case eDATE:
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getDate() < rhs.getDate();
			});
		break;
	}
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG("Sort time taken: " << dur << " milliseconds");
}

std::string FileIO::binarySearchInside(std::string& search)
{
	// Binary search

	return std::string();
}

std::string FileIO::binarySearchOutside(std::string& search)
{

	return std::string();
}

std::string FileIO::linearSearchInside(std::string& search)
{
	auto start = CSTART;
	auto it = vInsideAvgInfo.begin();

	while (it != vInsideAvgInfo.end())
	{
		if (search == it->getDate())
		{
			auto end = CSTART;
			auto dur = CDURATION(end - start);
			LOG("Search time taken: " << dur << " milliseconds");
			return it->avgToString();
		}
		it++;
	}
	return "Could not find " + search;
}

std::string FileIO::linearSearchOutside(std::string& search)
{

	return std::string();
}

// Search TODO choose inside or outside, Move print to function
// TODO Search
void FileIO::searchMapInside(const std::string & searchWord)
{
	auto itr = myMapInside.equal_range(searchWord);
	for (auto it = itr.first; it != itr.second; it++)
		LOG(it->first << "\n" << it->second.avgToString());
}

void FileIO::searchMapOutside(const std::string & searchWord)
{
	auto itr = myMapOutside.equal_range(searchWord);
	for (auto it = itr.first; it != itr.second; it++)
		LOG(it->first << "\n" << it->second.avgToString());
}

// Print function
void FileIO::printMap()
{
	for (int i = 0; i < 15 && i < vInsideAvgInfo.size(); i++)
	{
		LOG(vInsideAvgInfo[i].avgToString() << "\n");
	}
	auto iii = vOutsideAvgInfo.end();
	LOG("Last ele outside " << (iii - 1)->avgToString());
}


// Summer = 10 < temp, 5 days in row
// Spring = 0 < temp < 10, 7 days in row not before 15feb
// Metrological Winter Autumn (Sweden)
std::string FileIO::metroWinter()const
{
	// Metro Winter
	// Winter = temp < 0, 5 days in row
	const int days{ 5 }, tempLow{ 0 }, tempHigh{ 10 };
	int wDays{}, aDays{};
	auto itr = vOutsideAvgInfo.begin();
	for (; wDays < days && itr != vOutsideAvgInfo.end() - 1; itr++)
	{
		(itr->getAvgTemp() < tempLow) ? wDays++ : wDays = 0;
	}
	if (aDays == 5)
	{
		std::advance(itr, -5);
	}
	return (wDays == 5) ? ("Winter began " + itr->getDate()+"\n") : "Can't calculate Winter\n";
}
std::string FileIO::metroAutumn()
{
	// Metro Autumn
	// Autumn = 0 < temp < 10, 5 days in row not before 1 August
	const int days{ 5 }, tempLow{ 0 }, tempHigh{ 10 };
	int wDays{}, aDays{};
	auto itr = vOutsideAvgInfo.begin();
	for (; aDays < days && itr != vOutsideAvgInfo.end(); itr++)
	{
		if (itr->getMonth() > 7)
		{
			(itr->getAvgTemp() > tempLow && itr->getAvgTemp() < tempHigh) ? aDays++ : (aDays = 0);
		}
	}
	if (aDays == 5)
	{
		std::advance(itr, -5);
	}
	return (aDays == 5) ? ("Autumn began " + itr->getDate()+"\n") : "Can't calculate Autumn\n";
}

