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

const int USER_AMOUNT = 1000;
const int TRANSACTION_AMOUNT = 10000;

void generateUsers(std::vector<user>& users);
void generateTransactions(std::vector<transaction>& Transactions, const std::vector<user>& users);
void mining(Blockchain& block_chain, std::vector<Block>& Bblock);