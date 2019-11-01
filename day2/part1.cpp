#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <unordered_map>
#include <set>
using namespace std;

int main()
{
    ifstream fin("input1");
    std::vector<std::string> v;

    std::copy(std::istream_iterator<std::string>(fin), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string>>(v));
    auto two_multiplier = 0;
    auto three_multiplier = 0;
    for (const auto &s : v)
    {
        std::set<char> two, three;
        std::unordered_map<char, int> m;
        std::for_each(s.begin(), s.end(), [&](const auto &c)
        {
            m[c]++;
            if (m[c] == 2)
            {
                two.insert(c);
            }

            if (m[c] == 3)
            {
                two.erase(c);
                three.insert(c);
            }

            if(m[c] > 3)
            {
                two.erase(c);
                three.erase(c);
            }
        });
        two_multiplier += !two.empty() ? 1 : 0;
        three_multiplier += !three.empty() ? 1 : 0;
    }

    cout << two_multiplier * three_multiplier << '\n';
    return 0;
}
