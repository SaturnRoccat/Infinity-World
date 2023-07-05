#include "Chunk.h"
#include "..\Util\WorldUtils.h"
#include "..\Util\math.hpp"
#include <math.h>
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
                auto tile = _chunkData[x][y][z];
                BlockPos position(OverallX, int(y - 63), OverallZ);
                // note this wont support multi dimensions so this needs to be changed 
                if (!WorldUtils::WUSetBlock(position, _tileDataVector->at(_chunkData[x][y][z]), 0))
                {
                    // logger.error("FAILED to set block in chunk! at X {}, Y {}, Z {}", OverallX, y, OverallZ);
                }

                // Level::setBlock(position, 0, _tileDataVector->at(_chunkData[x][y][z]), 0u);
            }
        }
    }
}
void Chunk::recalculateChunkData()
{
    for (int x = 0; x < xSize; x++)
    {
        for (int z = 0; z < zSize; z++)
        {
            for (int y = ySize - 1; y > -1; y--)
            {
                BlockID& sampleBlock = _chunkData[x][y][z];

                if (!calculateGround({ x, y, z }, sampleBlock))
                {
                    calculateCeiling({ x, y, z }, sampleBlock);
                }

                // I think my code should work
                if(sampleBlock!=0)
                    sampleBlock *= _bm->getBiomeIndex(int(((worldPositionOfChunk.x * 16) + x) ), y, int(((worldPositionOfChunk.z * 16) + z) ));
            }
        }
    }
}

bool Chunk::calculateGround(packedData pkcd, BlockID& sampleBlock) 
{
    if (sampleBlock == 1u)
    {
        int sampleY = clamp<int>(pkcd.y + 1, 0, ySize - 1);
        if (_chunkData[pkcd.x][sampleY][pkcd.z] == 0u)
        {
            sampleBlock = 3u;
            // Do some special calls
            _chunkData[pkcd.x][clamp<int>(pkcd.y - 1, 0, ySize - 1)][pkcd.z] = 2u;
            _chunkData[pkcd.x][clamp<int>(pkcd.y - 2, 0, ySize - 1)][pkcd.z] = 2u;
            
            return true;
        }
    }

    // If everything fails 
    return false;
}
bool Chunk::calculateWall(packedData pkcd, BlockID& sampleBlock)
{
    if (sampleBlock == 1u)
    {

        for (int xOffset = -1; xOffset < 1; xOffset += 2)
        {
            int sampleX = clamp<int>(pkcd.x + xOffset, 0, xSize - 1);
            if (_chunkData[sampleX][pkcd.y][pkcd.z] == 0u)
            {
                sampleBlock = 5u;
                return true;
            }
        }

        for (int zOffset = -1; zOffset < 1; zOffset += 2)
        {
            int sampleZ = clamp<int>(pkcd.z + zOffset, 0, zSize - 1);
            if (_chunkData[pkcd.x][pkcd.y][sampleZ] == 0u)
            {
                sampleBlock = 5u;
                return true;
            }
        }
    }


    // If everything fails
    return false;
}
bool Chunk::calculateCeiling(packedData pkcd, BlockID& sampleBlock)
{

    if (sampleBlock == 1u)
    {
        int sampleY = clamp<int>(pkcd.y - 1, 0, ySize - 1);
        if (_chunkData[pkcd.x][sampleY][pkcd.z] == 0u)
        {

            _chunkData[pkcd.x][clamp<int>(pkcd.y + 2, 0, ySize - 1)][pkcd.z] = 5u;
            _chunkData[pkcd.x][clamp<int>(pkcd.y + 3, 0, ySize - 1)][pkcd.z] = 5u;
            sampleBlock = 4u;
            return true;
        }
    }
    return false;
}