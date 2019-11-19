// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;

ll work()
{
    ll n;
    std::cin >> n;
    if (n == 1)
        return 1;
    ll p{0};
    auto tn = n;
    for (auto i = 2ll; i * i <= tn; i++) {
        if (tn % i == 0) {
            while (tn % i == 0) {
                tn /= i;
            }
            if (p)
                return 1;
            else
                p = i;
        }
    }
    if (tn > 1) {
        if (p)
            return 1;
        p = tn;
    }
    return p;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cout << work() << "\n";
}

