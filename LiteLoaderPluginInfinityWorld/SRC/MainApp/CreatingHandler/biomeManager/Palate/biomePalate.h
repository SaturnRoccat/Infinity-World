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
	 * @param palateMergeData An unordered map that maps `uint8_t` keys to string values, representing the blocks and names of the biome.
	 * @param biomeName The name of the biome.
	 * @param tempBias The temperature bias associated with the biome.
	 * @param moistureBias The moisture bias associated with the biome.
	 */
	biomePalate(std::unordered_map<uint8_t, std::string>& palateMergeData, std::string biomeName, float tempBias, float moistureBias)
	{
		// Copy the elements from palateMergeData into _palate
		for (auto data : palateMergeData)
		{
			_palate.insert(data);
		}

		// Set the biome name
		_biomeName = biomeName;

		// Set the temperature bias and moisture bias
		_tmpBias = tempBias;
		_moistureBias = moistureBias;
	};

public:
	/**
	 * Sample a block from the palate based on the local index.
	 *
	 * @param localIndex The index used to select a block from the palate.
	 * @return The block string sampled from the palate.
	 */
	__forceinline std::string sample(uint8_t localIndex = 0u)
	{
		return _palate.at(localIndex);
	}

	/**
	 * Get the name of the biome.
	 *
	 * @return The name of the biome.
	 */
	__forceinline std::string& getName() { return _biomeName; };

	/**
	 * Get the biases associated with the biome.
	 *
	 * @return A pair of floats representing the temperature bias and moisture bias.
	 */
	__forceinline std::pair<std::pair<float, float>, float> getBiases() { return { {_tmpBias ,_moistureBias}, 0.2f }; }

private:
	float _tmpBias; // Temperature bias
	float _moistureBias; // Moisture bias

	std::unordered_map<uint8_t, std::string> _palate; // Palate data (mapping from uint8_t to string)
	std::string _biomeName; // Name of the biome
};
