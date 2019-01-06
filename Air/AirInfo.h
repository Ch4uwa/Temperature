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

	int dryInside{ 30 };
	int riskLevel{};

	void MoldLevel();
	void AvgMoldLevel();
public:
	AirInfo(const std::string&);
	AirInfo() :date(""), place(""), avgTemperature(0), avgHumidity(0) {}
	AirInfo(std::string date, std::string place, double avgTemperature, double avgHumidity);

	~AirInfo();


	// Methods
	std::string toString()const;
	std::string avgToString()const;
	
	bool getMoldWarning()const;

	

	// Accessor
	inline const std::string getDate()const { return this->date; }
	inline const std::string getPlace()const { return this->place; }
	inline const int getHumidity()const { return this->humidity; }
	inline const double getTemp()const { return this->temperature; }
	inline double getAvgTemp()const { return this->avgTemperature; }
	inline double getAvgHumid()const { return this->avgHumidity; }
	inline int getRiskLevel()const { return this->riskLevel; }



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

