// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <unordered_map>

using ll = long long;
auto constexpr mo = 1000000000ll;

int n, m;
std::unordered_map<int, int> table;
std::vector<int> all;
int tot;

template <class T = ll>
struct matrix
{
    matrix() = default;
    matrix(int n, int m) : n(n), m(m) {}
    matrix(int n) : n(n), m(n)
    {
        for (auto i = 0; i < n; i++)
            a[i][i] = 1;
    }

    void resize(int n, int m)
    {
        this->n = n;
        this->m = m;
    }

    void print() const
    {
        std::cout << "=============\n";
        for (auto i = 0; i < n; i++) {
            for (auto j = 0; j < m; j++)
                std::cout << a[i][j] << " ";
            std::cout << "\n";
        }
    }

    T a[22][22] = {};
    int n, m;
};

template <class T>
auto operator*(matrix<T> const& lhs, matrix<T> const& rhs)
{
    matrix<T> ret(lhs.n, rhs.m);
    for (auto i = 0; i < ret.n; i++)
    for (auto j = 0; j < ret.m; j++)
        for (auto k = 0; k < lhs.m; k++) {
            ret.a[i][j] += (lhs.a[i][k] * rhs.a[k][j]) % mo;
            ret.a[i][j] %= mo;
        }
    return ret;
}

matrix<> mat;

auto brace(int x)
{
    return x == 1
        ? 1
        : x == 2 ? -1 : 0;
}

auto get(int st, int p)
{
    return (st >> (2*p)) & 3;
}

auto dir(int st, int p)
{
    auto t = get(st, p);
    return brace(t);
}

void update(int& st, int p, int v)
{
    st &= (~0) ^ (3 << (2*p));
    st |= v << (2*p);
}

auto find(int st, int p)
{
    for (auto i = p, d = 0, step = dir(st, p); ; i += step) {
        d += dir(st, i);
        if (!d) return i;
    }
    return -1;
}

auto check(int prev, int now, bool last = false)
{
    auto left = 0;
    for (auto i = 0; i < m; i++) {
        auto s = get(now, i);
        if (s == 3) return false;
        auto up = get(prev, i);

        if (!left && !up) {
            if (last || i == m - 1)
                return false;
            update(prev, i, 1);
            left = 2;
        } else if (left == up) {
            // FIXME
            if (left == 1) {
                update(prev, find(prev, i), left);
                update(prev, i, 0);
                left = 0;
            } else {
                update(prev, i, 2);
                update(prev, find(prev, i), left);
                update(prev, i, 0);
                left = 0;
            }
        } else if (left == 1 && up == 2) {
            if (!(last && i == m - 1))
                return false;
            update(prev, i, 0);
        } else if (left == 2 && up == 1) {
            update(prev, i, 0);
            left = 0;
        } else if (left) {
            if (s) {
                if (last) return false;
                update(prev, i, left);
                left = 0;
            } else {
                if (i == m - 1) return false;
                update(prev, i, 0);
            }
        } else if (up) {
            if (s) {
                if (last) return false;
            } else {
                if (i == m - 1) return false;
                left = up;
                update(prev, i, 0);
            }
        }
    }

    return now == prev;
}

void init()
{
    table[0] = tot++;
    all.emplace_back(0);
    for (auto t = 0u; t < all.size(); t++) {
        auto st = all[t];
        for (auto i = 0; i < (1<<(2*m)); i++) {
            auto a = check(st, i);
            if (!a) continue;
            if (!table.count(i)) {
                table[i] = tot++;
                all.emplace_back(i);
            }
            mat.a[table[i]][table[st]] = 1;
        }
    }
    mat.resize(tot, tot);
}

template <class Matrix>
auto quick(Matrix a, int b)
{
    Matrix ret(a.n);
    for (; b; b /= 2) {
        if (b & 1) ret = ret * a;
        a = a * a;
    }
    return ret;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> m >> n;

    init();
    auto last = mat;
    for (auto t = 0u; t < all.size(); t++) {
        auto st = all[t];
        if (!check(st, 0, true)) continue;
        last.a[table[0]][table[st]] = 1;
    }

    matrix<> value(tot, 1);
    value.a[0][0] = 1;

    value = quick(mat, n - 1) * value;
    value = last * value;
    std::cout << (2*value.a[0][0]) % mo << "\n";
}

