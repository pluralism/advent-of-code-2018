#include <iostream>
#include <algorithm>
#include <numeric>
#include <vector>
#include <fstream>
using namespace std;

int main()
{
    ifstream fin("input1");
    std::vector<int> nums;
    std::copy(std::istream_iterator<int>(fin), std::istream_iterator<int>(), std::back_inserter<std::vector<int>>(nums));
    cout << std::accumulate(nums.begin(), nums.end(), 0) << '\n';
    return 0;
}
