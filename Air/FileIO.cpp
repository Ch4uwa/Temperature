#include "pch.h"
#include "FileIO.h"


FileIO::FileIO(const std::string& filename)
{
	vInfoInside.reserve(vReserveAmount);
	vInfoOutside.reserve(vReserveAmount);
	vInsideAvgInfo.reserve(vReserveAmountSplit);
	vOutsideAvgInfo.reserve(vReserveAmountSplit);
	std::ifstream inFile(filename);
	if (inFile)
	{

		std::string file{};
		while (getline(inFile, file))
		{
			if (file.find("Inne") != std::string::npos)
			{
				//InsideStream << file << "\n";
				AirInfo airinfo(file);
				vInfoInside.emplace_back(airinfo);
				countIn++;
			}
			else
			{
				//OutsideStream << file << "\n";
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
			<< vOutsideAvgInfo.size() << " Days from outside sensor\n";
	}
	else
	{
		std::cerr << "ERROR reading file: " << filename << "\n";
	}
}

FileIO::~FileIO()
{
}

void FileIO::printVall()const
{
	for (const auto& ele : vInfoInside)
	{
		std::cout << ele.toString();
		std::cin.get();
	}
}

void FileIO::printVavg() const
{
	int count{};
	for (const auto& ele : vInsideAvgInfo)
	{

		std::cout << ele.avgToString();
	}
	LOG(count++);
}

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

			//myMap.insert(std::make_pair(hash(d), AirInfo(d, p, t, h)));

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
	//myMap.insert(std::make_pair(hash(d), AirInfo(d, p, t, h)));
}

void FileIO::printWarning()const
{
	for (const auto& ele : vInfoInside)
	{
		if (ele.getMoldWarning())
		{
			std::cout << ele.toString();
			std::cin.get();
		}
	}
}

int FileIO::hash(const std::string& date)
{
	int hash{};
	for (size_t i = 0; i < date.length(); i++)
	{
		hash += date[i] * (1 + i);
	}
	return (hash % 199);
}

void FileIO::mapFind(const std::string& a)
{
	std::cout << myMap.find(hash(a))->second.avgToString();
}

void FileIO::printsort()
{
	auto itr = vInsideAvgInfo.begin();
	
		
	for (const auto&n : vInsideAvgInfo)
	{
		std::cout << n.getAvgHumid() << "\n";
	}
}

//std::string FileIO::search(const std::string& searchWord)
//{
//	return myMap[hash(searchWord)].avgToString();
//}