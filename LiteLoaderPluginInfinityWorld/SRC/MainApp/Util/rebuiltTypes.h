#pragma once
#include <iostream>
// This is a struct that matches the internal ChunkBlockPos. I didnt make this ambiennt on the Liteloader discord made this. Thanks to them
struct ChunkBlockPos {
    uint8_t x, z;
    int16_t height;

    inline constexpr ChunkBlockPos() :
        x{ 0 }, z{ 0 }, height{ 0 } {}

    inline constexpr ChunkBlockPos(const BlockPos& rhs) :
        x{ static_cast<uint8_t>(rhs.x >> 4) },
        z{ static_cast<uint8_t>(rhs.z >> 4) },
        height{ static_cast<int16_t>(rhs.y) } {}

};