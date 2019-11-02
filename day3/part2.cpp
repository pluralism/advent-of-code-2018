#include <iostream>
#include <fstream>
#include <regex>
#include <string>
#include <map>
using namespace std;

struct rectangle
{
	int id;
	int x;
	int y;
	int w;
	int h;
};

int main()
{
	fstream fin("input.txt");
	regex pattern(R"(#(\d+) @ (\d+),(\d+): (\d+)x(\d+))");
	map<pair<int, int>, int> visited_count;
	vector<rectangle> rectangles;

	while(!fin.eof())
	{
		string s;
		smatch m;
		getline(fin, s);

		if (regex_match(s, m, pattern))
		{
			rectangle r{ stoi(m[1]), stoi(m[2]), stoi(m[3]), stoi(m[4]), stoi(m[5]) };
			rectangles.push_back(r);

			for (auto i = r.y; i < r.y + r.h; i++)
			{
				for (auto j = r.x; j < r.x + r.w; j++)
				{
					visited_count[{j, i}]++;
				}
			}
		}
	}

	for (const auto &rectangle : rectangles)
	{
		auto claim_overlaps = false;
		for(auto i = rectangle.y; i < rectangle.y + rectangle.h; i++)
		{
			for(auto j = rectangle.x; j < rectangle.x + rectangle.w; j++)
			{
				if (visited_count[{j, i}] > 1)
				{
					claim_overlaps = true;
				}
			}
		}

		if (!claim_overlaps)
		{
			cout << rectangle.id << '\n';
			break;
		}
	}

	return 0;
}
