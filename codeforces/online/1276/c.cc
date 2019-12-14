// ml:run = $bin < input
#include <bits/stdc++.h>

std::vector<int> a;
int n;

std::vector<std::vector<int>> b;
int p, q;
int max;

bool fill(int r, int c, bool fillin = false)
{
    std::unordered_map<int, int> count;
    for (auto i : a)
        count[i]++;
    auto sum = 0;
    for (auto& p : count) {
        p.second = std::min(r, p.second);
        sum += p.second;
    }
    if (!fillin)
        return sum >= r * c;
    std::vector<int> num;
    for (auto const& p : count)
        for (auto j = 0; j < p.second; j++)
            num.emplace_back(p.first);
    std::sort(num.begin(), num.end(), [&](auto const& a, auto const& b) {
        return count[a] > count[b];
    });
    b.clear();
    b.resize(r, std::vector<int>(c));
    auto k = 0;
    for (auto i = 0; i < c; i++) {
        for (auto j = 0; j < r; j++) {
            b[j][(i + j) % c] = num[k++];
        }
    }
    return true;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n;
    a.resize(n);
    for (auto i = 0; i < n; i++)
        std::cin >> a[i];

    // i for rows
    for (auto i = 1; i * i <= n; i++) {
        auto l = i;
        auto r = n / i;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            if (fill(i, mid))
                l = mid;
            else
                r = mid;
        }
        if (fill(i, r))
            l = r;
        if (fill(i, l) && l * i >= max) {
            max = l * i;
            p = i;
            q = l;
        }
    }
    std::cout << max << "\n";
    std::cout << p << " " << q << "\n";
    fill(p, q, true);
    for (auto i = 0; i < p; i++) {
        for (auto j = 0; j < q; j++)
            std::cout << b[i][j] << " ";
        std::cout << "\n";
    }
}

