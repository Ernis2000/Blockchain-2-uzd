#include "blockchain.h"

void Blockchain::addblock(const Block& block)
{
	this->chain.push_back(block);
}