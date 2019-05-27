// ml:run = $bin < input
// ml:std = c++14
#include <iostream>
#include <vector>

int n, m;
std::vector<int> a;

auto judge(int mid)
{
    auto b = a;
    if (b[0] + mid >= m)
        b[0] = 0;
    for (auto i = 1; i < n; i++) {
        if (b[i] == b[i - 1])
            continue;
        if (b[i] < b[i - 1]) {
            if (b[i - 1] - b[i] <= mid)
                b[i] = b[i - 1];
            else
                return false;
            continue;
        }
        // b[i] > b[i - 1]
        if (b[i] + mid >= m && ((b[i] + mid) % m) >= b[i - 1])
            b[i] = b[i - 1];
    }
    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    a.resize(n);
    for (auto& i : a)
        std::cin >> i;
    auto l = 0;
    auto r = m;
    while (l + 1 < r) {
        auto mid = (l + r) / 2;
        if (judge(mid))
            r = mid;
        else
            l = mid;
    }
    if (judge(l))
        r = l;
    std::cout << r << "\n";
}

