#pragma once

#include <string>
#include <vector>
#include <ctime>
#include "transaction.h"

class Block {
public:
	std::string previousHash;
	std::string currentHash;
	std::time_t timestamp{};
	unsigned int version = 1;
	unsigned int difficulty_target = 1;
	unsigned long long int nonce = 0;

	Block();
	void set_transactions(const std::vector<transaction>& transactions);

private:
	std::vector<transaction> transactions;
};