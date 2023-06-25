#pragma once
#include "fastNoiselite.hpp"
#include "NoiseSegment\NoiseSegment.h"
#include <unordered_map>
class NoiseHandler
{
public:
	NoiseHandler(FastNoiseLite* FSN)
		: _fsn(FSN) {};
public:

	uint16_t pollData(int x, int y, int z);
	__forceinline uint16_t pollData(int3 pos) { return pollData(pos.x, pos.y, pos.z); }

	std::pair<int2, int3> getIndexDown(int x, int y, int z);
private:
	__forceinline std::pair<int2, int3> getIndexDown(int3 pos) { return getIndexDown(pos.x, pos.y, pos.z); }
private:

	// These numbers are magic numbers right now because we don't have a configuration loader.
	// Once I make one, these will be changeable. These numbers represent the code optimization.
	int3 _chunkSize = { 16, 128, 16 };
	int2 _chunksToContain = { 64, 64 };

	std::unordered_map<uint32_t, bool> existsInLocalMemory;
	FastNoiseLite* _fsn;
};
