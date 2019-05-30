// ml:run = $bin < input
// ml:std = c++14
#include <iostream>

auto constexpr maxn = 100007;
int a[maxn];
int count[maxn];
int first[maxn];
int last[maxn];
int n, k;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k;
    for (auto i = 1; i <= k; i++) {
        std::cin >> a[i];
        count[a[i]]++;
        if (!first[a[i]])
            first[a[i]] = i;
        last[a[i]] = i;
    }
    auto res = 0;
    for (auto i = 1; i <= n; i++) {
        if (!count[i])
            res++;
        if (i > 1 && (!first[i - 1] || !last[i] || first[i - 1] > last[i]))
            res++;
        if (i < n && (!first[i + 1] || !last[i] || first[i + 1] > last[i]))
            res++;
    }
    std::cout << res << "\n";
}

