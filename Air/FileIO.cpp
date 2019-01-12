#include "pch.h"
#include "FileIO.h"
#include <chrono>

// Constructor
FileIO::FileIO(const std::string& filename)
{
	vInsideAvgInfo.reserve(vReserveAmountSplit);
	vOutsideAvgInfo.reserve(vReserveAmountSplit);
	// 350003
	myMapInside.reserve(150001);
	myMapOutside.reserve(150001);
	//myMapAvg.reserve(401);


	std::ifstream inFile(filename);
	double divider{ 1000000.0 };
	if (inFile)
	{
		auto time1 = std::chrono::high_resolution_clock::now();
		std::string holder{};
		std::string date{};
		std::string place{};
		int hour{};
		int minute{};
		int seconds{};
		double temperature{};
		int humidity{};

		while (!inFile.eof())
		{
			getline(inFile, date, ' ');
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
				myMapInside.emplace(std::make_pair(airinfo.getDate(), airinfo));
				countIn++;
			}
			else
			{
				AirInfo airinfo(date, place, hour, minute, seconds, temperature, humidity);
				myMapOutside.emplace(std::make_pair(airinfo.getDate(), airinfo));
				countOut++;
			}
		}
		inFile.close();

		auto elapse1 = std::chrono::high_resolution_clock::now() - time1;
		auto a = std::chrono::duration_cast<std::chrono::microseconds>(elapse1).count() / divider;

		std::cout << "Done Reading! Time: " << (a) << "\n" << countIn + countOut
			<< " Rows, From " << filename << "\n";
		std::cout << "Running avgVals.\n";

		auto time2 = std::chrono::high_resolution_clock::now();

		avgVals(myMapInside, vInsideAvgInfo);

		auto elapse2 = std::chrono::high_resolution_clock::now() - time2;
		auto b = std::chrono::duration_cast<std::chrono::microseconds>(elapse2).count() / divider;

		std::cout << "Done making average values! Time: " << (b) << "\nInside map size "
			<< myMapInside.size() << "\nDays from inside sensor " << vInsideAvgInfo.size() << "\n";

		auto time3 = std::chrono::high_resolution_clock::now();

		avgVals(myMapOutside, vOutsideAvgInfo);

		auto elapse3 = std::chrono::high_resolution_clock::now() - time3;
		auto c = std::chrono::duration_cast<std::chrono::microseconds>(elapse3).count() / divider;

		std::cout << "Done making average values! Time: " << (c) << "\n"
			<< myMapOutside.size() << "\nDays from outside sensor " << vOutsideAvgInfo.size() << "\n";
		LOG("Calculating diff\n");

		auto time4 = std::chrono::high_resolution_clock::now();

		tempDiff();

		auto elapse4 = std::chrono::high_resolution_clock::now() - time4;
		auto d = std::chrono::duration_cast<std::chrono::microseconds>(elapse4).count() / divider;

		LOG("Diff Done! Time: " << (d)) << "\n";
		LOG("Total time: " << a + b + c + d);
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
	while (i != Map.end())
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

		AirInfo airinfo(i->second.getDate(), i->second.getPlace(), tempTemp, humidTemp);
		toVec.emplace_back(airinfo);

		if (itr.second != Map.end())
		{
			std::advance(i, Map.count(i->second.getDate()));
		}
		i = it;
		/*else
		{
			i = Map.end();
		}*/

	}
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
}

void FileIO::sortOutside(int sortBy)
{
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
}

// Search TODO choose inside or outside, Move print to function
// TODO Search
void FileIO::searchMap(const std::string & searchWord)
{
	auto itr = myMapInside.equal_range(searchWord);
	for (auto it = itr.first; it != itr.second; it++)
		LOG(it->first << "\n" << it->second.avgToString());
}

// Print function
void FileIO::printMap() // Prints everything inside the map
{
	/*for (const auto& n : myMapInside)
	{
		auto itr = myMapInside.equal_range(n.second.getDate());
		for (auto it = itr.first; it != itr.second; it++)
		{
		}
		std::cout << n.second.toString();
	}*/
	/*auto itr = vInsideAvgInfo.begin();
	if (std::is_sorted(itr, vInsideAvgInfo.end(), [&](const AirInfo& lhs, const AirInfo& rhs)
		{
			return (lhs.getDate() < rhs.getDate());
		}));*/

	for (int i = 0; i < 15 && i < vInsideAvgInfo.size(); i++)
	{
		LOG(vInsideAvgInfo[i].avgToString() << "\n");
	}
	auto iii = vOutsideAvgInfo.end();
	LOG((iii-1)->avgToString());
}

//TODO Search vec.

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
}

// Metrology Winter(false) Autumn(true)
std::string FileIO::getMetro(bool Autumn)const
{
	const int days{ 5 }, wTemp{ 0 }, aTemp{ 10 };
	unsigned int i{ 0 };
	int wDays{}, aDays{};
	// Metro Winter, Autumn
	for (; (Autumn ? aDays : wDays) < days && i < vOutsideAvgInfo.size(); i++)
	{
		// Metro Winter
		if (!Autumn && (vOutsideAvgInfo[i].getAvgTemp() >= wTemp))
		{
			wDays = 0;
		}
		if (!Autumn && (vOutsideAvgInfo[i].getAvgTemp() < wTemp))
		{
			wDays++;
		}
		// Metro Autumn
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
