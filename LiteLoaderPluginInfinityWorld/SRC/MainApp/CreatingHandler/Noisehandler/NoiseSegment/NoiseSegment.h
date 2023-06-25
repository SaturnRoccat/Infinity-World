#pragma once
#include <vector>
#include "..\..\Chunk.h"
#include <llapi\mc\Vec2.hpp>
#include <fastNoiselite.hpp>

// TODO: Write a serialize function that turns all of the data here into data that can be stored to disk 
struct int2
{
	int x;
	int y;
};
struct int3
{
	int x;
	int y;
	int z;
};
// size_t index = x + (y * width) + (z * width * height);
/**
 * @brief Represents a segment of noise data for a world.
 *        Each segment is associated with a specific offset and size.
 */
class NoiseSegment
{
public:
    /**
     * @brief Constructs a NoiseSegment object.
     *
     * @param FSN             Pointer to the FastNoiseLite object used for noise generation.
     * @param Offset          Offset of the segment.
     * @param ChunkSize       Size of each chunk in the segment. Default: {16, 128, 16}.
     * @param ChunksToContain Number of chunks to contain in each dimension. Default: {64, 64}.
     */
    NoiseSegment(FastNoiseLite* FSN,
        int2 Offset,
        int3 ChunkSize = { 16, 128, 16 },
        int3 ChunksToContain = { 64, 64 })
        : _fsn(FSN),
        _offset(Offset),
        _chunkSize(ChunkSize),
        _chunksToContain(ChunksToContain)
    {
        // Calculate the total size based on ChunkSize and ChunksToContain
        int totalSizeX = (ChunkSize.x * ChunksToContain.x) * (ChunkSize.y * ChunksToContain.y) * (ChunkSize.z * ChunksToContain.z);

        // Resize the blockValues vector to the desired size and assign all values to 0
        blockValues.resize(totalSizeX, 0);
        heightMap.resize(totalSizeX, 0);
    };

    /**
     * @brief Calculates and sets all the block data for the world.
     *        This function should only be called once or when the noise type changes.
     */
    void calculateAllBlocks();

    /**
     * @brief Calculates the heightmap for the data.
     */
    void calculateHeightMap();

    /**
    * Retrieves the block value at the specified coordinates (x, y, z).
    *
    * @param x The x-coordinate of the block.
    * @param y The y-coordinate of the block.
    * @param z The z-coordinate of the block.
    * @return The block value at the given coordinates.
    */
    __forceinline uint16_t getBlock(int x, int y, int z) {
        return blockValues[
            x +
                (y * _chunkSize.x * _chunksToContain.x) +
                (z * _chunkSize.x * _chunksToContain.x * _chunkSize.y)];
    }

    /**
     * Sets the block value at the specified coordinates (x, y, z) to the given value.
     * Optionally, the value can be set in a separate vector (otherData).
     *
     * @param x The x-coordinate of the block.
     * @param y The y-coordinate of the block.
     * @param z The z-coordinate of the block.
     * @param val The value to set for the block.
     * @param otherData (Optional) A pointer to a vector to store the block value.
     *                  If nullptr, the value is set in the blockValues vector.
     *                  This should only be used in set curcumstances.
     */
    __forceinline void setBlock(int x, int y, int z, uint16_t val, std::vector<uint16_t>* otherData = nullptr) {
        if (otherData == nullptr) {
            blockValues[
                x +
                    (y * _chunkSize.x * _chunksToContain.x) +
                    (z * _chunkSize.x * _chunksToContain.x * _chunkSize.y)] = val;
        }
        else {
            otherData->at(x +
                (y * _chunkSize.x * _chunksToContain.x) +
                (z * _chunkSize.x * _chunksToContain.x * _chunkSize.y)) = val;
        }
    }


public:


    // Stores a 1 or a 0 if it's stone or air.
    std::vector<uint16_t> blockValues;

    // Stores distances from the top of the chunk to the block that is in sunlight:
    // Eg, if a block is 5 blocks from the top of the chunk, it would be 5 at that index.
    std::vector<uint16_t> heightMap;
private:
private:
    int3 _chunkSize;        // Size of each chunk in the segment.
    int3 _chunksToContain;  // Number of chunks to contain in each dimension.
    FastNoiseLite* _fsn;    // Pointer to the FastNoiseLite object.
    int2 _offset;           // Offset of the segment.
};
