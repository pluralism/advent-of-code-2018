#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <algorithm>
#include <sstream>
using namespace std;

template <class Container>
void split(const string& s, Container& cont, const char delim)
{
	stringstream ss(s);
	string token;
	while(getline(ss, token, delim))
	{
		cont.push_back(stoi(token));
	}
}

int manhattan_distance(const pair<int, int>& p1, const ::pair<int, int>& p2)
{
	return abs(p2.first - p1.first) + abs(p2.second - p1.second);
}

struct closest_data
{
	int distance;
	pair<int, int> point;
};

int main()
{
	fstream fin("input.txt");
	vector<pair<int, int>> points{};

	while (!fin.eof())
	{
		string line;
		getline(fin, line);

		vector<int> coordinates{};
		split(line, coordinates, ',');
		points.emplace_back(make_pair(coordinates[0], coordinates[1]));
	}

	auto min_x = numeric_limits<int>::max();
	auto max_x = numeric_limits<int>::min();
	auto min_y = numeric_limits<int>::max();
	auto max_y = numeric_limits<int>::min();
	for (const auto& point : points)
	{
		min_x = min(min_x, point.first);
		max_x = max(max_x, point.first);
		min_y = min(min_y, point.second);
		max_y = max(max_y, point.second);
	}

	set<string> infinite_points;
	map<string, closest_data> closest;

	for (auto i = min_y; i <= max_y; i++)
	{
		for (auto j = min_x; j <= max_x; j++)
		{
			auto closest_distance = numeric_limits<int>::max();
			auto closest_point = pair<int, int>{};
			auto is_invalid_point = false;

			for (const auto& point : points)
			{
				const auto distance = manhattan_distance(make_pair(j, i), point);
				if (distance < closest_distance)
				{
					closest_distance = distance;
					closest_point = point;
					is_invalid_point = false;
				} else if (distance == closest_distance)
				{
					is_invalid_point = true;
				}
			}

			if (is_invalid_point)
			{
				continue;
			}

			const auto is_infinite_point = j == min_x || j == max_x || i == min_y || i == max_y;

			if (is_infinite_point)
			{
				const auto key = to_string(closest_point.first) + to_string(closest_point.second);
				infinite_points.insert(key);
			} else
			{
				const auto key = to_string(j) + to_string(i);
				closest.insert(make_pair(key, closest_data{ closest_distance, closest_point }));
			}
		}
	}

	map<string, int> positions_by_point{};
	for (const auto& p : closest)
	{
		if (infinite_points.count(p.first) == 0)
		{
			const auto key = to_string(p.second.point.first) + to_string(p.second.point.second);
			if (positions_by_point.count(key) == 0)
			{
				positions_by_point.insert(make_pair(key, 1));
			} else
			{
				positions_by_point.insert_or_assign(key, positions_by_point.find(key)->second + 1);
			}
		}
	}

	auto result = numeric_limits<int>::min();
	for(const auto& p : positions_by_point)
	{
		result = max(result, p.second);
	}

	cout << "Result: " << result << '\n';
	
	return 0;
}
