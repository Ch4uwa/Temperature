#ifndef AIRINFO_H
#define AIRINFO_H

#include "pch.h"

class AirInfo
{
private:
	std::string date;
	std::string place;
	std::string time{};
	double temperature;
	int humidity;
	int hour;
	int minute;
	int seconds;

	double avgTemperature{};
	double avgHumidity{};

	double diff{};

	int dryInside{ 30 };
	int riskLevel{};

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
	inline double getAvgTemp()const { return this->avgTemperature; }
	inline double getAvgHumid()const { return this->avgHumidity; }
	inline double getTempDiff()const { return this->diff; }
	inline int getRiskLevel()const { return this->riskLevel; }
	inline int getHour() { return this->hour; }
	inline int getMinute() { return this->minute; }
	inline int getSeconds() { return this->seconds; }


	// y=-0,0015x^3+0,1193x^2-2,9878x+102,96
	/*	Temp/RH MoldGrowth risk
		0-40 celsius range
		20-40 celsius if 75% rh risk
		0 celsius risk 100% rh

		22C-35C optimal growth
		71-94% RH 80%RH Critical
		2C 94rh
		4C 90rh
		6C 86rh
		8C 84rh
		10C 82rh
		12C 81rh
		15C-40C 80rh

	*/

};

#endif // !AIRINFO_H
