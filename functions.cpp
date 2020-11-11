#include "functions.h"
#include "hash.h"

void generateUsers(std::vector<user> &users) 
{
    user User;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomAmount(100, 1000000);
    for(int i = 0; i < USER_AMOUNT; i++)
    {
        User.name = "Name" + std::to_string(i);
        User.public_key = hashfunction(User.name);
        User.moneyCoin = randomAmount(gen);
        users.push_back(User);
    }
}
void generateTransactions(std::vector<transaction>& Transactions, const std::vector<user>& users)
{
    unsigned int number;
    unsigned int count = 0;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> randomAmount(0, 999);
    transaction temp;
    for (int i = 0; i < TRANSACTION_AMOUNT; i++)
    {
        number = randomAmount(gen);
        temp.sender = users[number].public_key;
        temp.receiver = users[randomAmount(gen)].public_key;
        temp.id = hashfunction(temp.sender + temp.receiver + std::to_string(count));
        std::uniform_int_distribution<int> money(0, users[number].moneyCoin);
        temp.amount = money(gen);
        Transactions.push_back(temp);
        count++;    
    }
}

void mining(Blockchain& block_chain, std::vector<Block>& Bblock)
{
    std::string hash_difficulty;
    std::string zero = std::to_string(0);
    for (int i = 0; i < Bblock.size(); i++)
    {
        if (i == 0)
        {
            Bblock[i].previousHash = hashfunction("first hash");
        }
        else {
            Bblock[i].previousHash = Bblock[i - 1].currentHash;
        }
        for (int l = 0; l < Bblock[i].difficulty_target; l++)
        {
            hash_difficulty.insert(0, zero);
        }
        do {
            Bblock[i].nonce++;
            Bblock[i].currentHash = hashfunction(std::to_string(Bblock[i].nonce) +
                Bblock[i].previousHash + std::to_string(Bblock[i].timestamp) +
                std::to_string(Bblock[i].version));
        } while (Bblock[i].currentHash.substr(0, Bblock[i].difficulty_target) != hash_difficulty);
        block_chain.addblock(Bblock[i]);
        std::cout << "Block nr:" << i << "\n" << Bblock[i].currentHash << std::endl;
    }
        
}