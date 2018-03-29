// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <set>

struct land
{
    int importance;
    int len;
    // lower left pos
    int x;
    int y;
};

std::istream& operator>>(std::istream& is, land& l)
{
    is >> l.importance >> l.len >> l.x >> l.y;
    return is;
}

struct pos
{
    int x;
    int y;
};

std::vector<land> lands;
std::vector<pos> points;
std::set<int> disx;
std::set<int> disy;
int a, l, n;

bool inrange(int x, int l, int r)
{
    return l <= x && x <= r;
}

bool inside(pos const& p1, pos const& p2, int l2)
{
    auto px = p1.x;
    auto py = p1.y;
    auto x = p2.x;
    auto y = p2.y;
    return inrange(px, x, x + l2 - 1)
        && inrange(py, y, y + l2 - 1);
}

bool intersect_square(pos const& p1, int l1, pos const& p2, int l2)
{
    if (inside(p1,                        p2, l2)) return true;
    if (inside(pos{p1.x+l1-1, p1.y},      p2, l2)) return true;
    if (inside(pos{p1.x,      p1.y+l1-1}, p2, l2)) return true;
    if (inside(pos{p1.x+l1-1, p1.y+l1-1}, p2, l2)) return true;
    if (inside(p2,                        p1, l1)) return true;
    if (inside(pos{p2.x+l2-1, p2.y},      p1, l1)) return true;
    if (inside(pos{p2.x,      p2.y+l2-1}, p1, l1)) return true;
    if (inside(pos{p2.x+l2-1, p2.y+l2-1}, p1, l1)) return true;

    return false;
}

// p, lower left point
bool judge(pos const& p, int mid)
{
    for (auto const& land : lands) {
        if (land.importance <= mid)
            continue;
        if (intersect_square(p, a, pos{land.x, land.y}, land.len))
            return false;
    }
    return true;
}

int main()
{
    std::cin >> l >> a;
    std::cin >> n;
    lands.resize(n);
    for (auto i = 0; i < n; i++) {
        std::cin >> lands[i];
        auto x = lands[i].x;
        auto y = lands[i].y;
        disx.insert(x);
        if (x - 1 >= 1) disx.insert(x - 1);
        if (x + 1 <= l) disx.insert(x + 1);
        disy.insert(y);
        if (y - 1 >= 1) disy.insert(y - 1);
        if (y + 1 <= l) disy.insert(y + 1);
    }
    disx.insert(1);
    disx.insert(a);
    disy.insert(1);
    disy.insert(a);

    auto ans = 200;
    for (auto x : disx)
    for (auto y : disy) {
        if (!inrange(x + a - 1, 1, l) || !inrange(y + a - 1, 1, l))
            continue;
        // bin search for impt
        auto l = 1;
        auto r = 100;
        while (l + 1 < r) {
            auto mid = (l + r) / 2;
            if (judge({x, y}, mid))
                r = mid;
            else
                l = mid;
        }
        if (judge({x, y}, l)) r = l;
        if (!judge({x, y}, r)) r = 200;
        ans = std::min(ans, r);
    }

    if (ans == 200)
        std::cout << "IMPOSSIBLE\n";
    else
        std::cout << ans << "\n";
}

