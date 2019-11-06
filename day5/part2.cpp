#include <iostream>
#include <string>
#include <fstream>
#include <algorithm>
using namespace std;

size_t react(const string& s)
{
	auto s_copy{ s };

	unsigned int i{ 0 };
	while (i < s_copy.length() - 1)
	{
		if (abs(s_copy[i] - s_copy[i + 1]) == 32)
		{
			s_copy.erase(i, 2);
			i = std::max(0, static_cast<int>(i) - 1);
		}
		else
		{
			i++;
		}
	}

	return s_copy.length();
}

int main()
{
	ifstream fin("input.txt");

	while(!fin.eof())
	{
		string s;
		getline(fin, s);
		auto result{ s.length() };
		for (int i = 'A'; i <= 'Z'; i++)
		{
			auto copy_s{ s };
			copy_s.erase(remove(copy_s.begin(), copy_s.end(), i), copy_s.end());
			copy_s.erase(remove(copy_s.begin(), copy_s.end(), i + 32), copy_s.end());
			result = std::min(static_cast<int>(result), static_cast<int>(react(copy_s)));
		}
		cout << result << '\n';
	}
	
	return 0;
}
