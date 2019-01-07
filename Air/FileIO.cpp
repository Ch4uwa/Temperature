#include "pch.h"
#include "FileIO.h"

// Constructor
FileIO::FileIO(const std::string& filename)
{
	vInfoInside.reserve(vReserveAmount);
	vInfoOutside.reserve(vReserveAmount);
	vInsideAvgInfo.reserve(vReserveAmountSplit);
	vOutsideAvgInfo.reserve(vReserveAmountSplit);
	myMap.reserve(401);
	std::ifstream inFile(filename);
	if (inFile)
	{
		std::string file{};
		while (getline(inFile, file))
		{
			if (file.find("Inne") != std::string::npos)
			{
				AirInfo airinfo(file);
				vInfoInside.emplace_back(airinfo);
				countIn++;
			}
			else
			{
				AirInfo airinfo(file);
				vInfoOutside.emplace_back(airinfo);
				countOut++;
			}
		}
		inFile.close();
		std::cout << "Done Reading " << countIn + countOut << " Rows, From " << filename << "\n";
		std::cout << "Running avgVals.\n";
		avgVals(vInfoInside, vInsideAvgInfo);
		std::cout << "Done making average values.\n"
			<< vInsideAvgInfo.size() << " Days from inside sensor\n";
		avgVals(vInfoOutside, vOutsideAvgInfo);
		std::cout << "Done making average values.\n"
			<< vOutsideAvgInfo.size() << " Days from outside sensor\n" << myMap.size();
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
void FileIO::avgVals(std::vector<AirInfo>& fromVec, std::vector<AirInfo>& toVec)
{
	std::string d{};
	std::string p{};
	int count{};
	double h{};
	double t{};
	auto itr = fromVec.begin();
	auto next = itr + 1;

	for (; itr != fromVec.end(); ++itr)
	{
		if (itr->getDate() != next->getDate())
		{
			d = next->getDate();
			p = next->getPlace();
			h = h / count;
			t = t / count;
			AirInfo airinfo(d, p, t, h);
			toVec.emplace_back(airinfo);
			myMap.insert(std::make_pair(d, AirInfo(d, p, t, h)));
			next = itr;
			count = 0;
			h = 0;
			t = 0;
		}
		if (itr->getDate() == next->getDate())
		{
			count++;
			h += itr->getHumidity();
			t += itr->getTemp();
		}
	}
	d = next->getDate();
	p = next->getPlace();
	h = h / count;
	t = t / count;
	AirInfo airinfo(d, p, t, h);
	toVec.emplace_back(airinfo);
	myMap.insert(std::make_pair(d, AirInfo(d, p, t, h)));
}

//Sort
// TODO Sort by temp diff inside outside
// TODO sort by door open time
/*
	inside temp - outside temp > inside temp outside temp
*/

void FileIO::sortTempDiff()
{
	auto it = vInsideAvgInfo.begin();
	auto oit = vOutsideAvgInfo.begin();
	auto itend = vInsideAvgInfo.end();
	auto oitend = vOutsideAvgInfo.end();

	for (; it != itend; it++, oit++)
	{
		it->setDiff((it->getAvgTemp() - oit->getAvgTemp()));
		oit->setDiff((it->getAvgTemp() - oit->getAvgTemp()));
		LOG("\n" << it->getDate() << " " << oit->getDate());
		LOG("\nTEMP: " << it->getAvgTemp() << " " << oit->getAvgTemp()
			<< "\nTEMPDIFF: " << it->getTempDiff() << " " << oit->getTempDiff());
	}
}




void FileIO::sortInside(int sortBy)
{
	auto it = vInsideAvgInfo.begin();
	auto itend = vInsideAvgInfo.end();

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

	}
}



// Search TODO choose inside or outside, Move print to function
void FileIO::searchMap(const std::string & searchWord)
{
	auto itr = myMap.equal_range(searchWord);
	for (auto it = itr.first; it != itr.second; it++)
		LOG(it->first << "\n" << it->second.avgToString());
}


// Print function
void FileIO::printMap() // Prints everything inside the map
{
	for (const auto& n : myMap)
	{
		auto itr = myMap.equal_range(n.second.getDate());
		for (auto it = itr.first; it != itr.second; it++)
		{
		}
		std::cout << n.second.avgToString();
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
	else
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
	}
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
