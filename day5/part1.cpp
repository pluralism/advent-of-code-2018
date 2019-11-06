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
		cout << react(s) << '\n';
	}
	
	return 0;
}
