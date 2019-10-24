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
        std::string odd;
        std::string even;
        for (auto ch : s) {
            auto num = ch - '0';
            if (num & 1)
                odd += ch;
            else
                even += ch;
        }

        std::string res;
        auto i = 0u;
        auto j = 0u;
        while (i < odd.size() || j < even.size()) {
            if (i < odd.size() && j < even.size()) {
                if (odd[i] < even[j])
                    res += odd[i++];
                else
                    res += even[j++];
            } else if (i < odd.size()) {
                res += odd[i++];
            } else {
                res += even[j++];
            }
        }
        std::cout << res << "\n";
    }
}

