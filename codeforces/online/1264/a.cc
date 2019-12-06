// ml:run = $bin < input
#include <bits/stdc++.h>

auto constexpr maxn = 400007;
int a[maxn];
int n;
std::vector<int> cut;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n;
        cut.clear();
        std::cin >> a[0];
        for (auto i = 1; i < n; i++) {
            std::cin >> a[i];
            if (i <= n/2 && a[i] < a[i - 1])
                cut.emplace_back(i);
        }
        int m = cut.size();
        auto g = 0;
        auto s = 0;
        auto b = 0;
        auto max = 0;
        auto cg = 0;
        auto cs = 0;
        auto cb = 0;
        for (auto i = 0; i < m; i++) {
            while (s < m && cut[s] - cut[g] <= cut[g])
                s++;
            while (b < m && cut[b] - cut[s] <= cut[g])
                b++;
            if (s == m || b == m || cut[b] > n / 2)
                break;
            max = cut.back();
            cg = cut[g];
            cs = cut[s] - cg;
            cb = max - cs - cg;
            break;
        }
        std::cout << cg << " " << cs << " " << cb << "\n";
    }
}

