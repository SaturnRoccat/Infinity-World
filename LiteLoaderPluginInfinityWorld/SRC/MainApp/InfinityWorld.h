#pragma once

// Liteloader And BDS API stuff

#include <llapi/LoggerAPI.h>
#include <llapi/EventAPI.h>

// Custom Headers

#include "..\version.h"
#include "fastNoiselite.hpp"
#include "CreatingHandler\Chunk.h"
#include "BS_thread_pool.hpp"

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

	// Used as a cheat because using Event::ServerStartedEvent kept getting SEH
	void HandleGen();

	// Continues the execution
	void cont();

private:
	std::unordered_map<uint64_t, bool> _loadedBeforeMap; // Stores information about loaded items
	BS::thread_pool* pool; // Represents a thread pool for concurrent execution
	bool _hasStartedGen = false; // Indicates if the generation has started
	FastNoiseLite* _sn; // Instance of the SimplexNoise generator

	// The master variable that is used to control the stage of the generation
	int _tickIndex = 0;
};
