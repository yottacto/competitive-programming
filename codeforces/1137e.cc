// ml:run = $bin < input
#include <iostream>
#include <vector>

using ll = long long;

struct point
{
    ll x;
    ll y;
};

int n, m;
ll b, s;

auto slope(point const& a, point const& b)
{
    return (a.y - b.y) / (double)(a.x - b.x);
}

auto calc(point const& a)
{
    return a.x * s + b + a.y;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;

    std::vector<point> q;
    q.reserve(m);
    q.emplace_back(point{0, 0});
    for (auto i = 0; i < m; i++) {
        int opt;
        std::cin >> opt;
        if (opt == 1) {
            int k;
            std::cin >> k;
            q.clear();
            q.emplace_back(point{0, 0});
            b = s = 0;
            n += k;
        } else if (opt == 2) {
            int k;
            std::cin >> k;
            auto p = point{n, -(n * s + b)};
            while (q.size() >= 2 && slope(p, q.back()) <= slope(q.back(), q[q.size() - 2]))
                q.pop_back();
            q.emplace_back(p);
            n += k;
        } else if (opt == 3) {
            ll tb, ts;
            std::cin >> tb >> ts;
            b += tb;
            s += ts;
        }
        while (q.size() >= 2 && calc(q.back()) >= calc(q[q.size() - 2]))
            q.pop_back();
        auto [pos, value] = q.back();
        value += pos * s + b;
        std::cout << pos + 1 << " " << value << "\n";
    }
}

