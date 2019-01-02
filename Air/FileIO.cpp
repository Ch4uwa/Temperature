#include "pch.h"
#include "FileIO.h"


FileIO::FileIO(const std::string& filename)
{
	vInfo.reserve(350000);
	std::ifstream inFile(filename);
	if (inFile)
	{
		std::string file{};
		while (getline(inFile, file))
		{
			AirInfo airinfo(file);
			vInfo.emplace_back(airinfo);
		}
		inFile.close();
		std::cout << "Reading done\n";
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
	for (const auto& ele : vInfo)
	{
		std::cout << ele.toString();
		std::cin.get();
	}
}
