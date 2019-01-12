#include "pch.h"
#include "AirInfo.h"


AirInfo::AirInfo(const std::string& date, const std::string& place, const int& hour,
	const int& minute, const int& seconds,
	const double& temperature, const int& humidity)
	:date(date), place(place), hour(hour), minute(minute),
	seconds(seconds), temperature(temperature), humidity(humidity)
{
	MoldLevel();
	setMonth();
}

AirInfo::AirInfo(std::string date, std::string place, double avgTemperature, double avgHumidity)
	:date(date), place(place), avgTemperature(avgTemperature), avgHumidity(avgHumidity)
{
	AvgMoldLevel();
	setMonth();
}

AirInfo::~AirInfo()
{
}

std::string AirInfo::toString()const
{
	std::stringstream infoFull;
	if (getMoldWarning())
	{
		infoFull << "> ==============================\n"
			<< "> Warning!" << (this->riskLevel < 10) ? " Mold index above limit <" : " HIGH RISK FOR MOLD! <";
		infoFull << std::fixed << std::setprecision(1)
			<< this->riskLevel << ">\n";
	}
	infoFull << "> =============================="
		<< "\n> Placement: " << this->place
		<< "\n> Date: " << this->date
		<< "\n> Time: " << this->hour << ":" << this->minute << ":" << this->seconds
		<< "\n> Temperature: " << this->temperature << " Celsius"
		<< "\n> Humidity: " << this->humidity << " %"
		<< "\n> ==============================\n";
	return infoFull.str();
}

std::string AirInfo::avgToString() const
{
	std::stringstream infoAvg;
	if (getMoldWarning())
	{
		infoAvg << "> ==============================\n"
			<< "> Warning!" << (this->riskLevel < 10) ? " Mold index above limit <" : " HIGH RISK FOR MOLD! <";
		infoAvg << std::fixed << std::setprecision(1)
			<< this->riskLevel << ">\n";
	}
	infoAvg << "> =============================="
		<< "\n> Placement: " << this->place
		<< "\n> Date: " << this->date
		<< "\n> Average Temperature: " << std::fixed << std::setprecision(1) << this->avgTemperature << " Celsius"
		<< "\n> Average Humidity: " << std::fixed << std::setprecision(1) << this->avgHumidity << " %"
		<< "\n> Diff " << diff
		<< "\n> MoldLimit " << riskLevel
		<< "\n> ==============================\n";
	return infoAvg.str();
}

/* MOLD Method */
bool AirInfo::getMoldWarning()const
{
	if (riskLevel > 0)
	{
		return true;
	}
	return false;
}

void AirInfo::MoldLevel()
{
	auto moldRH = -0.0015*pow(this->temperature, 3) +
		0.1193*pow(this->temperature, 2) - 2.9878*this->temperature + 102.96;
	this->riskLevel = static_cast<int>(this->humidity - moldRH);
}
void AirInfo::AvgMoldLevel()
{
	auto moldRH = -0.0015*pow(this->avgTemperature, 3) +
		0.1193*pow(this->avgTemperature, 2) - 2.9878*this->avgTemperature + 102.96;

	this->riskLevel = static_cast<int>(this->avgHumidity - moldRH);
}


