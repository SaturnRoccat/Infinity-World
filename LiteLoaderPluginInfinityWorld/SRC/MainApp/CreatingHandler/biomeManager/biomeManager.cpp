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