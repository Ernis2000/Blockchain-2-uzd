#include "hash.h"

std::string hashfunction(std::string word)
{

	unsigned int sum = 0;
	if (word == "")
	{
		word += std::to_string(sum);
	}
	for (int i : word)
	{
		unsigned int value = i;
		sum += (value * value);
		sum += (value % sum) * value;
		sum += sum * sum;
		sum += sum << 3;

	}
	sum = sum >> 2;
	std::stringstream ss;
	ss << std::hex << sum;
	std::string result = (ss.str());
	while (result.length() != 64)
	{
		for (unsigned int tempresult : result)
		{
			tempresult = tempresult * (sum >> 2);
			tempresult += tempresult >> 2;
			tempresult += tempresult | sum;
			ss.str("");
			ss << std::hex << tempresult;
			result += ss.str();
		}
		if (result.length() > 64)
		{
			result = result.substr(0, 64);
		}
	}
	

	return result;
}