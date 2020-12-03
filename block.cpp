#include "block.h"
#include "functions.h"
Block::Block()
{
	timestamp = time(nullptr);
}
void Block::set_transactions(const std::vector<transaction>& transactions)
{
	this->transactions = transactions;
	std::vector<std::string> transactionIDs;
	transactionIDs.reserve(transactions.size());
	for (const auto& transaction : transactions)
	{
		transactionIDs.push_back(transaction.id);
	}
	MerkleRootHash = create_merkle(transactionIDs);
}

std::vector<transaction> Block::getTransactions() const
{
	return this->transactions;
}
