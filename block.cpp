#include "block.h"

Block::Block()
{
	timestamp = time(nullptr);
}
void Block::set_transactions(const std::vector<transaction>& transactions)
{
	this->transactions = transactions;
}