#include "pch.h"
#include "FileIO.h"

// Constructor
FileIO::FileIO(const std::string& filename)
{
	vInsideAvgInfo.reserve(vReserveAmountSplit);
	vOutsideAvgInfo.reserve(vReserveAmountSplit);
	myMapInside.reserve(150001);
	myMapOutside.reserve(150001);
	mapInsideAvgData.reserve(199);
	mapOutsideAvgData.reserve(199);

	auto time1 = CSTART;
	std::ifstream inFile(filename);

	if (inFile)
	{
		std::string holder{};
		std::string date{};
		std::string place{};
		std::string time{};
		double temperature{};
		int humidity{};

		while (getline(inFile, date, ' '))
		{
			getline(inFile, time, ',');
			getline(inFile, place, ',');
			getline(inFile, holder, ',');
			temperature = stod(holder);
			getline(inFile, holder);
			humidity = stoi(holder);

			if (place == "Inne" && date != "")
			{
				AirInfo airinfo(date, place, time, temperature, humidity);
				myMapInside.insert(std::make_pair(airinfo.getDate(), airinfo));
			}
			else if (place == "Ute" && date != "")
			{
				AirInfo airinfo(date, place, time, temperature, humidity);
				myMapOutside.insert(std::make_pair(airinfo.getDate(), airinfo));
			}
		}
		inFile.close();

		avgVals(myMapInside, vInsideAvgInfo);
		avgVals(myMapOutside, vOutsideAvgInfo);

		insideByDate = true;
		outsideByDate = true;

		tempDiff();
		s_metroAutumn = metroAutumn();
		s_metroWinter = metroWinter();
		copyToMap();

		auto end = CSTART;
		auto durStartUp = CDURATION(end - time1);

		LOG("Time taken: " << (durStartUp) << " microsecs\n");
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

/************* PRIVATE METHODS *************/

// Make average values
template<typename T1, typename T2>
void FileIO::avgVals(T1& Map, T2& toVec)
{
	auto i = Map.find(Map.begin()->second.getDate());
	do
	{
		double tempTemp{}, humidTemp{}, tempMold{};

		auto itr = Map.equal_range(i->second.getDate());
		auto it = itr.first;

		for (; it != itr.second; it++)
		{
			humidTemp += (it->second.getHumidity());
			tempTemp += (it->second.getTemp());
			tempMold += (it->second.getRiskLevel());

		}

		humidTemp = humidTemp / Map.count(i->second.getDate());
		tempTemp = tempTemp / Map.count(i->second.getDate());
		tempMold = tempMold / Map.count(i->second.getDate());

		AirInfo airinfo(i->second.getDate(), i->second.getPlace(), tempTemp, humidTemp, tempMold);
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

// Copy average value to Hash(Map)
void FileIO::copyToMap()
{
	auto start = CSTART;
	for (const auto& a : vInsideAvgInfo)
	{
		mapInsideAvgData.emplace(a.getDate(), a);
	}
	for (const auto& n : vOutsideAvgInfo)
	{
		mapOutsideAvgData.emplace(n.getDate(), n);
	}
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG(dur << " Microseconds");
}

// Calculate temp diff at same day. inside / outside.
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
			auto sum = it->getAvgTemp() - oit->getAvgTemp();
			sum < 0 ? (it->setDiff((-sum)), oit->setDiff((-sum))) : (it->setDiff((sum)), oit->setDiff((sum)));
		}
	}
}

// Print methods
// Print first 5 elements
void FileIO::print5(const std::vector<AirInfo>& vec)const
{
	auto it = vec.begin();
	auto it5 = vec.begin();
	std::advance(it5, 5);
	for (; it < it5; it++)
	{
		std::cout << it->avgToString();
	}
}

// Print last 5 elements
void FileIO::print5Rev(const std::vector<AirInfo>& vec)const
{
	auto rit = vec.rbegin();
	auto rit5 = vec.rbegin();
	std::advance(rit5, 5);
	for (; rit < rit5; rit++)
	{
		std::cout << rit->avgToString();
	}
}

// Metrological Winter Autumn (Sweden)
// Summer = 10 < temp, 5 days in row
// Spring = 0 < temp < 10, 7 days in row not before 15feb
// Metro Winter
// Winter = temp < 0, 5 days in row
std::string FileIO::metroWinter()const
{
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
	return (wDays == 5) ? ("Winter began " + itr->getDate()) : "Can't calculate Winter";
}

// Metro Autumn
// Autumn = 0 < temp < 10, 5 days in row not before 1 August
std::string FileIO::metroAutumn()const
{
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
	return (aDays == 5) ? ("Autumn began " + itr->getDate()) : "Can't calculate Autumn";
}


/************* PUBLIC METHODS *************/

// Print Temp Diff
void FileIO::printTempDiff()
{
	auto start = CSTART;
	auto it = vInsideAvgInfo.begin();
	auto oit = vOutsideAvgInfo.begin();
	auto itend = vInsideAvgInfo.end();
	auto oitend = vOutsideAvgInfo.end();

	auto it5 = it;
	auto oit5 = oit;
	auto rit = vInsideAvgInfo.rbegin();
	auto roit = vOutsideAvgInfo.rbegin();
	auto rit5 = rit;
	auto roit5 = roit;
	std::advance(it5, 5);
	std::advance(oit5, 5);
	std::advance(rit5, 5);
	std::advance(roit5, 5);

	std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
		{
			return lhs.getTempDiff() > rhs.getTempDiff();
		});

	std::stable_sort(oit, oitend, [](const AirInfo& lhs, const AirInfo& rhs)
		{
			return lhs.getTempDiff() > rhs.getTempDiff();
		});

	insideByDate = false;
	outsideByDate = false;
	std::cout << "> FIVE HIGHEST\n";
	for (; it < it5 && oit < oit5; it++, oit++)
	{
		std::cout << "> ============================================================\n"
			<< "> Placement: " << std::setw(22) << std::left << it->getPlace() << "Placement: " << oit->getPlace() << "\n"
			<< "> Date: " << std::setw(27) << std::left << it->getDate() << "Date: " << oit->getDate() << "\n"
			<< std::setprecision(1) << std::fixed
			<< "> Temperature diff: " << std::setw(15) << std::left << it->getTempDiff() << "Temperature diff : " << oit->getTempDiff() << "\n"
			<< std::showpos
			<< "> Temperature: " << std::setw(20) << std::left << it->getAvgTemp() << "Temperature: " << oit->getAvgTemp() << "\n"
			<< std::noshowpos << "> ============================================================\n";
	}
	std::cout << "> FIVE LOWEST\n";
	for (; rit < rit5 && roit < roit5; rit++, roit++)
	{
		std::cout << "> ============================================================\n"
			<< "> Placement: " << std::setw(22) << std::left << rit->getPlace() << "Placement: " << roit->getPlace() << "\n"
			<< "> Date: " << std::setw(27) << std::left << rit->getDate() << "Date: " << roit->getDate() << "\n"
			<< std::setprecision(1) << std::fixed
			<< "> Temperature diff: " << std::setw(15) << std::left << rit->getTempDiff() << "Temperature diff : " << roit->getTempDiff() << "\n"
			<< std::showpos
			<< "> Temperature: " << std::setw(20) << std::left << rit->getAvgTemp() << "Temperature: " << roit->getAvgTemp() << "\n"
			<< std::noshowpos << "> ============================================================\n";
	}

	auto end = CSTART;
	auto dur = CDURATION(end - start);
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
	{
		start = CSTART;
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgTemp() > rhs.getAvgTemp();
			});
		insideByDate = false;
		std::cout << "> Five days with highest temperature\n";
		print5(vInsideAvgInfo);
		std::cout << "> Five days with lowest temperature\n";
		print5Rev(vInsideAvgInfo);
		break;
	}
	case eHUMID:
	{
		start = CSTART;
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgHumid() < rhs.getAvgHumid();
			});
		insideByDate = false;
		std::cout << "> Five days with lowest humidity\n";
		print5(vInsideAvgInfo);
		std::cout << "> Five days with highest humidity\n";
		print5Rev(vInsideAvgInfo);
		break;
	}
	case eMOLD:
	{
		start = CSTART;
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getRiskLevel() > rhs.getRiskLevel();
			});
		insideByDate = false;
		std::cout << "> Five days with highest mold risk\n";
		print5(vInsideAvgInfo);
		std::cout << "> Five days with lowest mold risk\n";
		print5Rev(vInsideAvgInfo);
		break;
	}
	case eDATE:
		start = CSTART;
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getDate() < rhs.getDate();
			});
		insideByDate = true;
		std::cout << "> Five days with highest\n";
		print5(vInsideAvgInfo);
		std::cout << "> Five days with lowest\n";
		print5Rev(vInsideAvgInfo);
		break;
	}
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG("Sort time taken: " << dur << " seconds");
}
void FileIO::sortOutside(int sortBy)
{
	auto start = CSTART;
	auto it = vOutsideAvgInfo.begin();
	auto itend = vOutsideAvgInfo.end();

	switch (sortBy)
	{
	case eTEMP:
	{
		start = CSTART;
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgTemp() > rhs.getAvgTemp();
			});
		outsideByDate = false;
		std::cout << "> Five days with highest temperature\n";
		print5(vOutsideAvgInfo);
		std::cout << "> Five days with lowest temperature\n";
		print5Rev(vOutsideAvgInfo);
		break;
	}
	case eHUMID:
	{
		start = CSTART;
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getAvgHumid() < rhs.getAvgHumid();
			});
		outsideByDate = false;
		std::cout << "> Five days with lowest humidity\n";
		print5(vOutsideAvgInfo);
		std::cout << "> Five days with highest humidity\n";
		print5Rev(vOutsideAvgInfo);
		break;
	}
	case eMOLD:
	{
		start = CSTART;
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getRiskLevel() > rhs.getRiskLevel();
			});
		outsideByDate = false;
		std::cout << "> Five days with highest mold risk\n";
		print5(vOutsideAvgInfo);
		std::cout << "> Five days with lowest mold risk\n";
		print5Rev(vOutsideAvgInfo);
		break;
	}
	case eDATE:
		start = CSTART;
		std::stable_sort(it, itend, [](const AirInfo& lhs, const AirInfo& rhs)
			{
				return lhs.getDate() < rhs.getDate();
			});
		break;
		outsideByDate = true;
		std::cout << "> Five first days\n";
		print5(vOutsideAvgInfo);
	}
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG("Sort time taken: " << dur << " seconds");
}

