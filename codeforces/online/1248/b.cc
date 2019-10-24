// ml:run = $bin < input
#include <bits/stdc++.h>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int n;
    std::cin >> n;
    std::vector<int> a(n);
    for (auto i = 0; i < n; i++)
        std::cin >> a[i];
    std::sort(a.begin(), a.end());
    auto sum0 = 0ll;
    for (auto i = 0; i < n/2; i++)
        sum0 += a[i];
    auto sum1 = 0ll;
    for (auto i = n/2; i < n; i++)
        sum1 += a[i];
    std::cout << sum0 * sum0 + sum1 * sum1 << "\n";
}

