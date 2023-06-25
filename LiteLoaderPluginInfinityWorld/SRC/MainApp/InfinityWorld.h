#pragma once

// Liteloader And BDS API stuff

#include <llapi/LoggerAPI.h>
#include <llapi/EventAPI.h>

// Custom Headers

#include "..\version.h"
#include "fastNoiselite.hpp"
#include "CreatingHandler\Chunk.h"
#include "BS_thread_pool.hpp"
#include "CreatingHandler\Noisehandler\NoiseHandler.h"
#include "CreatingHandler\Noisehandler\NoiseSegment\NoiseSegment.h"

// STD

#include <string>
#include <memory>
#include <unordered_map>

extern Logger logger;
class InfinityWorld
{
public:
	// Constructor used to instantiate the SimplexNoise
	InfinityWorld();

	// Called to initialize stuff
	void Init();

	// Continues the execution
	void cont();

public:
	int perpassDelay = 1 * 1;

private:

	void produceNoiseData();

	void finalizeData();

	void memoryCleanup();
private:
	std::unordered_map<std::size_t, bool> _loadedBeforeMap; // Stores information about loaded items

	std::unordered_map<uint8_t, std::string> _masterTiledata;

	BS::thread_pool* pool; // Represents a thread pool for concurrent execution
	bool _hasStartedGen = false; // Indicates if the generation has started
	FastNoiseLite* _sn; // Instance of the SimplexNoise generator

	// The master variable that is used to control the stage of the generation: This also only tracks internal ticks this is not in anyway meant to sync with the game
	int _tickIndex = 0;

	std::vector<Chunk*> chunkArray; // Moved outside the player loop
};
