#include "pch.h"
#include "AirInfo.h"


AirInfo::AirInfo(const std::string& date, const std::string& place, const std::string& time, const double& temperature, const int& humidity)
	:date(date), place(place), time(time), temperature(temperature), humidity(humidity)
{
	MoldLevel();
	setMonth();
}

AirInfo::AirInfo(std::string date, std::string place, double avgTemperature, double avgHumidity, double avgRiskLevel)
	:date(date), place(place), avgTemperature(avgTemperature), avgHumidity(avgHumidity), avgRiskLevel(avgRiskLevel)
{
	setMonth();
}

AirInfo::~AirInfo()
{
}

std::string AirInfo::avgToString()const
{
	std::stringstream infoAvg;
	if (getMoldWarning())
	{
		infoAvg << "\n> ==============================\n"
			<< "> Warning! Mold index above limit <"
			<< std::fixed << std::setprecision(1)
			<< this->avgRiskLevel << ">\n";
	}
	infoAvg << "> =============================="
		<< "\n> Placement: " << this->place
		<< "\n> Date: " << this->date
		<< "\n> Average Temperature: " << std::fixed << std::setprecision(1) << this->avgTemperature << " Celsius"
		<< "\n> Average Humidity: " << std::fixed << std::setprecision(1) << this->avgHumidity << " %"
		<< "\n> Mold index: " << std::fixed << std::setprecision(1) << this->avgRiskLevel
		<< "\n> ==============================\n";
	return infoAvg.str();
}

/* MOLD Method */

void AirInfo::MoldLevel()
{
	auto moldRH = -0.0015*pow(this->temperature, 3) +
		0.1193*pow(this->temperature, 2) - 2.9878*this->temperature + 102.96;
	this->riskLevel = static_cast<int>(this->humidity - moldRH);
}



