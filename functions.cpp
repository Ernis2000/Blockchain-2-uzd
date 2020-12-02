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

bc::hash_digest create_merkle(bc::hash_list& merkle)
{
 // Stop if hash list is empty or contains one element
 if (merkle.empty())
 return bc::null_hash;
 else if (merkle.size() == 1)
 return merkle[0];
 // While there is more than 1 hash in the list, keep looping...
 while (merkle.size() > 1)
 {
 // If number of hashes is odd, duplicate last hash in the list.
 if (merkle.size() % 2 != 0)
 merkle.push_back(merkle.back());
 // List size is now even.
 assert(merkle.size() % 2 == 0);
 // New hash list.
 bc::hash_list new_merkle;
 // Loop through hashes 2 at a time.
 for (auto it = merkle.begin(); it != merkle.end(); it += 2)
 {
 // Join both current hashes together (concatenate).
 bc::data_chunk concat_data(bc::hash_size * 2);
 auto concat = bc::serializer<
 decltype(concat_data.begin())>(concat_data.begin());
 concat.write_hash(*it);
 concat.write_hash(*(it + 1));
 // Hash both of the hashes.
 bc::hash_digest new_root = bc::bitcoin_hash(concat_data);
 // Add this to the new list.
 new_merkle.push_back(new_root);
 }
 // This is the new list.
 merkle = new_merkle;
 // DEBUG output -------------------------------------
 std::cout << "Current merkle hash list:" << std::endl;
 for (const auto& hash: merkle)
 std::cout << " " << bc::encode_base16(hash) << std::endl;
 std::cout << std::endl;
 // --------------------------------------------------
 }
 // Finally we end up with a single item.
 return merkle[0];
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
