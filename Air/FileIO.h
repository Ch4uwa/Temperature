#ifndef FILEIO_H
#define FILEIO_H
#include "pch.h"
#include "AirInfo.h"


class FileIO
{
private:
	const int vReserveAmount{ 350000 };
	const int vReserveAmountSplit{ 200 };
	int countIn{}, countOut{};
	std::vector<AirInfo> vInfoInside;
	std::vector<AirInfo> vInfoOutside;
	std::vector<AirInfo> vInsideAvgInfo;
	std::vector<AirInfo> vOutsideAvgInfo;

	std::multimap<int, AirInfo> myMap;

	std::stringstream InsideStream, OutsideStream;
public:
	FileIO(const std::string&);
	~FileIO();
	
	void printVall()const;
	void printVavg()const;
	void avgVals(std::vector<AirInfo>& fromVec, std::vector<AirInfo>& toVec);
	void printWarning() const;
	int hash(const std::string& date);

	// TODO Search map?
	
	void mapFind(const std::string & a);
	//std::string search(const std::string& searchWord);


	

	// TODO Sort std::stable_sort / mergesort
	void printsort();




};

#endif // FILEIO

