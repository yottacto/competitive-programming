#include <bits/stdc++.h>

using ll = long long;

int n;

struct data
{
    int id;
    ll area;
};

bool query_less(int i, int j, int k)
{
    std::cout << "2 " << i << " " << j << " " << k << "\n";
    std::cout.flush();
    int x;
    std::cin >> x;
    return x > 0;
}

ll query_area(int i, int j, int k)
{
    std::cout << "1 " << i << " " << j << " " << k << "\n";
    std::cout.flush();
    ll x;
    std::cin >> x;
    return x;
}

void work()
{
    auto next = 2;
    for (auto i = 3; i <= n; i++) {
        if (query_less(1, i, next))
            next = i;
    }

    std::vector<data> da(n + 1);
    ll max = 0;
    std::vector<int> opp;
    for (auto i = 2; i <= n; i++) {
        if (i == next)
            continue;
        auto d = data{i, query_area(1, next, i)};
        da[i] = d;
        if (d.area > max) {
            max = d.area;
            opp.clear();
            opp.emplace_back(i);
        } else if (d.area == max) {
            opp.emplace_back(i);
        }
    }
    std::vector<data> left;
    std::vector<data> right;
    if (opp.size() == 2) {
        if (query_less(1, opp[1], opp[0]))
            std::swap(opp[1], opp[0]);
    }
    left.emplace_back(da[opp[0]]);
    for (auto i = 2; i <= n; i++) {
        if (i == opp[0] || i == next)
            continue;
        if (query_less(1, i, opp[0]))
            left.emplace_back(da[i]);
        else
            right.emplace_back(da[i]);
    }
    std::sort(left.begin(), left.end(), [](auto const& a, auto const& b) {
        return a.area < b.area;
    });
    std::sort(right.begin(), right.end(), [](auto const& a, auto const& b) {
        return a.area > b.area;
    });
    std::vector<int> res;
    res.emplace_back(1);
    res.emplace_back(next);
    for (auto i : left)
        res.emplace_back(i.id);
    for (auto i : right)
        res.emplace_back(i.id);
    std::cout << "0 ";
    for (auto i : res)
        std::cout << i << " ";
    std::cout << "\n";
    std::cout.flush();
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n;
    work();
}

