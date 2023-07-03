#pragma once
#include <llapi\HookAPI.h>
#include <llapi\mc\Block.hpp>
#include <llapi\mc\LevelChunk.hpp>
#include <llapi\mc\ChunkBlockPos.hpp>
// #include "rebuiltTypes.h"
#include <memory>
#include <llapi\mc\BlockActor.hpp>
#include "macro.h"
#include <llapi\LoggerAPI.h>

extern Logger logger;





__forceinline void hookedSetBlock(LevelChunk* chunk, ChunkBlockPos* pos, Block* block)
{

	/*
	* I wouldnt usualy write comments like this but because the hooking API is undocumented. i will
	* What this call below this comment does is.
	* First find the function with the symbol "?setBlockSimple\@LevelChunk\@\@QEAAXAEBVChunkBlockPos\@\@AEBVBlock\@\@\@Z"
	* Then define the params
	* then we call out to it with the params this function takes in
	* 
	*/

	if (!chunk)
	{
		logger.fatal("CHUNK pointer was NULL");
		throw std::runtime_error("CHUNK pointer was NULL");
	}

	if (!pos)
	{
		logger.fatal("POS pointer was NULL");
		throw std::runtime_error("POS pointer was NULL");
	}

	if (!block)
	{
		logger.fatal("BLOCK pointer was NULL");
		throw std::runtime_error("BLOCK pointer was NULL");
	}


	// logger.info("CBP: X {}, Y {}, Z {}", std::to_string(pos->x), std::to_string(pos->y.mVal), std::to_string(pos->z));
	SymCall("?setBlockSimple\@LevelChunk\@\@QEAAXAEBVChunkBlockPos\@\@AEBVBlock\@\@\@Z", void, LevelChunk*, ChunkBlockPos*, Block*)(chunk, pos, block);

}



// OLD code just here if i need it
// Block* hookedSetBlock(LevelChunk* chunk, ChunkBlockPos* pos, Block* block, BlockSource* bls, std::shared_ptr<BlockActor> ba)
//{
//
//	/*
//	* I wouldnt usualy write comments like this but because the hooking API is undocumented. i will
//	* What this call below this comment does is.
//	* First find the function with the symbol "?setBlockSimple\@LevelChunk\@\@QEAAXAEBVChunkBlockPos\@\@AEBVBlock\@\@\@Z"
//	* Then define the params
//	* then we call out to it with the params this function takes in
//	* 
//	*/
//
//	if (!chunk)
//	{
//		logger.fatal("CHUNK pointer was NULL");
//		throw std::runtime_error("CHUNK pointer was NULL");
//	}
//
//	if (!pos)
//	{
//		logger.fatal("POS pointer was NULL");
//		throw std::runtime_error("POS pointer was NULL");
//	}
//
//	if (!block)
//	{
//		logger.fatal("BLOCK pointer was NULL");
//		throw std::runtime_error("BLOCK pointer was NULL");
//	}
//
//
//	//	logger.info("CBP: X {}, Y {}, Z {}", std::to_string(pos->x), std::to_string(pos->y.mVal), std::to_string(pos->z));
//	return SymCall(
//		"?setBlock@LevelChunk@@QEAAAEBVBlock@@AEBVChunkBlockPos@@AEBV2@PEAVBlockSource@@V?$shared_ptr@VBlockActor@@@std@@@Z",
//		Block*,
//		LevelChunk*,
//		ChunkBlockPos*,
//		Block*,
//		BlockSource*,
//		std::shared_ptr<BlockActor>)
//		(chunk ,pos, block, bls, ba);
//
//}
