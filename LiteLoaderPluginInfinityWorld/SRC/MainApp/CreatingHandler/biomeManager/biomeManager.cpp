#include "biomeManager.h"



int biomeManager::getBiomeIndex(float x, float y, float z)
{
	auto sampleData = sampleBothMaps(x, y, z);
	static biomePalate* cachedBiome;
	static int index;
	if (cachedBiome != nullptr)
	{
		auto biases = cachedBiome->getBiases();

		if (betweenSections(biases, sampleData))
		{
			return index;
		}
	}

	index = 0;
	bool matched = false;
	while (index < _palates.size() && matched == false)
	{
		auto biases = _palates.at(index)->getBiases();
		if (betweenSections(biases, sampleData))
		{
			auto data = _palates.at(index);
			cachedBiome = data;

			return index;
		}
		index++;
	}
	return 0;
}

bool biomeManager::betweenSections(std::pair<std::pair<float, float>, std::pair<float, float>>& betweenData, std::pair<float, float>& data)
{
	bool leftBetween = false;
	if (data.first > betweenData.first.first && data.first < betweenData.second.first)
	{
		leftBetween = true;
	}
	else
	{
		return false;
	}

	bool rightBetween = false;
	if (data.second > betweenData.first.second && data.second < betweenData.second.second)
	{
		rightBetween = true;
	}
	else
	{
		return false;
	}

	if (rightBetween && leftBetween) { return true; }
	return false;
}

void biomeManager::setupTileData()
{
	for (auto& data : _palates)
	{
		for (auto& stringData : data->getPalate())
		{
			_tileDataVec->push_back(stringData);
		}
	}
}


void biomeManager::addBasics()
{
	std::vector<std::string> grassyCavesBlockTypes = {
		"minecraft:air", // this must ALLWAYS be set to this 
		"minecraft:stone", // This is the underground block most commonly used something like stone, or sandstone work
		"minecraft:stone", // This is what the transition between the floor block and the underground block is
		"minecraft:stone", // This is the floor block
		"minecraft:stone", // This block is used on the top of the caves
		"minecraft:stone" // This is used as a transistion block from top of the caves and underground
	};
	// The blocks to place go first, then the name, then the temp, then the moisture, and how much each is aloud to vary so this can still gen in a -0.2 and a 0.2 climate
	biomePalate* grassyCaves = new biomePalate(grassyCavesBlockTypes, "grassyCaves", 0, 0, 0.6);

	std::vector<std::string> snowyTundraBlockTypes = {
	"minecraft:air",
	"minecraft:stone",
	"minecraft:dirt",
	"minecraft:snow",
	"minecraft:ice",
	"minecraft:packed_ice"
	};

	biomePalate* snowyTundra = new biomePalate(snowyTundraBlockTypes, "snowyTundra", -0.8, 0.6, 0.2);
	
	std::vector<std::string> sandyDesertBlockTypes = {
	"minecraft:air",
	"minecraft:stone",
	"minecraft:sandstone",
	"minecraft:sand",
	"minecraft:sandstone",
	"minecraft:sandstone"
	};

	biomePalate* sandyDesert = new biomePalate(sandyDesertBlockTypes, "sandyDesert", 0.8, -0.8, 0.2);

	std::vector<std::string> marshlandsBlockTypes = {
	"minecraft:air",
	"minecraft:stone",
	"minecraft:dirt",
	"minecraft:grass",
	"minecraft:mud",
	"minecraft:mud"
	};

	biomePalate* marshlands = new biomePalate(marshlandsBlockTypes, "marshlands", -0.4, 0.6, 0.2);

	addPalate(grassyCaves);
	addPalate(snowyTundra);
	addPalate(sandyDesert);
	addPalate(marshlands);

}