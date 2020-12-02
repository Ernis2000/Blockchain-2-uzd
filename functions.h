#pragma once
#include "transaction.h"
#include "user.h"
#include "block.h"
#include "blockchain.h"
#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <ctime>
#include <bitcoin/bitcoin.hpp>

const int USER_AMOUNT = 1000;
const int TRANSACTION_AMOUNT = 10000;

void generateUsers(std::vector<user>& users);
void generateTransactions(std::vector<transaction>& Transactions, const std::vector<user>& users);
bc::hash_digest create_merkle(bc::hash_list& merkle);
void mining(Blockchain& block_chain, std::vector<Block>& Bblock, std::vector<transaction>& TransactionsToExecute);
