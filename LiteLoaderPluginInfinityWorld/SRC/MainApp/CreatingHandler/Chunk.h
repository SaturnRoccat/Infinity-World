#pragma once
#include <llapi\mc\Vec2.hpp>
#include <llapi\mc\Vec3.hpp>

#include "fastNoiselite.hpp"
#include "biomeManager\biomeManager.h"
#include <memory>
#include <llapi/LoggerAPI.h>


class chunkPosition
{
public:
    int x;
    int z;

    chunkPosition(Vec3 other)
    {
        this->x = int(other.x / 16);
        this->z = int(other.z / 16);
    }

    chunkPosition(Vec2& other)
    {
        this->x = int(other.x / 16);
        this->z = int(other.y / 16);
    }

    chunkPosition(int x, int z)
    {
        this->x = x;
        this->z = z;
    }



    chunkPosition() { x = 0; z = 0; }

    bool operator==(const chunkPosition& other) const
    {
        return x == other.x && z == other.z;
    }


    bool operator!=(const chunkPosition& other) const
    {
        if (this->x != other.x)
        {
            return true;
        }

        if (this->z != other.z)
        {
            return true;
        }
        
        return false;
    }
    inline std::size_t hash()
    {
        std::size_t h1 = std::hash<int>()(this->x);
        std::size_t h2 = std::hash<int>()(this->z);
        return h1 ^ (h2 << 1);
    }
    std::string toString() const
    {
        std::ostringstream oss;
        oss << "x: " << x << ", z: " << z;
        return oss.str();
    }
};

enum collisionSide
{
    TOP,
    BOTTOM,
    SIDE
};

struct blkPos
{
    int x;
    int y;
    int z;
    collisionSide side;
};

class Chunk
{
public:
    Chunk(chunkPosition worldPositionOfChunk,
        FastNoiseLite *noise,
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

    void createChunkData();
    void placeChunkData();
    void recalculateChunkData();
public:
    chunkPosition worldPositionOfChunk; 
    int xSize; 
    int ySize; 
    int zSize;
private:
    void findAirBlocks(const std::vector<std::vector<std::vector<uint8_t>>>& _chunkData, std::queue<blkPos>& airQueue);

    void findTouchingStoneBlocks
    (const std::vector<std::vector<std::vector<uint8_t>>>& _chunkData,
        std::queue<blkPos>& airQueue,
        std::vector<blkPos>& touchingStoneBlocks);
private:
    std::vector<std::vector<std::vector<uint8_t>>> _chunkData;
    FastNoiseLite* _noise;
    biomeManager* _bm;
    std::vector<std::string>* _tileDataVector;
};

