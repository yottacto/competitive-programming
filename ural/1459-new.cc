#include <iostream>
#include <iomanip>
#include <bitset>
#include <vector>
#include <unordered_map>

#define M 3

int n, m;
std::unordered_map<int, int> table;
std::vector<int> all;
int tot;

struct matrix
{
    matrix() = default;
    matrix(int n, int m) : n(n), m(m) {}

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

    int a[50][50] = {};
    int n, m;
};

auto operator*(matrix const& lhs, matrix const& rhs)
{
    matrix ret(lhs.n, rhs.m);
    for (auto i = 0; i < ret.n; i++)
    for (auto j = 0; j < ret.m; j++)
        for (auto k = 0; k < lhs.m; k++)
            ret.a[i][j] += lhs.a[i][k] * rhs.a[k][j];
    return ret;
}

matrix mat;

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
    return t == 1
        ? 1
        : t == 2 ? -1 : 0;
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
    // 0, 1: (, 2: ), 3: up (, 4: up )
    auto kind = 0;
    auto to_match = 0;
    for (auto i = 0; i < m; i++) {
        auto s = (now >> (2*i)) & 3;
        if (s == 3) return false;
        auto up = (prev >> (2*i)) & 3;
        to_match += brace(s);
        if (to_match < 0) return false;

        std::cout << i << " now = " << s << " up = " << up << " left = " << left << " kind = " << kind << "\n";

        if (!up) {
            if (!s) {
                if (!left || i == m - 1) return false;
            } else {
                if (!left)
                    kind = 1;
                else {
                    if (kind == 1)
                        kind = 2;
                    else if (kind == 2)
                        kind = 0;
                }
                if (s != kind && s != kind -2)
                    return false;
                left ^= 1;
            }
        } else {
            if (!s) {
                if (!left)
                    kind = up + 2;
                else {
                    // FIXME
                    if (kind == 3 && up == 2) {
                        if (!(last && i == m - 1))
                            return false;
                    }
                }
                left ^= 1;
            } else {
                if (left) return false;
            }
        }
    }
    if (to_match != 0) return false;
    return true;
}

void print(int x)
{
    std::cout << x << ": ";
    std::string s;
    for (auto i = 0; i < M; i++, x /= 4)
        s += char('0' + (x%4));
    std::cout << s << "\n";
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
    std::cerr << "table size: " << table.size() << "\n";
    mat.print();

    print(all[0]);
    print(all[1]);
    print(all[2]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    // std::cin >> m >> n;

    n = 4;
    m = M;
    std::cout << check(33, 9, false) << "\n"; return 0;

    init();
    matrix value(tot, 1);
    value.a[0][0] = 1;
    for (auto i = 0; i < n-1; i++) {
        value = mat * value;
        value.print();
        // std::cout << "\n";
    }

    for (auto t = 0u; t < all.size(); t++) {
        auto st = all[t];
        if (!check(st, 0, true)) continue;
        mat.a[table[0]][table[st]] = 1;
    }
    mat.print();
    value = mat * value;
    value.print();

    std::cout << "\n";
    std::cout << value.a[0][0]*2 << "\n";
    // mat.print();
}

