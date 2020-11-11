#include "functions.h"

int main(){
	std::vector<user> User;
    std::vector<transaction> Transaction;
    std::vector<transaction> Tcount;
    generateUsers(User);
    generateTransactions(Transaction, User);
    Blockchain block_chain;

    std::random_device rd;
    std::mt19937 gen(rd());

    std::vector<Block> list;
    
    while (Transaction.size() >= 100)
    {
        std::vector<transaction> temp;
        for (int i = 0; i < 100; i++)
        {
            std::uniform_int_distribution<int> index(0, Transaction.size() - 1);
            unsigned int indexes = index(gen);
            temp.push_back(Transaction[indexes]);
            Tcount.push_back(Transaction[indexes]);
            Transaction.erase(Transaction.begin() + indexes);
        }
        Block Bl;
        Bl.set_transactions(temp);
        list.push_back(Bl);
    }
    mining(block_chain, list);
    for (std::vector<transaction>::iterator i = Tcount.begin(); i != Tcount.end(); ++i)
    {
        for (std::vector<user>::iterator j = User.begin(); j != User.end(); ++j)
        {
            if ((*i).sender == (*j).public_key)
            {
                (*j).moneyCoin -= (*i).amount;
            }
        }
        std::cout << (*i).id << " " << (*i).amount << std::endl;
    }

	return 0;
}

