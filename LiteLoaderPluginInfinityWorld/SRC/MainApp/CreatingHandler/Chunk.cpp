#include "Chunk.h"
#include "..\Util\WorldUtils.h"
extern Logger logger;

void Chunk::createChunkData()
{
    const static int worldTaper = 50;
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
                float noiseValue = _noise->GetNoise(
                    float(((worldPositionOfChunk.x * 16) + x) / 2),
                    float(y),
                    float(((worldPositionOfChunk.z * 16) + z) / 2));


                noiseValue = (noiseValue + 1.0f) / 2.0f; // Normalize noise value from range -1 to 1 to range 0 to 1
                if (y < worldTaper && noiseValue > threshold) {

                    // Calculate the normalized t value between 0 and 1
                    float t = 1.0f - (static_cast<float>(worldTaper - y) / worldTaper);

                    // Apply the ease-in exponential function to modify the bias factor
                    float modifiedBias = bias * (1.f - (1.0f - std::pow(2.0f, -10.0f * t)));

                    noiseValue -= modifiedBias; // Subtract the modified bias from the noise value
                    noiseValue = std::max(noiseValue, 0.0f); // Clamp the noise value to ensure it doesn't go below 0

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

                BlockPos position(OverallX, int(y), OverallZ);
                // note this wont support multi dimensions so this needs to be changed 
                WorldUtils::WUSetBlock(position, _tileData->at(_chunkData[x][y][z]));

                // Level::setBlock(position, 0, _tileData->at(_chunkData[x][y][z]), 0u);
            }
        }
    }
}