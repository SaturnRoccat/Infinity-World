#include "NoiseHandler.h"
#include "..\..\Util\math.hpp"

std::pair<int2, int3> NoiseHandler::getIndexDown(int x, int y, int z)
{
    int2 internalMapPos = { _chunksToContain.x * _chunkSize.x, _chunksToContain.y * _chunkSize.z };
    int3 sampleCoords = {
        x % (_chunksToContain.x * _chunkSize.x),
        y,
        z % (_chunksToContain.y * _chunkSize.z)
    };
    return { internalMapPos, sampleCoords };
}