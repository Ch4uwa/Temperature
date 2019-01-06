#include "pch.h"
#include "AirInfo.h"


AirInfo::AirInfo(const std::string& file)
{
	std::string holder{};
	std::stringstream ss(file);
	getline(ss, this->date, ' ');
	getline(ss, this->time, ',');
	getline(ss, this->place, ',');
	getline(ss, holder, ',');
	this->temperature = stod(holder);
	getline(ss, holder);
	this->humidity = stoi(holder);
	MoldLevel();
}

AirInfo::AirInfo(std::string date, std::string place, double avgTemperature, double avgHumidity)
	:date(date), place(place), avgTemperature(avgTemperature), avgHumidity(avgHumidity)
{
	AvgMoldLevel();
}

AirInfo::~AirInfo()
{
}

std::string AirInfo::toString()const
{
	std::stringstream info;
	if (getMoldWarning())
	{
		info << "==============================\n"
			<< "Warning! Mold risk "
			<< std::fixed << std::setprecision(1)
			<< this->riskLevel << "\n";
	}
	info << "=============================="
		<< "\nPlacement: " << this->place
		<< "\nDate: " << this->date
		<< "\nTime: " << this->time
		<< "\nTemperature: " << this->temperature << " Celsius"
		<< "\nHumidity: " << this->humidity << " %\n"
		<< "==============================\n";
	return info.str();
}

std::string AirInfo::avgToString() const
{
	std::stringstream info;
	if (getMoldWarning())
	{
		info << "==============================\n"
			<< "Warning! Mold risk "
			<< std::fixed << std::setprecision(1)
			<< this->riskLevel << "\n";
	}
	info << "\n=============================="
		<< "\nPlacement: " << this->place
		<< "\nDate: " << this->date
		<< "\nAverage Temperature: " << std::fixed << std::setprecision(1) << this->avgTemperature << " Celsius"
		<< "\nAverage Humidity: " << std::fixed << std::setprecision(1) << this->avgHumidity << " %\n"
		<< "==============================\n";

	return info.str();
}

/* MOLD Methods */
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
	this->riskLevel = (this->humidity - moldRH);
}
void AirInfo::AvgMoldLevel()
{
	auto moldRH = -0.0015*pow(this->avgTemperature, 3) +
		0.1193*pow(this->avgTemperature, 2) - 2.9878*this->avgTemperature + 102.96;
	this->riskLevel = (this->avgHumidity - moldRH);
}


