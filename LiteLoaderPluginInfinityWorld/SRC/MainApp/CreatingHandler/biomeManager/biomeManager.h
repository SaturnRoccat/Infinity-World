#pragma once



#include "Palate\biomePalate.h"
#include <map>
#include <string>
#include "fastNoiselite.hpp"


#define XandZDialation 3 // This is here so i can add a config system easier




/*
* 0 = Air
* 1 = Solid
* 2 = Transition
* 3 = surface Top
* 4 = surface Other // stuff like the walls and ceiling 
*/

class biomeManager
{
public:
	biomeManager(std::vector<std::string>* tileDataVec, int seed = 1337)
	{
		_tileDataVec = tileDataVec;
		_moistureMap = FastNoiseLite(seed + 1);
		_tempMap = FastNoiseLite(seed + 2);
		_moistureMap.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
		_tempMap.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);



		addBasics();
	};

	__forceinline void addPalate(biomePalate* pal) { _palates.emplace_back(pal); };

	int getBiomeIndex(float x, float y, float z);
	__forceinline int getBiomeIndex(int x, int y, int z) {
		return getBiomeIndex(float(x), float(y), float(z));
	};

	__forceinline float getData(float x, float y, float z, float bias = 0.1) { return _moistureMap.GetNoise(x / XandZDialation, y, z / XandZDialation) + bias; }

	__forceinline std::pair<float, float> sampleBothMaps(float x, float y, float z, float bias = 0.1) {
		return {
		_moistureMap.GetNoise(x / XandZDialation, y, z / XandZDialation) + bias, _tempMap.GetNoise(x / XandZDialation, y, z / XandZDialation) };
	}

	void setupTileData();

public:



	 

private:
	void addBasics();
	bool betweenSections(std::pair<std::pair<float, float>, std::pair<float, float>>& betweenData, std::pair<float, float>& data);

private:


	std::vector<std::string>* _tileDataVec;
	std::vector<biomePalate*> _palates;
	FastNoiseLite _moistureMap;
	FastNoiseLite _tempMap;
};