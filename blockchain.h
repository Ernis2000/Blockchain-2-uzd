#pragma once

#include<vector>
#include "block.h"

class Blockchain {
public:
	void addblock(const Block& block);
private:
	std::vector<Block> chain;
};