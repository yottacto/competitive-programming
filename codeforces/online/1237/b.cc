// ml:run = $bin < input
#include <iostream>
#include <unordered_map>

auto constexpr maxn = 100007;
int a[maxn];
int b[maxn];
int n;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    std::unordered_map<int, int> id;
    for (auto i = 0; i < n; i++) {
        std::cin >> a[i];
        id[a[i]] = i;
    }
    for (auto i = 0; i < n; i++)
        std::cin >> b[i];
    auto min = n;
    auto res = 0;
    for (auto i = n - 1; i >= 0; i--) {
        if (id[b[i]] > min)
            res++;
        min = std::min(min, id[b[i]]);
    }
    std::cout << res << "\n";
}

