#ifndef FILEIO_H
#define FILEIO_H
#include "AirInfo.h"


class FileIO
{
private:
	const int vReserveAmountSplit{ 199 };

	enum eSortBy
	{
		eTEMP = 1, eHUMID, eMOLD, eTEMPDIFF, eDATE
	};

	// containers
	std::vector<AirInfo> vInsideAvgInfo;
	std::vector<AirInfo> vOutsideAvgInfo;

	std::unordered_map<std::string, AirInfo> mapInsideAvgData;
	std::unordered_map<std::string, AirInfo> mapOutsideAvgData;

	std::unordered_multimap<std::string, AirInfo> myMapInside;
	std::unordered_multimap<std::string, AirInfo> myMapOutside;
	
	std::string s_metroWinter{};
	std::string s_metroAutumn{};

	std::string metroWinter()const;
	std::string metroAutumn()const;
public:
	FileIO(const std::string&);
	~FileIO();


	inline std::string getMetroWinter()const { return this->s_metroWinter; }
	inline std::string getMetroAutumn()const { return this->s_metroAutumn; }

	template<typename T1,typename T2>
	void avgVals(T1& Map, T2& toVec);

	
	void copyToMap();

	void tempDiff();

	// Sort
	void sortInside(int sortBy);
	void sortOutside(int sortBy);

	// Search
	std::string binarySearchInside(const std::string& search);
	std::string binarySearchOutside(const std::string& search);
	std::string linearSearchInside(const std::string& search);
	std::string linearSearchOutside(const std::string& search);
	void searchMapInside(const std::string& searchWord);
	void searchMapOutside(const std::string & searchWord);

	// Print Method
	void print5(const std::vector<AirInfo>& vec);
	void print5Rev(const std::vector<AirInfo>& vec);

};

#endif // FILEIO
