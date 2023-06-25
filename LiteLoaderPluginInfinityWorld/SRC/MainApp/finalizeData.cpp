#include "InfinityWorld.h"
#include "Util\Timer.h"
#include <llapi/LoggerAPI.h>

void InfinityWorld::finalizeData()
{

    const static int maxPlacementTime = 40;

    long long currentTime = 0;
    auto arraySize = chunkArray.size();
    int calculationPosition = 0;
    Timer* calculationTimer = new Timer();
    while (currentTime < maxPlacementTime && calculationPosition < arraySize)
    {
        calculationTimer->getTime();
        auto& chunk = chunkArray.back();
        if (chunk != nullptr)
        {
            chunk->placeChunkData();
            delete chunk;
            chunkArray.pop_back();
        }
        currentTime += calculationTimer->getTime();
        calculationPosition++;
    }
    if (chunkArray.size() == 0)
    {
        dataPlaced = true;
    }
    else
    {
        dataPlaced = false;
    }

}