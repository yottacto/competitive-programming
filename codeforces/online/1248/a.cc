// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        int n;
        std::cin >> n;
        auto odd = 0;
        for (auto i = 0; i < n; i++) {
            int x;
            std::cin >> x;
            odd += x & 1;
        }

        int m;
        std::cin >> m;
        ll res{};
        for (auto i = 0; i < m; i++) {
            int x;
            std::cin >> x;
            if (x & 1)
                res += odd;
            else
                res += n - odd;
        }
        std::cout << res << "\n";
    }
}

