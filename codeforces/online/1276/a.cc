// ml:run = $bin < input
#include <bits/stdc++.h>

std::vector<int> pos;
std::string s;
int n;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> s;
        pos.clear();
        n = s.size();
        for (auto i = 0; i < n - 2; ) {
            if (s[i] == 'o' && s[i + 1] == 'n' && s[i + 2] == 'e') {
                pos.emplace_back(i + 1);
                i += 3;
            } else if (s[i] == 't' && s[i + 1] == 'w' && s[i + 2] == 'o') {
                if (i < n - 4 && s[i + 3] == 'n' && s[i + 4] == 'e') {
                    pos.emplace_back(i + 2);
                    i += 5;
                } else {
                    pos.emplace_back(i + 1);
                    i += 3;
                }
            } else {
                i++;
            }
        }
        std::cout << pos.size() << "\n";
        for (auto i : pos)
            std::cout << i + 1 << " ";
        std::cout << "\n";
    }
}

