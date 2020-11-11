#pragma once
#include<string>

class transaction {
	public:
		std::string id;
		std::string sender;
		std::string receiver;
		int amount;
};