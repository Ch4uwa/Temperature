#pragma once
class AirInfo
{
private:
	std::string date{};
	std::string time{};
	std::string place{};
	double temperature{};
	int humidity{};
public:
	AirInfo(const std::string&);
	~AirInfo();

	std::string toString()const;

};

