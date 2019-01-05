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
}

AirInfo::AirInfo(std::string date, std::string place, double avgTemperature, double avgHumidity)
	:date(date), place(place), avgTemperature(avgTemperature), avgHumidity(avgHumidity)
{
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
			<< "Warning! Mold risk";
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
			<< "Warning! Mold risk";
	}
	info << "\n=============================="
		<< "\nPlacement: " << this->place
		<< "\nDate: " << this->date
		<< "\nAverage Temperature: " << std::fixed << std::setprecision(1) << this->avgTemperature << " Celsius"
		<< "\nAverage Humidity: " << std::fixed << std::setprecision(1) << this->avgHumidity << " %\n"
		<< "==============================\n";

	return info.str();
}

bool AirInfo::getMoldWarning()const
{
	// TODO Time counting, longer the time higher the risk.
	if (this->temperature >= moldTemp[0] && this->humidity >= moldHumid[6])
	{
		int i{ 6 };
		while (this->temperature <= moldTemp[i])
		{
			if (this->humidity >= moldHumid[i])
			{
				return true;
			}
			i--;
		}
	}
	return false;
}
