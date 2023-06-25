#include "InfinityWorld.h"
#include "Util\Timer.h"
#include <llapi/LoggerAPI.h>

void InfinityWorld::finalizeData()
{

    Timer* T = new Timer();
    T->getTime();
    for (auto& C : chunkArray)
    {
        C->placeChunkData(); // Place chunk data in the world
    }

    if (chunkArray.size() > 0)
    {
        auto chunkSize = chunkArray.size();
        logger.warn("Ammount Of Chunks In Array: {}", chunkSize);
        auto time = T->getTime();
        logger.warn("Chunk time: {}: For an Average of {}ms Per Chunk", time, time / chunkSize);

    }
}