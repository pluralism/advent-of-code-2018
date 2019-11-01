#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
    ifstream fin("input1");
    std::vector<std::string> v;

    std::copy(std::istream_iterator<std::string>(fin), std::istream_iterator<std::string>(), std::back_inserter<std::vector<std::string>>(v));
    auto part2_completed = false;
    for (const auto &s : v)
    {
        for (const auto &s2 : v)
        {
            std::string common_s;
            for (auto i = 0; i < s.length(); i++)
            {
                if (s[i] == s2[i])
                {
                    common_s += s[i];
                }
            }

            if (s.length() - common_s.length() == 1)
            {
                cout << common_s << '\n';
                part2_completed = true;
                break;
            }
        }

        if (part2_completed) break;
    }
    return 0;
}
