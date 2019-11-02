#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <regex>
#include <algorithm>
using namespace std;

struct entry
{
	int year;
	int month;
	int day;
	int hour;
	int minute;

	string data;
};

int main()
{
	ifstream fin("input.txt");
	vector<entry> entries;
	regex guard_pattern(R"(Guard #(\d+))");
	regex falls_asleep_pattern(R"(:(\d+)\] falls)");
	regex wakes_up_pattern(R"(:(\d+)\] wakes)");
	regex date_pattern(R"(\[(\d+)\-(\d+)\-(\d+) (\d+):(\d+)\])");

	while(!fin.eof())
	{
		string str;
		smatch m;
		getline(fin, str);
		
		if (regex_search(str, m, date_pattern))
		{
			entries.push_back(entry{stoi(m[1]), stoi(m[2]), stoi(m[3]), stoi(m[4]), stoi(m[5]), str});
		}
	}

	std::sort(entries.begin(), entries.end(), [](const auto& e1, const auto& e2)
	{
		return e1.data < e2.data;
	});

	map<int, vector<pair<int, int>>> guards_sleeping_intervals;
	int guard;
	int begin_sleeping_time, end_sleeping_time;
	for (const auto& entry : entries)
	{
		smatch m;
		if (regex_search(entry.data, m, guard_pattern))
		{
			guard = stoi(m[1]);
			begin_sleeping_time = end_sleeping_time = 0;

			if (guards_sleeping_intervals.find(guard) == guards_sleeping_intervals.end())
			{
				guards_sleeping_intervals[guard] = vector<pair<int, int>>{};
			}
		}

		if (regex_search(entry.data, m, falls_asleep_pattern))
		{
			begin_sleeping_time = stoi(m[1]);
		}

		if (regex_search(entry.data, m, wakes_up_pattern))
		{
			end_sleeping_time = stoi(m[1]);

			guards_sleeping_intervals[guard].push_back({begin_sleeping_time, end_sleeping_time});
		}
	}

	const auto sleepiest_guard = *std::max_element(guards_sleeping_intervals.begin(), guards_sleeping_intervals.end(),
		[](const auto& g1, const auto& g2)
	{
		auto g1_sum = 0;
		auto g2_sum = 0;

		for (const auto& g1_interval : g1.second)
		{
			g1_sum += (g1_interval.second - g1_interval.first);
		}

		for (const auto& g2_interval : g2.second)
		{
			g2_sum += (g2_interval.second - g2_interval.first);
		}

		return g1_sum < g2_sum;
	});

	vector<int> minutes(60);

	for (const auto& interval : sleepiest_guard.second)
	{
		for(auto i = interval.first; i < interval.second; i++)
		{
			minutes[i]++;
		}
	}

	cout << sleepiest_guard.first * std::distance(minutes.begin(), std::max_element(minutes.begin(), minutes.end())) << '\n';
	return 0;
}
