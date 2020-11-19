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
        std::uniform_int_distribution<int> money(0, users[number].moneyCoin);
        temp.amount = money(gen);
        temp.id = hashfunction(temp.sender + temp.receiver + std::to_string(temp.amount));
        Transactions.push_back(temp);
        count++;    
    }
}

std::string MerkleTree(std::vector<std::string>& transactions)
{
    while (transactions.size() > 1)
    {
        if (transactions.size() % 2 != 0)
            transactions.push_back(transactions.back());

        std::vector<std::string> merkle;
        std::string joined_data;
        for (auto it = transactions.begin(); it != transactions.end(); it += 2)
        {
            joined_data = "";
            joined_data += *it;
            joined_data += (*(it + 1));
            merkle.push_back(hashfunction(joined_data));
        }
        transactions = merkle;
   }
    return transactions[0];
}

void mining(Blockchain& block_chain, std::vector<Block>& Bblock, std::vector<transaction> &TransactionsToExecute)
{
   
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> selectBlock(0, Bblock.size() - 1);
    std::string hash_difficulty;
    std::string zero = std::to_string(1);
    bool done = false;
    while (!done)
    {
        
        unsigned int i = selectBlock(gen);
        std::string Block_hash;
        if (block_chain.index() == 0)
        {
            Bblock[i].previousHash = hashfunction("first hash");
        }
        else {
            Bblock[i].previousHash = block_chain.getLast().MerkleRootHash;
        }

        for (int l = 0; l < Bblock[i].difficulty_target; l++)
        {
            hash_difficulty.insert(0, zero);
        }
       
        do {
            if (Bblock[i].nonce > 100000)
            {
                break;
            }
           
            Bblock[i].nonce++;
            std::stringstream ToHash;
            ToHash << Bblock[i].nonce << Bblock[i].previousHash << Bblock[i].timestamp << Bblock[i].MerkleRootHash << Bblock[i].version;
            Block_hash = hashfunction(ToHash.str());
            Bblock[i].MerkleRootHash = Block_hash;
            
        } while (Bblock[i].MerkleRootHash.substr(0, Bblock[i].difficulty_target) != hash_difficulty);
        
        if (Bblock[i].MerkleRootHash.substr(0, Bblock[i].difficulty_target) == hash_difficulty)
        {
            done = true;
            hash_difficulty.clear();
            TransactionsToExecute = Bblock[i].getTransactions();
            block_chain.addblock(Bblock[i]);
            std::cout<<"Block: " << block_chain.index() << "\n" << "Hash: " << Bblock[i].MerkleRootHash << std::endl;
        }


    }
        

       
}