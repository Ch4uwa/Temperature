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
	int hour{};
	int minute{};
	int seconds{};
	int humidity{};
	double avgHumidity{};
	double temperature{};
	double avgTemperature{};
	double diff{};
	double avgRiskLevel{};
	int riskLevel{};

	inline void setMonth()
	{
		std::string holder;
		std::stringstream ss(date);
		getline(ss, holder, '-');
		getline(ss, holder, '-');
		this->month = stoi(holder);
		ss.clear();
	}

	void MoldLevel();
public:
	AirInfo(const std::string& date, const std::string& place, const std::string& time, const double& temperature, const int& humidity);
	AirInfo() :date(""), place(""), avgTemperature(0.0), avgHumidity(0.0), avgRiskLevel(0.0) {}
	AirInfo(std::string date, std::string place, double avgTemperature, double avgHumidity, double avgRiskLevel);

	~AirInfo();


	// Methods

	std::string avgToString()const;

	// Modifiers
	inline void setDiff(const double& diff) { this->diff = diff; };
	inline void setAvgHumid(const double& avgHumid) { this->avgHumidity = avgHumid; };
	inline void setAvgTemp(const double& avgTemp) { this->avgTemperature = avgTemp; };

	// Accessor
	inline const bool getMoldWarning()const { return (this->riskLevel > 0) ? true : false; };
	inline const std::string& getDate()const { return this->date; }
	inline const std::string& getPlace()const { return this->place; }
	inline const int& getHumidity()const { return this->humidity; }
	inline const double& getTemp()const { return this->temperature; }
	inline const double& getAvgTemp()const { return this->avgTemperature; }
	inline const double& getAvgHumid()const { return this->avgHumidity; }
	inline const double& getTempDiff()const { return this->diff; }
	inline const double& getAvgRiskLevel()const { return this->avgRiskLevel; }
	inline const int& getRiskLevel()const { return this->riskLevel; }
	inline const int& getHour()const { return this->hour; }
	inline const int& getMinute()const { return this->minute; }
	inline const int& getSeconds()const { return this->seconds; }
	inline const int& getMonth()const { return this->month; }
	inline const int& getDay()const { return this->day; }

};

#endif // !AIRINFO_H
