#ifndef FILEIO_H
#define FILEIO_H
#include "pch.h"
#include "AirInfo.h"


class FileIO
{
private:
	const int vReserveAmountSplit{ 200 };
	int countIn{}, countOut{};
	//std::vector<AirInfo> vInfoInside;
	//std::vector<AirInfo> vInfoOutside;
	std::vector<AirInfo> vInsideAvgInfo;
	std::vector<AirInfo> vOutsideAvgInfo;

	//std::unordered_multimap<std::string, AirInfo> myMapAvg;
	std::unordered_multimap<std::string, AirInfo> myMapInside;
	std::unordered_multimap<std::string, AirInfo> myMapOutside;
public:
	FileIO(const std::string&);
	~FileIO();

	/*
		is door open
			temp inside, temp outside diff

	*/

	void avgVals(std::unordered_multimap<std::string, AirInfo>& myMap, std::vector<AirInfo>& toVec);
	std::string getMetro(bool Autumn)const;

	// Sort Method TODO Sort by biggest temp diff
	void sortInside(int sortBy);
	void sortOutside(int sortBy);

	void tempDiff();
	// Search
	
	void searchMap(const std::string& searchWord);

	// Print Method
	void printV(bool average, bool in, bool warnings);
	void printMap();





	//int hash(const std::string& date);



};

#endif // FILEIO

