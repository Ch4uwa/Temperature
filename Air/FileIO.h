#ifndef FILEIO_H
#define FILEIO_H
#include "pch.h"
#include "AirInfo.h"

class FileIO
{
private:
	std::vector<AirInfo> vInfo;
public:
	FileIO(const std::string&);
	~FileIO();

	void printVall()const;
	
};

#endif // FILEIO