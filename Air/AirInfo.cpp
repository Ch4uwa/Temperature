#include "pch.h"
#include "AirInfo.h"


AirInfo::AirInfo(const std::string& file)
{
	std::string holder;
	std::stringstream ss(file);
	getline(ss, this->date, ' ');
	getline(ss, this->time, ',');
	getline(ss, this->place, ',');
	getline(ss, holder, ',');
	this->temperature = stod(holder);
	getline(ss, holder);
	this->humidity = stoi(holder);
}

AirInfo::~AirInfo()
{
}

std::string AirInfo::toString()const
{
	std::stringstream info;
	info << "Date: " << this->date << " Time: " << this->time << " Placement: " << this->place
		<< " Temperature: " << this->temperature << " Humidity: " << this->humidity << "\n";
	return info.str();
}
