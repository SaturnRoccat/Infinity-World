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
#include "Util\TickRespectiveFunction\TickRespectiveFunction.h"

#define SEED 9999


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

    _tileDataVectorNew.push_back("minecraft:air");
    _tileDataVectorNew.push_back("minecraft:stone" );
    _tileDataVectorNew.push_back("minecraft:dirt" );
    _tileDataVectorNew.push_back("minecraft:grass" );
    _tileDataVectorNew.push_back("minecraft:moss_block" );

    bm = new biomeManager(&_tileDataVectorNew, SEED);



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
    if (dataPlaced)
    {
        for (auto& c : chunkArray)
        {
            delete c;
        }
    }
}


               
void InfinityWorld::cont()
{
    switch (_tickIndex)
    {
        // This should ALLWAYS be on the first tick
        case 0: {
            produceNoiseData();
            calculatedBlocks = false;
            calculatingBlocks = false;
            _tickIndex++;
            break;
        }
        // This handles the biome setting and making the correct blocks
        case 1: {
            recalculateBlocks();
            if (calculatedBlocks)
            {
                _tickIndex++;
            }
            break;
        }
        // This should ALLWAYS be on the last tick
        case 2: {
            finalizeData();
            if (dataPlaced)
            {
                _tickIndex++;
            }
            break;
        }
        // We do this last pass to handle all memory cleanups that are needed becuase of a bug in LL using a std::shared_ptr for auto memory management doesnt 
        // work so we have to manage it our self and we cant delete it after use becuase the heap corrupts so i just decided to make a whole gen pass for it
        case 3: {
            memoryCleanup();
            _tickIndex = 0;
            dataPlaced = false;
            break;
        }
    }
}


InfinityWorld::InfinityWorld()
{
	// Just a temp simplex noise var should never be called in this funct
	_sn = new FastNoiseLite(2222);
    _sn->SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2S);
    _sn->SetFractalOctaves(6);
    // _sn->SetFractalType(FastNoiseLite::FractalType_DomainWarpProgressive);
	pool = new BS::thread_pool(std::thread::hardware_concurrency() / 2);
}

