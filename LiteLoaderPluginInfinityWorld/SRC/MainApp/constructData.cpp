#include "InfinityWorld.h"
#include <llapi\EventAPI.h>
#include <llapi\mc\Level.hpp>
#include <llapi\mc\Block.hpp>
#include "BS_thread_pool.hpp"


//
#include <llapi/EventAPI.h>
#include <llapi/ScheduleAPI.h>
#include <mutex>
#include <memory>

#include <llapi/mc/Objective.hpp>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/Scoreboard.hpp>
#include <llapi/mc/Types.hpp>
#include <math.h>
#include "Util\Timer.h"

std::mutex mapHashes;
void InfinityWorld::produceNoiseData()
{

    chunkArray.clear();
    chunkArray.resize(0);
    auto PlayerList = Level::getAllPlayers();
    for (auto& p : PlayerList)
    {
        chunkPosition pcp;
        pcp.x = floor(p->getPos().x / 16); // Calculate player's chunk position (x-axis)
        pcp.z = floor(p->getPos().z / 16); // Calculate player's chunk position (z-axis)

        static const int numChunks = 7; // Number of chunks to load around the player
        for (int x = pcp.x - numChunks; x <= pcp.x + numChunks; x++) {
            for (int z = pcp.z - numChunks; z <= pcp.z + numChunks; z++) {
                chunkPosition CurrentChunkPos = { pcp.x + x, pcp.z + z }; // Calculate the position of the current chunk
                uint64_t chunkHash = CurrentChunkPos.hash(); // Generate a hash for the chunk position
                auto it = _loadedBeforeMap.find(chunkHash); // Check if the chunk has been loaded before

                if (it == _loadedBeforeMap.end()) // Chunk not found in loaded chunks
                {
                        
                    Chunk* currentChunk = new Chunk(CurrentChunkPos, _sn, &_tileDataVectorNew, bm, 16, 192, 16); // Create a new chunk
                    currentChunk->createChunkData(); // Generate chunk data
                    chunkArray.push_back(currentChunk); // Add the chunk to the array
                       _loadedBeforeMap.insert({ chunkHash, true }); // Mark the chunk as loaded

                }
            }
        }
    }
    // pool->wait_for_tasks();

}