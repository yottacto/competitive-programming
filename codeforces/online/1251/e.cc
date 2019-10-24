// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;

struct data
{
    ll m;
    ll p;
};

int n;
std::vector<data> da;


int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        da.clear();
        da.resize(n);
        for (auto i = 0; i < n; i++)
            std::cin >> da[i].m >> da[i].p;
        std::sort(da.begin(), da.end(), [](auto const& a, auto const& b) {
            return a.m < b.m
                || (a.m == b.m && a.p < b.p);
        });
        std::map<int, int> all;
        auto before = 0;
        auto cost = 0ll;
        for (auto i = n - 1; i >= 0; i--) {
            all[da[i].p]++;
            if (i + before < da[i].m) {
                auto c = all.begin()->first;
                cost += c;
                all[c]--;
                if (!all[c])
                    all.erase(c);
                before++;
            }
        }
        std::cout << cost << "\n";
    }
}

