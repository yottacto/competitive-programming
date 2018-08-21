// ml:run = $bin < input
#include <iostream>
#include <string>

int n;
std::string s;
int count[30];

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    std::cin >> s;
    for (auto ch : s)
        count[ch - 'a']++;
    auto one = 0;
    for (auto i = 0; i < 26; i++)
        if (count[i] >= 2) {
            std::cout << "Yes\n";
            return 0;
        } else if (count[i] == 1)
            one++;
    if (one == 1)
        std::cout << "Yes\n";
    else
        std::cout << "No\n";
}