// Search methods
// Binary search
std::string FileIO::binarySearchInside(const std::string& search)
{
	auto start = CSTART;
	if (!insideByDate)
	{
		LOG("Not by date");
		sortInside(4);
	}
	size_t first = 0;
	auto last = vInsideAvgInfo.size() - 1;
	auto mid = (first + last) / 2;

	while (!(search == vInsideAvgInfo[mid].getDate()))
	{
		if (search > vInsideAvgInfo[mid].getDate())
		{
			first = (mid + 1);
		}
		else if (search < vInsideAvgInfo[mid].getDate())
		{
			last = (mid - 1);
		}
		else
		{
			if (!(vInsideAvgInfo[mid].getDate() == search))
			{
				return "Can't find that date.\n";
			}
		}
		mid = (first + last) / 2;
	}
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG("Binary time taken: " << dur << " microseconds\n");
	return vInsideAvgInfo[mid].avgToString();
}

std::string FileIO::binarySearchOutside(const std::string& search)
{
	auto start = CSTART;
	if (!outsideByDate)
	{
		LOG("Not by date");
		sortOutside(4);
	}

	size_t first{};
	auto last = vOutsideAvgInfo.size() - 1;
	auto mid = (first + last) / 2;

	while (!(search == vOutsideAvgInfo[mid].getDate()))
	{
		if (search > vOutsideAvgInfo[mid].getDate())
		{
			first = (mid + 1);
		}
		else if (search < vOutsideAvgInfo[mid].getDate())
		{
			last = (mid - 1);
		}
		else
		{
			if (!(vOutsideAvgInfo[mid].getDate() == search))
			{
				return "Can't find that date.\n";
			}
		}
		mid = (first + last) / 2;
	}
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG("Binary time taken: " << dur << " microseconds\n");
	return vOutsideAvgInfo[mid].avgToString();
}

