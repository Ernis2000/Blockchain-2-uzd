#include "functions.h"
#include "hash.h"
int main(){
	std::vector<user> User;
    std::vector<transaction> Transaction;
    generateUsers(User);
    generateTransactions(Transaction, User);
    Blockchain block_chain;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::vector<Block> list;
    std::vector<int> Index;
    unsigned int Failedverifications = 0;
    for (size_t i = 0; i < Transaction.size(); i++)
    {
        for (std::vector<user>::iterator j = User.begin(); j != User.end(); ++j)
        {
            if (Transaction[i].sender == (*j).public_key && Transaction[i].amount > (*j).moneyCoin)
            {
                Failedverifications++;
               
            }
        }
        if (Transaction[i].id != hashfunction(Transaction[i].sender + Transaction[i].receiver + std::to_string(Transaction[i].amount)))
        {
            Failedverifications++;
        }
    }
    std::cout << "Failed verifications:" << Failedverifications << std::endl;
    std::vector<transaction> TransactionCopy;
    while (Transaction.size())
    {
        TransactionCopy = Transaction;
        std::vector<transaction> TransactionsToExecute;
        std::vector<transaction> temp;
        if (Transaction.size() >= 100)
        {
            for (int i = 0; i < 100; i++)
            {
             
                std::uniform_int_distribution<int> index(0, Transaction.size() - 1);
                unsigned int indexes = index(gen);
                temp.push_back(Transaction[indexes]);
                Transaction.erase(Transaction.begin() + indexes);
            }
        }
        else {
            for (size_t i = 0; i != Transaction.size(); ++i)
            {
                temp.push_back(Transaction[i]);
            }
        }
        
        Block Bl;
        Bl.set_transactions(temp);
        list.push_back(Bl);
        if (list.size() == 5)
        {
            mining(block_chain, list, TransactionsToExecute);
            
            Index.clear();
            for (size_t i = 0; i != Transaction.size(); ++i)
            {
                for (std::vector<transaction>::iterator j = TransactionsToExecute.begin(); j != TransactionsToExecute.end(); j++)
                {
                    if (Transaction[i].id == (*j).id)
                    {
                        Index.push_back(i);
                    }
                }
            }
            for (size_t i = 0; i != Index.size(); ++i)
            {
                Transaction.erase(Transaction.begin() + Index[i]);
            }
            
            for (std::vector<transaction>::iterator i = TransactionsToExecute.begin(); i != TransactionsToExecute.end(); ++i)
            {
                for (std::vector<user>::iterator j = User.begin(); j != User.end(); ++j)
                {
                    if ((*i).sender == (*j).public_key)
                    {
                        (*j).moneyCoin -= (*i).amount;
                    }
                    else if ((*i).receiver == (*j).public_key)
                    {
                        (*j).moneyCoin += (*i).amount;
                    }
                }
            }
           
            list.clear();
            TransactionsToExecute.clear();
        }
    }
	return 0;
}

