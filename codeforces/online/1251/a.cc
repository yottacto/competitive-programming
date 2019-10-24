// ml:run = $bin < input
#include <bits/stdc++.h>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::string s;
        std::cin >> s;
        std::set<char> all;
        char last = 0;
        for (auto ch : s) {
            if (last && last == ch) {
                last = 0;
            } else {
                if (last)
                    all.insert(last);
                last = ch;
            }
        }
        if (last)
            all.insert(last);
        std::string res;
        for (auto ch : all)
            res += ch;
        std::cout << res << "\n";
    }
}

