// ml:run = cp $bin std
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <string>
#include <vector>

using ll = long long;

struct query
{
    ll t;
    int x, y;
    bool save;
};

std::vector<query> queries;
std::vector<int> disc;
int n, p;
int tot;

auto constexpr maxn = 1000000;
double a[maxn];

void update(int l, int r, double a0, double d)
{
    for (auto i = l; i <= r; i++) {
        a[i] += a0;
        a0 += d;
    }
}

auto sum(int l, int r) -> double
{
    auto ret = 0.;
    for (auto i = l; i <= r; i++)
        ret += a[i];
    return ret;
}

void clear(int l, int r)
{
    for (auto i = l; i <= r; i++)
        a[i] = 0;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> p;
    int q;
    std::cin >> q;
    queries.resize(q);

    auto last_time = 0ll;
    auto saved = 0.;
    for (auto& i : queries) {
        std::string s;
        std::cin >> i.t >> s >> i.x >> i.y;
        i.save = (s == "save");

        update(1, n, (i.t - last_time) * p, 0);

        if (s == "save") {
            saved += sum(i.x, i.y);
            std::cout << std::fixed << std::setprecision(10)
                << saved << "\n";
            clear(i.x, i.y);
        } else {
            auto pi = i.x;
            auto d = i.y;
            auto x = saved / (d * d);
            saved = 0;
            update(pi - d + 1, pi - 1,     x,     +x);
            update(pi,         pi + d - 1, x * d, -x);
        }
        last_time = i.t;
    }
}

