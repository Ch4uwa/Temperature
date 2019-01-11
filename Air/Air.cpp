#include "pch.h"
#include "Program.h"





int main()
{
	Program p;
	p.run();
	
	//TODO Search avg value.


	/*
		calc shit

	*/


	/*double c{};
	double T1{ 22 };
	double T2{ 20 };
	double RFlim{};
	double RF1lim{};
	double RF{80};


	RFlim = (-0.0015*pow(T2, 3)) + (0.1193*pow(T2, 2)) - 2.9878*T2 + 102.96;
	LOG(95-RFlim);*/
	/*while (std::cin >> T2)
	{

		c = (RF - 105) / (pow(T1, 2) - 54 * T1);
		RF1lim = 105 + c * (pow(T2, 2) - 54 * T2);


		LOG("RF "<<RF << " RFlim " << RFlim << " RF1lim " << RF1lim << " c " << c);
	}*/

	// Binary search
	/*int search{ 4678 };

	int max = vec.size();
	int min{};
	int pos = max / 2;
	do
	{
		if (search < vec[pos])
		{
			max = pos;
			pos = ((max + min) / 2);
		}
		else if (search > vec[pos])
		{
			min = pos;
			pos = ((max + min) / 2);
		}
	} while (search != vec[pos]);
	LOG("Found" << vec[pos] << " at " << pos);
	*/

	std::cin.get();
}

