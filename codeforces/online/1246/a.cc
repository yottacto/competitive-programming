// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
ll n, p;

int ones(ll x)
{
    auto count = 0;
    for (; x; x /= 2)
        count += x & 1;
    return count;
}

int calc()
{
    for (auto i = 1ll; i <= 32; i++) {
        auto tn = n - i * p;
        if (tn >= i && ones(tn) <= i)
            return i;
    }
    return -1;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> p;
    std::cout << calc() << "\n";
}

