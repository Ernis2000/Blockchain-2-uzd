#pragma once

#include<vector>
#include "block.h"

class Blockchain {
public:
	void addblock(const Block& block);
	int index() const;
	Block getLast() const;
private:
	std::vector<Block> chain;
};