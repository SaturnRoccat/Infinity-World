#pragma once
#include <unordered_map>



/*
* 0 = underground block
* 1 = surface block
* 2 = transition
*/



class biomePalate
{
public:
	biomePalate() {};

	
public:

	std::unordered_map<uint8_t, std::string> _palate;
private:
private:
};