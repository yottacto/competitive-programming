// ml:run = $bin < input
#include <iostream>
#include <vector>

int n;
std::vector<int> a[2];

template <class Vec>
void add(Vec const& v1, Vec const& v2, Vec & v3)
{
    v3[0] = v2[0];
    for (int i = 1; i <= n; i++)
        v3[i] = (v1[i - 1] + v2[i]) % 2;
}

template <class Vec>
int size(Vec const& v1)
{
    auto res = v1.size();
    while (v1[res - 1] == 0) res--;
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    if (n == 0) { std::cout << "-1\n"; return 0; }
    a[0].resize(n + 1);
    a[1].resize(n + 1);
    a[0][0] = 1;
    a[1][1] = 1;

    auto prev1 = 1;
    auto prev2 = 0;
    auto now = 0;
    for (int i = 0; i < n - 1; i++) {
        add(a[prev1], a[prev2], a[now]);
        prev2 = prev1;
        prev1 = now;
        now = 1 - now;
    }

    auto l1 = size(a[prev1]);
    std::cout << l1 - 1 << "\n";
    a[prev1].resize(l1);
    for (auto i : a[prev1])
        std::cout << i << " ";
    std::cout << "\n";

    auto l2 = size(a[prev2]);
    std::cout << l2 - 1 << "\n";
    a[prev2].resize(l2);
    for (auto i : a[prev2])
        std::cout << i << " ";
    std::cout << "\n";
}

