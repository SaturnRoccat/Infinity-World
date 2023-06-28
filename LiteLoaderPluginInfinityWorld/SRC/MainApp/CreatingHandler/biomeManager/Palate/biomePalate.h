#pragma once
#include <unordered_map>
#include <string>


/*
* 0 = underground block
* 1 = surface block
* 2 = transition
*/



/**
 * The `biomePalate` class represents the palate for a biome. It stores the information related to the blocks, names, and biases associated with the biome.
 */
class biomePalate
{
public:
	/**
	 * Constructor for the `biomePalate` class.
	 *
	 * @param palateMergeData An vector that stores string values, representing the blocks of the biome.
	 * @param biomeName The name of the biome.
	 * @param tempBias The temperature bias associated with the biome.
	 * @param moistureBias The moisture bias associated with the biome.
	 */
	biomePalate(std::vector<std::string>& palateMergeData, std::string biomeName, float tempBias, float moistureBias, float maxBias = 0.2f)
	{
		// Copy the elements from palateMergeData into _palate
		for (auto data : palateMergeData)
		{
			_palate.push_back(data);
		}

		// Set the biome name
		_biomeName = biomeName;

		// Set the temperature bias and moisture bias
		_tmpBias = tempBias;
		_moistureBias = moistureBias;
		_maxBias = maxBias;
	};


	std::vector<std::string>& getPalate() { return _palate; };


	/**
	 * Get the name of the biome.
	 *
	 * @return The name of the biome.
	 */
	__forceinline std::string& getName() { return _biomeName; };

	/**
	 * Get the biases associated with the biome.
	 *
	 * @return A pair of pairs representing the temperature bias and moisture bias min and max.
	 */
	__forceinline std::pair<std::pair<float, float>, std::pair<float, float>> getBiases() { 
		return {
			{_tmpBias - _maxBias, _moistureBias - _maxBias},
			{_tmpBias + _maxBias, _moistureBias + _maxBias}
		};
	}
public:

private:
	float _tmpBias; // Temperature bias
	float _maxBias; // max bias
	float _moistureBias; // Moisture bias

	std::vector<std::string> _palate; // Palate data 
	std::string _biomeName; // Name of the biome
};
