#pragma once
#include <llapi\mc\Block.hpp>
#include <llapi\mc\Level.hpp>
#include <llapi\mc\LevelChunk.hpp>
#include <llapi\mc\LevelListener.hpp>
#include <llapi\mc\ChunkPos.hpp>
#include "..\CreatingHandler\Chunk.h"
#include <llapi\mc\BlockPos.hpp>
#include <llapi\mc\BlockSource.hpp>
#include <llapi\mc\WorldBlockTarget.hpp>
#include <llapi\mc\BlockActor.hpp>
#include <llapi\mc\ChunkBlockPos.hpp>

#include <llapi\HookAPI.h>
#include "hooks.h"
// #include "rebuiltTypes.h"
extern Logger logger;
// Basic struct used for easy storage of loose block data
struct compoundedData
{
	std::string name = "NULL";
	unsigned short tileData = 0;


	bool operator==(const compoundedData& other) const
	{
		if (this == &other)  // Check for self-comparison
			return true;

		if (this->name == other.name && this->tileData == other.tileData)
			return true;

		return false;
	}

	bool operator!=(const compoundedData& other) const
	{
		return !(*this == other);
	}


};

/**
 * @brief This is an extended version of the level API and should be used instead of the Level class
 */
class WorldUtils : public Level
{
public:
    /**
     * @brief Sets a block at the specified position in the world
     *
     * @param pos The position of the block
     * @param blk A pointer to the Block object to be set
     * @param dim The dimension in which the block should be set (default is 0)
     * @return true if the block was set successfully, false otherwise
     */
    __forceinline static bool WUSetBlock(const BlockPos& pos, Block* blk, int dim = 0)
    {
        static BlockSource* bs;
        static int localDim = 100;
        if (dim != localDim)
        {
            localDim = dim;
            bs = getBlockSource(localDim);
        }
        return bs->setBlock(pos, *blk, 3, nullptr, nullptr);
    }

    /**
     * @brief Sets a block at the specified position in the world using the block name and tile data
     *
     * @param pos The position of the block
     * @param name The name of the block
     * @param dim The dimension in which the block should be set (default is 0)
     * @param tileData The tile data for the block (default is 0u)
     * @return true if the block was set successfully, false otherwise
     */
    __forceinline static bool WUSetBlock(const BlockPos& pos, const std::string& name, int dim = 0, unsigned short tileData = 0u)
    {
        static Block* BLK;
        static compoundedData CD;

        compoundedData TempCD = { name, tileData };

        if (TempCD != CD)
        {
            CD = TempCD;
            BLK = Block::create(CD.name, CD.tileData);
        }

        if (!BLK)
        {
            return false;
        }

        return WUSetBlock(pos, BLK, dim);
    }

    
    __forceinline static bool WUFastSetBlock( ChunkBlockPos* CBP, Block* blk, BlockPos& blkPos, int dim = 0)
    {

        BlockSource* blkSource;
        static int localDim = 100;
        static ChunkPos oldChunkPos;
        static LevelChunk* LVC;


        ChunkPos newChunkPos(blkPos.x / 16, blkPos.z / 16);
        blkSource = Level::getBlockSource(dim);
        localDim = dim;
        oldChunkPos = newChunkPos;
        LVC = blkSource->getChunkAt(blkPos);
        if (localDim != dim || oldChunkPos != newChunkPos)
        {
            localDim = dim;
            oldChunkPos = newChunkPos;
            LVC = blkSource->getChunkAt(blkPos);
        }

        if (!LVC)
        {
            logger.fatal("LVC NULL, Local DIM: {}, blkSource: {}, oldChunkPos: X {}, Z {}", localDim, static_cast<void*>(blkSource), oldChunkPos.x, oldChunkPos.z);
            return false;
        }
        else
        {
            // logger.info("X {}, Y{}, Z{}", blkPos.x, blkPos.y, blkPos.z);
            // hookedSetBlock(LVC, CBP, blk);


            hookedSetBlock(LVC, CBP, blk);

            return true;
        }

        // Have no idea why i do this should be a void 
    }

    __forceinline static bool WUFastSetBlock(BlockPos& pos, const std::string& name, int dim = 0, unsigned short tileData = 0u)
    {
        static Block* BLK;
        static compoundedData CD;

        compoundedData TempCD = { name, tileData };

        if (TempCD != CD)
        {
            CD = TempCD;
            BLK = Block::create(CD.name, CD.tileData);
        }

        if (!BLK)
        {
            return false;
        }
        ChunkBlockPos CRB(pos.x % 16, pos.y, pos.z % 16); // Create ChunkBlockPos using the provided pos
        return WUFastSetBlock(&CRB, BLK, pos, dim); // Call the other overload
    }

    // TODO: Implement when needed but this shouldnt be needed for awhile;
    // __forceinline static bool WUSetBlock(const BlockPos& pos, int dim, CompoundTag* nbt);
public:
};


