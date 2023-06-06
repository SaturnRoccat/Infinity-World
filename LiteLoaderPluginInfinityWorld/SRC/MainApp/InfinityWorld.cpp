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


struct int2
{
	int x;
	int y;
};


__forceinline void Pass(InfinityWorld* infinity) { infinity->cont(); };

// Inits the function. ie sends a message showing that it exists
void InfinityWorld::Init()
{
    // Construct logger message
    std::string loggerMessage = "Loading: Infinity World!, Version: " +
        std::to_string(static_cast<int>(PLUGIN_VERSION_MAJOR)) +
        "." + std::to_string(static_cast<int>(PLUGIN_VERSION_MINOR)) +
        "." + std::to_string(static_cast<int>(PLUGIN_VERSION_REVISION));

    // Log the message
    logger.info(loggerMessage.c_str());

    // Subscribe to PlayerJoinEvent
    auto playerJoinEventSubscription = Event::PlayerJoinEvent::subscribe([this](const Event::PlayerJoinEvent& event) {
        if (!_hasStartedGen)
        {
            logger.info("Started Gen.");

            _hasStartedGen = true;

            Schedule::repeat([this]() {
                Pass(this);
                }, 1);
        }
        return true;
        });
}




void InfinityWorld::cont()
{
    std::vector<std::shared_ptr<Chunk>> chunkArray; // Moved outside the player loop

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
                    Chunk* currentChunk = new Chunk(CurrentChunkPos, _sn, 16, 192, 16); // Create a new chunk
                    currentChunk->createChunkData(); // Generate chunk data
                    chunkArray.push_back(std::make_shared<Chunk>(*currentChunk)); // Add the chunk to the array
                    _loadedBeforeMap.insert({ chunkHash, true }); // Mark the chunk as loaded
                }
            }
        }

    }


    for (auto& C : chunkArray)
    {
        C->placeChunkData(); // Place chunk data in the world
    }
}


InfinityWorld::InfinityWorld()
{
	// Just a temp simplex noise var should never be called in this funct
	_sn = new FastNoiseLite(1337);

    _sn->SetFractalOctaves(9); // Set the number of octaves
    _sn->SetFractalLacunarity(0.4f); // Set the lacunarity
	pool = new BS::thread_pool(std::thread::hardware_concurrency() / 2);
}

