// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <set>

auto constexpr maxn = 50007;
auto constexpr inf = 1000000000;

struct point
{
    int x;
    int y;
    int z;
    int id;
};

bool operator<(point const& a, point const& b)
{
    return a.x < b.x
        || (a.x == b.x && a.y < b.y)
        || (a.x == b.x && a.y == b.y && a.z < b.z)
        || (a.x == b.x && a.y == b.y && a.z == b.z && a.id < b.id);
}

point operator-(point const& a, point const& b)
{
    return point{
        a.x - b.x,
        a.y - b.y,
        a.z - b.z,
        b.id,
    };
}

point a[maxn];
int out_id[maxn];
int next[maxn];
int prev[maxn];
int n;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 1; i <= n; i++) {
        std::cin >> a[i].x >> a[i].y >> a[i].z;
        a[i].id = i;
    }
    a[0] = point{-inf, -inf, -inf, 0};
    a[n + 1] = point{inf, inf, inf, n + 1};
    std::sort(a + 1, a + n + 1);
    for (auto i = 1; i <= n; i++) {
        out_id[i] = a[i].id;
        a[i].id = i;
    }
    std::set<point> all;
    for (auto i = 0; i <= n; i++) {
        all.emplace(a[i + 1] - a[i]);
        next[i] = i + 1;
        prev[i + 1] = i;
    }
    for (auto i = 0; i < n; i += 2) {
        // std::cout << all.size() << "\n";
        // for (auto const& p : all)
        //     std::cout << "[" << p.x << "," << p.y << "," << p.z << ", " << p.id << "] ";
        // std::cout << "\n";
        auto now = *all.begin();
        std::cout << out_id[now.id] << " " << out_id[next[now.id]] << "\n";
        all.erase(all.begin());
        all.erase(a[now.id] - a[prev[now.id]]);
        all.erase(a[next[next[now.id]]] - a[next[now.id]]);
        all.emplace(a[next[next[now.id]]] - a[prev[now.id]]);
        next[prev[now.id]] = next[next[now.id]];
        prev[next[next[now.id]]] = prev[now.id];
    }
}

