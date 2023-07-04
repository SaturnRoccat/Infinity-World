#pragma once
#include <llapi\mc\Block.hpp>
#include <llapi\mc\BlockSource.hpp>
#include <llapi\mc\Level.hpp>
#include <llapi\mc\ChunkPos.hpp>
#include <llapi\LoggerAPI.h>


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
 *
 */
class WorldUtils : public Level
{
public:
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
			logger.error("Failed To Make Block!");
			return false;
		}


		return WUSetBlock(pos, BLK, dim);

	}


	// TODO: Implement when needed but this shouldnt be needed for awhile;
	// __forceinline static bool WUSetBlock(const BlockPos& pos, int dim, CompoundTag* nbt);
public:
};

