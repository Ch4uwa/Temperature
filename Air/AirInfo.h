#pragma once
class AirInfo
{
private:
	std::string date{};
	std::string time{};
	std::string place{};
	double temperature{};
	int humidity{};
	double avgTemperature{};
	double avgHumidity{};
	const int moldHumid[7]{ 94,90,86,84,82,81,80 };
	const int moldTemp[7]{ 2,4,6,8,10,12,15 };
	int dryInside{ 30 };
public:
	AirInfo(const std::string&);
	//AirInfo():date(""),place(""),avgTemperature(0),avgHumidity(0) {};
	AirInfo(std::string date, std::string place, double avgTemperature, double avgHumidity);

	~AirInfo();
	


	std::string toString()const;
	std::string avgToString()const;

	inline const std::string getDate()const { return this->date; }
	inline const std::string getPlace()const { return this->place; }
	inline const int getHumidity()const { return this->humidity; }
	inline const double getTemp()const { return this->temperature; }
	inline const double getAvgTemp()const { return this->avgTemperature; }
	inline const double getAvgHumid()const { return this->avgHumidity; }
	bool getMoldWarning()const;

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

