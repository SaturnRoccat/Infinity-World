#include "InfinityWorld.h"
#include <llapi\EventAPI.h>
#include <llapi\mc\Level.hpp>
#include <llapi\mc\Block.hpp>
#include "BS_thread_pool.hpp"

#include <llapi/EventAPI.h>
#include <llapi/ScheduleAPI.h>
#include <mutex>
#include <memory>

#include <llapi/mc/Objective.hpp>
#include <llapi/mc/Player.hpp>
#include <llapi/mc/Scoreboard.hpp>
#include <llapi/mc/Types.hpp>
#include <math.h>




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

    // Setup

    _masterTiledata.insert({ 0u, "minecraft:air" });
    _masterTiledata.insert({ 1u, "minecraft:stone" });



    // Subscribe to PlayerJoinEvent
    auto playerJoinEventSubscription = Event::PlayerJoinEvent::subscribe([this](const Event::PlayerJoinEvent& event) {
        if (!_hasStartedGen)
        {
            logger.info("Started Gen.");

            _hasStartedGen = true;

            Schedule::repeat([this]() {
                Pass(this);
                }, this->perpassDelay);
        }
        return true;
        });
}

void InfinityWorld::memoryCleanup()
{
    for (auto& c : chunkArray)
    {
        delete c;
    }
}


               
void InfinityWorld::cont()
{
    switch (_tickIndex)
    {
        // This should ALLWAYS be on the first tick
        case 0: {
            produceNoiseData();
            _tickIndex++;
            break;
        }
        // This should ALLWAYS be on the last tick
        case 1: {
            finalizeData();
            _tickIndex++;
            break;
        }
        // We do this last pass to handle all memory cleanups that are needed becuase of a bug in LL using a std::shared_ptr for auto memory management doesnt 
        // work so we have to manage it our self and we cant delete it after use becuase the heap corrupts so i just decided to make a whole gen pass for it
        case 2: {
            memoryCleanup();
            _tickIndex = 0;
            break;
        }
    }
}


InfinityWorld::InfinityWorld()
{
	// Just a temp simplex noise var should never be called in this funct
	_sn = new FastNoiseLite(9191);
    _sn->SetNoiseType(FastNoiseLite::NoiseType_Value);
    // _sn->SetFractalType(FastNoiseLite::FractalType_DomainWarpProgressive);
	pool = new BS::thread_pool(std::thread::hardware_concurrency() / 2);
}

