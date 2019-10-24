// ml:run = $bin < input
#include <bits/stdc++.h>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        auto count0 = 0;
        auto count1 = 0;
        std::vector<int> len;
        for (auto i = 0; i < n; i++) {
            std::string s;
            std::cin >> s;
            for (auto ch : s)
                if (ch == '0')
                    count0++;
                else
                    count1++;
            len.emplace_back(s.size());
        }
        std::sort(len.begin(), len.end());
        auto res = 0;
        for (auto i = 0; i < n; i++) {
            auto l = len[i];
            if (l & 1) {
                if (count0 & 1)
                    count0--;
                else
                    count1--;
                l--;
            }
            if (count0 < count1)
                std::swap(count0, count1);
            if (count0 >= l) {
                count0 -= l;
                res++;
            } else {
                if (!(count0 & 1) && !(count1 & 1))
                    res++;
            }
        }
        std::cout << res << "\n";
    }
}

