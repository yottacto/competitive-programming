// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;
auto constexpr mo = 998244353ll;

ll add(ll x, ll y)
{
    auto res = (x + y) % mo;
    if (res < 0)
        res += mo;
    return res;
}

ll sub(ll x, ll y)
{
    auto res = (x - y) % mo;
    if (res < 0)
        res += mo;
    return res;
}

ll mul(ll x, ll y)
{
    auto res = (x * y) % mo;
    if (res < 0)
        res += mo;
    return res;
}

int n;
std::vector<int> a;
std::string s;

bool check(int x)
{
    auto b = a;
    std::vector<int> op;
    for (auto i = 1; i < n; i++) {
        if (b[i - 1] == x)
            continue;
        op.emplace_back(i);
        b[i - 1] = x;
        b[i] = !b[i];
    }
    if (b[n - 1] == x) {
        std::cout << op.size() << "\n";
        for (auto i : op)
            std::cout << i << " ";
        std::cout << "\n";
        return true;
    }
    return false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n >> s;
    a.resize(n);
    for (auto i = 0; i < n; i++)
        a[i] = s[i] == 'B';
    if (check(0) || check(1))
        return 0;
    std::cout << "-1\n";
}

