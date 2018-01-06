// ml:run = $bin < input
#include <iostream>
#include <vector>

int n;
std::vector<int> a;
std::vector<int> tree;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    a.resize(n + 1);
    auto isomorphic = true;
    auto tot = 1;
    std::cin >> a[0];
    for (int i = 1; i <= n; i++) {
        std::cin >> a[i];
        tot += a[i];
        if (a[i] > 1 && a[i - 1] > 1)
            isomorphic = false;
    }

    if (isomorphic) {
        std::cout << "perfect\n";
        return 0;
    }

    std::cout << "ambiguous\n";
    tree.resize(tot);
    tree[0] = -1;
    auto now = 1;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < a[i]; j++)
            tree[now + j] = now - 1;
        now += a[i];
    }
    for (auto i : tree)
        std::cout << i + 1 << " ";
    std::cout << "\n";

    now = 1;
    auto level_start = 0;
    for (int i = 1; i <= n; i++) {
        tree[now] = level_start;
        for (int j = 1; j < a[i]; j++)
            tree[now + j] = now - 1;
        level_start = now;
        now += a[i];
    }
    for (auto i : tree)
        std::cout << i + 1 << " ";
    std::cout << "\n";
}

