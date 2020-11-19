#include "blockchain.h"

void Blockchain::addblock(const Block& block)
{
	this->chain.push_back(block);
}
Block Blockchain::getLast() const {
    return this->chain.back();
}
int Blockchain::index() const {
    return this->chain.size();
}