#include "pch.h"
#include "Program.h"





int main()
{
	

	Program p;
	p.run();
	/*double temp{}, humid{};
	while (std::cin >> temp >> humid)
	{

		auto moldRH = -0.0015*pow(temp, 3) +
			0.1193*pow(temp, 2) - 2.9878*temp + 102.96;
		LOG(moldRH <<"----"<< humid - moldRH);
	}*/


	/*double c{};
	double T1{ 22 };
	double T2{ 20 };
	double RFlim{};
	double RF1lim{};
	double RF{ 80 };


	while (std::cin >> T2)
	{

		RFlim = (-0.0015*pow(T2, 3)) + (0.1193*pow(T2, 2)) - 2.9878*T2 + 102.96;
		LOG(100 - RFlim);
		c = (RF - 105) / (pow(T1, 2) - 54 * T1);
		RF1lim = 105 + c * (pow(T2, 2) - 54 * T2);


		LOG("RF " << RF << " RFlim " << RFlim << " RF1lim " << RF1lim << " c " << c);
	}*/

	

	std::cin.get();
}

