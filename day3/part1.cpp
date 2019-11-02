#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>
using namespace std;

int main()
{
	fstream fin("input.txt");
	regex pattern(R"(#(\d+) @ (\d+),(\d+): (\d+)x(\d+))");
	map<pair<int, int>, int> visited_count;

	while(!fin.eof())
	{
		string s;
		smatch m;
		getline(fin, s);

		if (regex_match(s, m, pattern))
		{
			const auto x = stoi(m[2]);
			const auto y = stoi(m[3]);
			const auto w = stoi(m[4]);
			const auto h = stoi(m[5]);

			for (auto i = y; i < y + h; i++)
			{
				for (auto j = x; j < x + w; j++)
				{
					visited_count[{j, i}]++;
				}
			}
		}
	}

	const auto overlapping_area= std::count_if(visited_count.begin(), visited_count.end(), [](const auto &p)
	{
		return p.second >= 2;
	});

	cout << overlapping_area << '\n';
	return 0;
}
