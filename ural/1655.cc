// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <iterator>
#include <tuple>
#include <initializer_list>
#include <algorithm>
#include <utility>
#include <vector>
#include <cmath>

struct data
{
    double b, d, v;
    double remain;
    int id;
};

auto& operator>>(std::istream& is, data& d)
{
    is >> d.b >> d.d >> d.v;
    d.v /= 60.;
    d.remain = std::max(0., (d.d - 1.)) / d.v;
    return is;
}

auto constexpr  eps = 1e-6;
auto constexpr  inf = 1e20;
auto constexpr maxn = 600;
double a, w;
int n, p;
bool aimed;
std::vector<data> da;

struct path_type
{
    int last;
    int end;
    int choose;
};

double f[maxn][maxn][2];
path_type from[maxn][maxn][2];

template <class T>
T abs(T x)
{
    return x < 0 ? -x : x;
}

auto equal(double x, double y)
{
    return abs(x - y) < eps;
}

auto less(double x, double y)
{
    return x + eps < y;
}

auto greater(double x, double y)
{
    return less(y, x);
}

auto prev(int p, int x = 1)
{
    p -= x;
    if (p < 0) p += n;
    return p;
}

auto next(int p, int x = 1)
{
    p += x;
    if (p >= n) p -= n;
    return p;
}

auto calc(int from, int to, int dir) -> double
{
    if (dir < 0) return calc(to, from, 1);
    auto a1 = da[from].b;
    auto a2 = da[to].b;
    auto d = a2 - a1;
    if (less(d, 0.)) d += 360;
    return d / w;
}

template <class T, class Path_type>
void update(T& f, Path_type& from, std::initializer_list<std::tuple<T, Path_type, T>> l)
{
    for (auto const& i : l) {
        if (less(da[std::get<1>(i).choose].remain, std::get<2>(i)))
                continue;
        if (greater(f, std::get<0>(i))) {
            f = std::get<0>(i);
            from = std::get<1>(i);
        }
    }
}

void print(path_type pos)
{
    std::vector<int> id;
    for (auto i = n; i > 1; i--) {
        id.emplace_back(da[pos.choose].id);
        pos = from[pos.last][i - 1][pos.end];
    }
    if (aimed) id.emplace_back(da[p].id);
    for (auto it = std::rbegin(id); it != rend(id); ++it)
        std::cout << *it << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> a >> w >> n;
    w *= 360;
    da.resize(n);
    for (auto i = 0; i < n; i++) {
        std::cin >> da[i];
        da[i].id = i + 1;
        if (equal(da[i].b, a))
            aimed = true;
    }

    if (!aimed) {
        da.emplace_back(data{a, 1000, 0.01, 0, -1});
        n++;
    }

    std::sort(std::begin(da), std::end(da), [](data const& lhs, data const& rhs) {
        return less(lhs.b, rhs.b);
    });

    p = std::find_if(std::begin(da), std::end(da), [&](data const& x){
        return equal(x.b, a);
    }) - std::begin(da);

    std::fill(&f[0][0][0], &f[0][0][0] + sizeof(f) / sizeof(f[0][0][0]), inf);

    f[p][1][0] = f[p][1][1] = 0;
    for (auto l = 2; l <= n; l++) {
        for (auto c = 0; c < l; c++) {
            auto i = prev(p, l-1-c);
            auto r = next(i, l-1);
            // f[][][0]
            update(f[i][l][0], from[i][l][0], {
                {f[next(i)][l-1][0] + calc(next(i), i, -1),                path_type{next(i), 0, i}, f[next(i)][l-1][0] + calc(next(i), i, -1)},
                {f[next(i)][l-1][1] + calc(r, i, -1),                      path_type{next(i), 1, i}, f[next(i)][l-1][1] + calc(r, i, -1)},
                {f[i][l-1][0]       + 2 * calc(i, r, 1),                   path_type{i, 0, r},       f[i][l-1][0] + calc(i, r, 1)},
                {f[i][l-1][1]       + calc(i, r, 1) + calc(prev(r), r, 1), path_type{i, 1, r},       f[i][l-1][1] + calc(prev(r), r, 1)}
            });

            // f[][][1]
            update(f[i][l][1], from[i][l][1], {
                {f[next(i)][l-1][0] + calc(i, r, 1) + calc(next(i), i, -1), path_type{next(i), 0, i}, f[next(i)][l-1][0] + calc(next(i), i, -1)},
                {f[next(i)][l-1][1] + 2 * calc(i, r, 1),                    path_type{next(i), 1, i}, f[next(i)][l-1][1] + calc(i, r, 1)},
                {f[i][l-1][0]       + calc(i, r, 1),                        path_type{i, 0, r},       f[i][l-1][0] + calc(i, r, 1)},
                {f[i][l-1][1]       + calc(prev(r), r, 1),                  path_type{i, 1, r},       f[i][l-1][1] + calc(prev(r), r, 1)}
            });
        }
    }

    auto ans = inf;
    path_type pos;
    for (auto i = 0; i < n; i++)
        for (auto j = 0; j < 2; j++)
            if (greater(ans, f[i][n][j])) {
                ans = f[i][n][j];
                pos = from[i][n][j];
            }

    if (!less(ans, inf)) {
        std::cout << "Impossible\n";
        return 0;
    }
    std::cout << std::fixed << std::setprecision(3) << ans << "\n";
    print(pos);
}

