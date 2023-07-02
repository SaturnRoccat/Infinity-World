#pragma once
#include <llapi\HookAPI.h>
#include <llapi\mc\Block.hpp>
#include <llapi\mc\LevelChunk.hpp>
#include <llapi\mc\ChunkBlockPos.hpp>
// #include "rebuiltTypes.h"
#include <memory>
#include <llapi\mc\BlockActor.hpp>
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
	try
	{
		SymCall("?setBlockSimple\@LevelChunk\@\@QEAAXAEBVChunkBlockPos\@\@AEBVBlock\@\@\@Z", void, LevelChunk*, ChunkBlockPos*, Block*)(chunk, pos, block);
	}
	catch (...)
	{
		logger.info("CBP: X {}, Y {}, Z {}", std::to_string(pos->x), std::to_string(pos->y.mVal), std::to_string(pos->z));
	}

}