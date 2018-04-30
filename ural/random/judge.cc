// ml:run = cp $bin judge
#include <iostream>
#include <algorithm>
#include <iterator>
#include <fstream>
#include <vector>

using ll = long long;
struct data { int x; int y; ll value; };

auto constexpr inf = 1ll << 50;
auto ans = -inf;

auto& operator>>(std::istream& is, data& d)
{
    is >> d.x >> d.y >> d.value;
    return is;
}

std::vector<data> da;
std::vector<int> a;

auto inrange(int x, int l, int r)
{
    return l <= x && x <= r;
}

auto judge()
{
    std::ifstream fin{"bfdiff.out1"};
    int lx, rx, ly, ry;
    fin >> lx >> rx >> ly >> ry;

    auto count = 0;
    auto sum = 0ll;
    for (auto const& d : da) {
        if (inrange(d.x, lx, rx) && inrange(d.y, ly, ry)) {
            count++;
            sum += d.value;
        }
    }
    if (count <= 1)
        return false;
    if (sum != ans)
        return false;

    return true;
}

template <class Vec>
void sort_unique(Vec& v)
{
    std::sort(std::begin(v), std::end(v));
    auto last = std::unique(std::begin(v), std::end(v));
    v.erase(last, std::end(v));
}

int main(int argc, char** argv)
{
    {
        std::ifstream fin{"bfdiff.in"};
        int n;
        fin >> n;
        da.resize(n);
        std::vector<int> px;
        std::vector<int> py;
        for (auto i = 0; i < n; i++) {
            fin >> da[i];
            px.emplace_back(da[i].x);
            py.emplace_back(da[i].y);
        }
        sort_unique(px);
        sort_unique(py);

        for (auto px1 = 0u; px1 < px.size(); px1++)
        for (auto py1 = 0u; py1 < py.size(); py1++)
            for (auto px2 = px1; px2 < px.size(); px2++)
            for (auto py2 = py1; py2 < py.size(); py2++) {
                auto lx = px[px1];
                auto ly = py[py1];
                auto rx = px[px2];
                auto ry = py[py2];

                auto count = 0;
                auto sum = 0ll;
                for (auto const& d : da) {
                    if (inrange(d.x, lx, rx) && inrange(d.y, ly, ry)) {
                        count++;
                        sum += d.value;
                    }
                }
                if (count <= 1) continue;
                ans = std::max(ans, sum);
            }
    }

    if (argc > 1)
        std::cout << ans << "\n";

    if (judge())
        std::cout << "YES\n\n";
    else
        std::cout << "NO\n\n";
}