// Linear search
std::string FileIO::linearSearchInside(const std::string& search)
{
	auto start = CSTART;
	auto it = vInsideAvgInfo.begin();
	auto rit = vInsideAvgInfo.rbegin();
	auto mid = vInsideAvgInfo.size() / 2;


	for (unsigned short i{ 0 }; it->getDate() != search && rit->getDate() != search && i != (1 + mid); i++, it++, rit++)
		if (it->getDate() == search || rit->getDate() == search)
		{
			auto end = CSTART;
			auto dur = CDURATION(end - start);
			LOG("<Linear> Found time taken: " << dur << " microseconds");
			return (it->getDate() == search) ? "it " + it->avgToString() : "rit " + rit->avgToString();
		}

	auto end = CSTART;
	auto dur = CDURATION(end - start);

	return "<Linear>: " + std::to_string(dur) + " microseconds, " + " to not find " + search;


}

std::string FileIO::linearSearchOutside(const std::string& search)
{
	auto start = CSTART;
	auto it = vOutsideAvgInfo.begin();
	auto rit = vOutsideAvgInfo.rbegin();
	auto mid = vOutsideAvgInfo.size() / 2;


	for (unsigned short i{ 0 }; it->getDate() != search && rit->getDate() != search && i != (1 + mid); i++, it++, rit++)
		if (it->getDate() == search || rit->getDate() == search)
		{
			auto end = CSTART;
			auto dur = CDURATION(end - start);
			LOG("<Linear> Found time taken: " << dur << " microseconds");
			return (it->getDate() == search) ? "it " + it->avgToString() : "rit " + rit->avgToString();
		}

	auto end = CSTART;
	auto dur = CDURATION(end - start);

	return "<Linear>: " + std::to_string(dur) + " microseconds, " + " to not find " + search;

}

// Hash(Map) search
std::string FileIO::searchMapInside(const std::string & searchWord)
{
	auto start = CSTART;
	auto itr = mapInsideAvgData.find(searchWord);
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG("Hash " << dur << " microsec");
	return itr->second.avgToString();
}

std::string FileIO::searchMapOutside(const std::string & searchWord)
{
	auto start = CSTART;
	auto itr = myMapOutside.find(searchWord);
	auto end = CSTART;
	auto dur = CDURATION(end - start);
	LOG("Hash " << dur << " microsec");
	return itr->second.avgToString();
}
