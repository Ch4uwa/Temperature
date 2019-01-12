#ifndef FILEIO_H
#define FILEIO_H
#include "AirInfo.h"


class FileIO
{
private:
	const int vReserveAmountSplit{ 200 };
	int countIn{}, countOut{};
	double divider{ 1000000.0 };
	enum eSortBy
	{
		eTEMP = 1, eHUMID, eMOLD, eTEMPDIFF, eDATE
	};

	std::vector<AirInfo> vInsideAvgInfo;
	std::vector<AirInfo> vOutsideAvgInfo;

	//std::unordered_multimap<std::string, AirInfo> myMapAvg;
	std::unordered_multimap<std::string, AirInfo> myMapInside;
	std::unordered_multimap<std::string, AirInfo> myMapOutside;
public:
	FileIO(const std::string&);
	~FileIO();

	void avgVals(std::unordered_multimap<std::string, AirInfo>& myMap, std::vector<AirInfo>& toVec);
	std::string metroWinter()const;
	std::string metroAutumn();
	void tempDiff();


	// Sort
	void sortInside(int sortBy);
	void sortOutside(int sortBy);

	// Search
	std::string binarySearchInside(std::string& search);
	std::string binarySearchOutside(std::string& search);
	std::string linearSearchInside(std::string& search);
	std::string linearSearchOutside(std::string& search);
	void searchMapInside(const std::string& searchWord);
	void searchMapOutside(const std::string & searchWord);

	// Print Method
	void printMap();

};

#endif // FILEIO
