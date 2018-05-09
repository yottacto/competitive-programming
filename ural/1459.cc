// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <set>

auto constexpr mo = 1000000000;
int n, m;
int now, prev;
int ans;

template <class T>
void add(T& lhs, T rhs)
{
    lhs = (lhs + rhs) % mo;
}

std::unordered_map<int, int> f[2];

auto get(int st, int p)
{
    return (st >> (2*p)) & 3;
}

void update(int& st, int p, int v)
{
    st &= (~0) ^ (3 << (2*p));
    st |= v << (2*p);
}

auto get_dir(int st, int p)
{
    auto t = get(st, p);
    return t == 1
        ? 1
        : t == 2 ? -1 : 0;
}

auto find(int st, int p)
{
    for (auto i = p, d = 0, step = get_dir(st, p); ; i += step) {
        d += get_dir(st, i);
        if (!d) return i;
    }
    return -1;
}

std::set<int> all;

void dp(int i, int j)
{
    std::swap(now, prev);
    f[now].clear();
    // std::cout << "(" << i << "," << j << ") : " << f[prev].size() << ": ";
    for (auto const& p : f[prev]) {
        // std::cout << p.first << " ";
        auto st = p.first;
        all.insert(st);
        if (j == 0) st <<= 2;
        auto v = p.second;
        auto left = get(st, j);
        auto up = get(st, j+1);
        if (!left && !up) {
            if (i != n - 1 && j != m - 1) {
                update(st, j, 1);
                update(st, j+1, 2);
                add(f[now][st], v);
            }
        } else if (left == up) {
            update(st, find(st, j + 2-left), left);
            update(st, j, 0);
            update(st, j+1, 0);
            add(f[now][st], v);
        } else if (left == 1 && up == 2) {
            if (i == n - 1 && j == m - 1)
                add(ans, v);
        } else if (left == 2 && up == 1) {
            update(st, j, 0);
            update(st, j+1, 0);
            add(f[now][st], v);
        } else if (left) {
            if (i != n - 1) add(f[now][st], v);
            if (j != m - 1) {
                update(st, j, 0);
                update(st, j+1, left);
                add(f[now][st], v);
            }
        } else if (up) {
            if (j != m - 1) add(f[now][st], v);
            if (i != n - 1) {
                update(st, j, up);
                update(st, j+1, 0);
                add(f[now][st], v);
            }
        }
    }
    // std::cout << "\n";
}

auto calc()
{
    now = 0; prev = 1;
    ans = 0;
    f[now].clear();
    f[0][0] = 1;
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < m; j++)
            dp(i, j);
    add(ans, ans);
    // std::cout << all.size() << "\n";
    return ans;
}

int main()
{
    std::cin >> m >> n;
    // m = 5;
    // n = 32;
    int prev{0};
    int now;
    // for (n = 4; n < 5; n++) {
    //     now = calc();
    //     std::cout << "(" << n << ", " << m << ") : " << now << "\n";
    //     prev = now;
    // }
    std::cout << calc() << "\n";
}

