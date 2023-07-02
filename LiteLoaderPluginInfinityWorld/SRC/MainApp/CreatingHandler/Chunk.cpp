#include "Chunk.h"
#include "..\Util\WorldUtils.h"
#include "..\Util\math.hpp"
#include <math.h>
#include <queue>

extern Logger logger;

void Chunk::createChunkData()
{
    const static int worldTaper = 20;
    const static float threshold = 0.2;
    const static float bias = 0.4f;

    for (int x = 0; x < xSize; x++)
    {
        std::vector<std::vector<uint8_t>> xPush;
        for (int y = 0; y < ySize; y++)
        {
            std::vector<uint8_t> yPush;
            for (int z = 0; z < zSize; z++)
            {
                float sampleX = ((worldPositionOfChunk.x * 16) + x) * 0.7;
                float sampleZ = ((worldPositionOfChunk.z * 16) + z) * 0.7;

                float noiseValue = _noise->GetNoise(
                    sampleX,
                    float(y),
                    sampleZ);

                // Retrieve moisture value using biomeManager's getData function
                float moisture = _bm->getData(sampleX, float(y), sampleZ);

                // Apply the moisture to modify the noise value
                noiseValue = lerp(noiseValue, moisture, 0.35f); // Adjust the blending factor (0.5f) as desired

                noiseValue = (noiseValue + 1.0f) / 2.0f; // Normalize noise value from range -1 to 1 to range 0 to 1


                // Apply the tapering effect based on the y coordinate and threshold
                if (y < worldTaper && noiseValue > threshold)
                {
                    float t = 1.0f - (static_cast<float>(worldTaper - y) / worldTaper);
                    float modifiedBias = bias * (1.f - (1.0f - std::pow(2.0f, -10.0f * t)));
                    noiseValue -= modifiedBias;
                    noiseValue = std::max(noiseValue, 0.0f);
                }

                noiseValue = (2.0f * noiseValue) - 1.0f; // Rescale noise value from range 0 to 1 to range -1 to 1

                if (noiseValue > threshold)
                {
                    yPush.push_back(0);
                }
                else
                {
                    yPush.push_back(1);
                }
            }
            xPush.push_back(yPush);
        }
        _chunkData.push_back(xPush);
    }
}



// 678
void Chunk::placeChunkData()
{
     for (int x = 0; x < xSize; x++)
    {
        int OverallX = int(((worldPositionOfChunk.x * 16) + x) / 2);

        for (int z = 0; z < zSize; z++)
        {
            int OverallZ = int(((worldPositionOfChunk.z * 16) + z) / 2);
            for (int y = 0; y < ySize; y++)
            {
                int yPosition = int(y - 62);
                BlockPos position(OverallX, yPosition, OverallZ);
                // note this wont support multi dimensions so this needs to be changed 
                // WorldUtils::WUSetBlock(position, _tileDataVector->at(_chunkData[x][y][z]), 0);

                WorldUtils::WUFastSetBlock(position, _tileDataVector->at(_chunkData[x][y][z]));

                // Level::setBlock(position, 0, _tileData->at(_chunkData[x][y][z]), 0u);
            }
        }
    }
}

void Chunk::findAirBlocks(const std::vector<std::vector<std::vector<uint8_t>>>& _chunkData, std::queue<blkPos>& airQueue)
{
    for (int x = 0; x < xSize; ++x)
    {
        for (int y = 0; y < ySize; ++y)
        {
            for (int z = 0; z < zSize; ++z)
            {
                if (_chunkData[x][y][z] == 0u)
                {
                    blkPos airPos = { x, y, z, SIDE }; // this can be any value, since we don't care about side for air blocks
                    airQueue.push(airPos);
                }
            }
        }
    }
}
struct CheckStruct
{
    int x;
    int y;
    int z;
};

void Chunk::findTouchingStoneBlocks
    (const std::vector<std::vector<std::vector<uint8_t>>>& _chunkData,
        std::queue<blkPos>& airQueue,
        std::vector<blkPos>& touchingStoneBlocks)
{
    std::vector<std::vector<std::vector<bool>>> visited
    (xSize,
        std::vector<std::vector<bool>>(ySize,
            std::vector<bool>(zSize,
                false)));

    while (!airQueue.empty())
    {
        blkPos current = airQueue.front();
        airQueue.pop();

        // check neighbors in all six directions
        std::vector<CheckStruct> directions = 
        { 
            {0, 1, 0},
            {0, -1, 0},
            {1, 0, 0},
            {-1, 0, 0},
            {0, 0, 1},
            {0, 0, -1}
        };


        for (CheckStruct& dir : directions)
        {
            /*CheckStruct calculationPosition = {
                clamp(directions.x, 0, xSize - 1),
                clamp(directions.y, 0, ySize - 1),
                clamp(directions.z, 0, zSize - 1),
            };*/




        }
       
    }
}


void Chunk::recalculateChunkData()
{
    std::queue<blkPos> airQueue;
    std::vector<blkPos> allColidingStone;
    findAirBlocks(_chunkData, airQueue);
    findTouchingStoneBlocks(_chunkData, airQueue, allColidingStone);



    // ISTG if anyone says anything about this swtich statement i will find you
    // And i will bonk you with a stick
    // https://tenor.com/bVx9C.gif
    for (auto& blk : allColidingStone)
    {
        switch (blk.side)
        {
        case TOP: {
            _chunkData[blk.x][blk.y][blk.z] = 3u;
            break;
        }
        case BOTTOM:
        case SIDE: {
            
            break;
        }
        default:
            break;
        }
    }
}





//
//void Chunk::recalculateChunkData()
//{
//    for (int x = 0; x < xSize; x++)
//    {
//        for (int z = 0; z < zSize; z++)
//        {
//            for (int y = ySize - 1; y > -1; y--)
//            {
//                auto& current = _chunkData[x][y][z];
//                auto& sample = _chunkData[x][clamp(y + 1, 0, ySize - 1)][z];
//                if (current == 1u && sample == 0u)
//                {
//                    current = 3u;
//                }
//            }
//        }
//    }
//
//}
