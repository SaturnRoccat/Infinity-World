#pragma once
#include <llapi\mc\Vec2.hpp>
#include <llapi\mc\Vec3.hpp>
#include "fastNoiselite.hpp"
#include "biomeManager\biomeManager.h"
#include <memory>
#include <llapi/LoggerAPI.h>


typedef uint8_t BlockID;

struct packedData
{
    int x, y, z;
};

class chunkPosition
{
public:
    int x;
    int z;

    // Constructor taking a Vec3 object
    chunkPosition(Vec3 other)
    {
        this->x = int(other.x / 16);
        this->z = int(other.z / 16);
    }

    // Constructor taking a Vec2 object by reference
    chunkPosition(Vec2& other)
    {
        this->x = int(other.x / 16);
        this->z = int(other.y / 16);
    }

    // Constructor taking individual x and z values
    chunkPosition(int x, int z)
    {
        this->x = x;
        this->z = z;
    }

    // Default constructor
    chunkPosition() { x = 0; z = 0; }

    // Overloaded equality operator
    bool operator==(const chunkPosition& other) const
    {
        return x == other.x && z == other.z;
    }

    // Hash function for using chunkPosition as a key in unordered containers
    inline std::size_t hash()
    {
        std::size_t h1 = std::hash<int>()(this->x);
        std::size_t h2 = std::hash<int>()(this->z);
        return h1 ^ (h2 << 1);
    }

    // Convert chunkPosition to a string representation
    std::string toString() const
    {
        std::ostringstream oss;
        oss << "x: " << x << ", z: " << z;
        return oss.str();
    }
};

class Chunk
{
public:
    // Constructor
    Chunk(chunkPosition worldPositionOfChunk,
        FastNoiseLite* noise,
        std::vector<std::string>* TD,
        biomeManager* bm,
        int xSize = 16,
        int ySize = 128,
        int zSize = 16)
        : worldPositionOfChunk(worldPositionOfChunk),
        _noise(noise),
        _tileDataVector(TD),
        _bm(bm),
        xSize(xSize),
        ySize(ySize),
        zSize(zSize)
    {};

    // Function to create the chunk data
    void createChunkData();

    // Function to place the chunk data
    void placeChunkData();

    // Function to recalculate the chunk data
    void recalculateChunkData();

public:
    chunkPosition worldPositionOfChunk; // The world position of the chunk
    int xSize; // The size of the chunk in the x-direction
    int ySize; // The size of the chunk in the y-direction
    int zSize; // The size of the chunk in the z-direction

private:
    // Private helper functions to calculate different parts of the chunk data
    bool calculateGround(packedData pkcd, BlockID& sampleBlock);
    bool calculateWall(packedData pkcd, BlockID& sampleBlock);
    bool calculateCeiling(packedData pkcd, BlockID& sampleBlock);

private:
    // Private member variables
    std::vector<std::vector<std::vector<BlockID>>> _chunkData; // The chunk data
    FastNoiseLite* _noise; // Pointer to the FastNoiseLite object
    biomeManager* _bm; // Pointer to the biomeManager object
    std::vector<std::string>* _tileDataVector; // Pointer to the tile data vector
};
