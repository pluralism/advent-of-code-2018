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

	map<int, map<int, int>> guards_sleeping_frequency;
	int guard;
	int begin_sleeping_time{}, end_sleeping_time;
	for (const auto& entry : entries)
	{
		smatch m;
		if (regex_search(entry.data, m, guard_pattern))
		{
			guard = stoi(m[1]);
			begin_sleeping_time = end_sleeping_time = 0;
		}

		if (regex_search(entry.data, m, falls_asleep_pattern))
		{
			begin_sleeping_time = stoi(m[1]);
		}

		if (regex_search(entry.data, m, wakes_up_pattern))
		{
			end_sleeping_time = stoi(m[1]);
			for (auto i = begin_sleeping_time; i < end_sleeping_time; i++)
			{
				guards_sleeping_frequency[i][guard]++;
			}
		}
	}

	auto max_frequency = 0;
	auto best_minute = 0;
	auto best_guard = 0;
	for (const auto& minutes_data : guards_sleeping_frequency)
	{
		for (const auto& guard_data : minutes_data.second)
		{
			if (guard_data.second > max_frequency)
			{
				best_minute = minutes_data.first;
				best_guard = guard_data.first;
				max_frequency = guard_data.second;
			}
		}
	}

	cout << best_minute * best_guard << '\n';
	return 0;
}
