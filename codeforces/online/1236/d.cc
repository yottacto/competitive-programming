// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <algorithm>
#include <vector>
#include <iterator>

using ll = long long;
ll n, m, k;

std::vector<std::vector<int>> row;
std::vector<std::vector<int>> col;

bool check()
{
    ll up{0};
    ll down{n + 1};
    ll left{0};
    ll right{m + 1};
    auto tot = 0ll;
    ll x{1};
    ll y{1};
    auto d = 0;
    while (up + 1 != down && left + 1 != right) {
        // std::cerr << "up=" << up << " down=" << down
        //     << " left=" << left << " right=" << right << "\n";
        // std::cerr << "(x, y) = (" << x << ", " << y << ")\n";
        if (tot > k)
            return false;
        if (d == 0) {
            ll bound = *std::upper_bound(row[x].begin(), row[x].end(), y);
            bound = std::min(bound, right);
            tot += (right - bound) * (down - x);
            right = bound;
            y = bound - 1;
            up = x;
        } else if (d == 1) {
            ll bound = *std::upper_bound(col[y].begin(), col[y].end(), x);
            bound = std::min(bound, down);
            tot += (down - bound) * (y - left);
            down = bound;
            x = bound - 1;
            right = y;
        } else if (d == 2) {
            ll bound = *std::prev(std::lower_bound(row[x].begin(), row[x].end(), y));
            bound = std::max(bound, left);
            tot += (bound - left) * (x - up);
            left = bound;
            y = bound + 1;
            down = x;
        } else {
            ll bound = *std::prev(std::lower_bound(col[y].begin(), col[y].end(), x));
            bound = std::max(bound, up);
            tot += (bound - up) * (right - y);
            up = bound;
            x = bound + 1;
            left = y;
        }
        d = (d + 1) % 4;
    }
    return tot == k;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> m >> k;
    row.resize(n + 1);
    col.resize(m + 1);
    for (auto i = 1; i <= n; i++) {
        row[i].emplace_back(0);
        row[i].emplace_back(m + 1);
    }
    for (auto i = 1; i <= m; i++) {
        col[i].emplace_back(0);
        col[i].emplace_back(n + 1);
    }
    for (auto i = 0; i < k; i++) {
        ll x, y;
        std::cin >> x >> y;
        row[x].emplace_back(y);
        col[y].emplace_back(x);
    }
    for (auto i = 1; i <= n; i++)
        std::sort(row[i].begin(), row[i].end());
    for (auto i = 1; i <= m; i++)
        std::sort(col[i].begin(), col[i].end());

    if (check())
        std::cout << "Yes\n";
    else
        std::cout << "No\n";
}

