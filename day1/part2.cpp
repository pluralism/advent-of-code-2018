#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <unordered_set>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("input1");
    auto sum = 0;
    std::unordered_set<int> seen_sums{sum};

    std::vector<int> nums;
    std::copy(std::istream_iterator<int>(fin), std::istream_iterator<int>(), std::back_inserter<std::vector<int>>(nums));
    bool part2Completed = false;
    while(!part2Completed)
    {
        for (const auto& x : nums)
        {
            sum += x;

            if (seen_sums.find(sum) != seen_sums.end())
            {
                part2Completed = true;
                cout << sum << '\n';
                break;
            }
            seen_sums.insert(sum);
        }
    }
    return 0;
}
