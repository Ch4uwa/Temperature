#ifndef AIRINFO_H
#define AIRINFO_H
#include "pch.h"


class AirInfo
{
private:
	std::string date{};
	int month{};
	int day{};
	std::string place{};
	std::string time{};
	double temperature{};
	int humidity{};
	int hour{};
	int minute{};
	int seconds{};

	double avgTemperature{};
	double avgHumidity{};
	
	

	double diff{};

	int dryInside{ 30 };
	int riskLevel{};
	inline void setMonth()
	{
		std::string holder;
		std::stringstream ss(date);
		getline(ss, holder, '-');
		getline(ss, holder, '-');
		this->month = stoi(holder);
		getline(ss, holder);
		this->day = stoi(holder);
	}
	void MoldLevel();
	void AvgMoldLevel();
public:
	AirInfo(const std::string& date, const std::string& place,const int& hour,
		const int& minute, const int& seconds,
		const double& temperature, const int& humidity);
	AirInfo() :date(""), place(""), avgTemperature(0), avgHumidity(0) {}
	AirInfo(std::string date, std::string place, double avgTemperature, double avgHumidity);

	~AirInfo();


	// Methods
	std::string toString()const;
	std::string avgToString()const;

	bool getMoldWarning()const;

	inline void setDiff(const double& diff) { this->diff = diff; };
	inline void setAvgHumid(const double& avgHumid) { this->avgHumidity = avgHumid; };
	inline void setAvgTemp(const double& avgTemp) { this->avgTemperature = avgTemp; };

	// Accessor
	inline const std::string getDate()const { return this->date; }
	inline const std::string getPlace()const { return this->place; }
	inline const int getHumidity()const { return this->humidity; }
	inline const double getTemp()const { return this->temperature; }
	inline const double getAvgTemp()const { return this->avgTemperature; }
	inline const double getAvgHumid()const { return this->avgHumidity; }
	inline const double getTempDiff()const { return this->diff; }
	inline const int getRiskLevel()const { return this->riskLevel; }
	inline const int getHour()const { return this->hour; }
	inline const int getMinute()const { return this->minute; }
	inline const int getSeconds()const { return this->seconds; }
	inline const int getMonth()const { return this->month; }
	inline const int getDay()const { return this->day; }

};

#endif // !AIRINFO_H
