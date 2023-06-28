#include "InfinityWorld.h"
#include "Util\Timer.h"
// This pass will be VERY calculation heavy so it will break up over multiple ticks. I might use a flood fill algorithm to get all air
// Or i might just walk the whole array and do that. I suppose i could just do a check when the block is palced but that adds more load to a allready
// Heavy pass so i think for now i will stick with calling it this way :) 


void InfinityWorld::recalculateBlocks()
{
	Timer localTimer = Timer();
	{
		static Timer* time = new Timer();

		const int maxTime = 35;
		int overallTime = 0;
		static int index;
		if (calculatingBlocks == false)
		{
			index = 0;
		}

		while (overallTime < maxTime && index < chunkArray.size())
		{
			time->getTime();

			auto& chunk = chunkArray[index];
			index++;
			chunk->recalculateChunkData();

			overallTime += time->getTime();
			calculatingBlocks = true;
		}

		if (index >= chunkArray.size())
		{
			calculatedBlocks = true;
		}
		else
		{
			calculatedBlocks = false;
		}
	}
	// debuggin only 
	// logger.warn("Time Taken To recalculateBlocks {}", localTimer.getTime());
}