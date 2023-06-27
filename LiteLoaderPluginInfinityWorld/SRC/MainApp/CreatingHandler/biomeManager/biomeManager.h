#pragma once



#include "Palate\biomePalate.h"
#include <map>
#include <string>
#include "fastNoiselite.hpp"


//
//typedef struct comparsionData
//{
//	std::pair<float, float> minMaxTemp;
//	std::pair<float, float> minMaxmoisture;
//};



class biomeManager
{
public:
	biomeManager(int seed = 1337) 
	{
		_moistureMap = FastNoiseLite(seed + 1);
		_tempMap = FastNoiseLite(seed + 2);
	};

	int getBiomeIndex(float x, float y, float z);
	__forceinline int getBiomeIndex(int x, int y, int z) {
		return getBiomeIndex(float(x), float(y), float(z));
	};
	__forceinline float getData(float x, float y, float z) { return _moistureMap.GetNoise(x / 3, y, z / 3) + 0.3; }
public:



	 

private:


private:



	std::map<std::string, biomePalate> _palates;
	FastNoiseLite _moistureMap;
	FastNoiseLite _tempMap;
};