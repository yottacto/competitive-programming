// ml:run = $bin < input
#include <iostream>
#include <algorithm>

using ll = long long;

static auto constexpr maxn = 3 * 50;
static auto constexpr maxl = 70;

struct matrix
{
    int n;
    ll a[maxn][maxn] = {};
};

std::ostream& operator<<(std::ostream& os, matrix const& mat)
{
    os << mat.n << " * " << mat.n << "\n";
    for (auto i = 0; i < mat.n; i++) {
        for (auto j = 0; j < mat.n; j++)
            os << mat.a[i][j] << " ";
        os << "\n";
    }
    return os;
}

auto add(ll lhs, ll rhs)
{
    if (lhs < 0 || rhs < 0)
        return -1ll;
    return lhs + rhs;
}

auto mul(ll lhs, ll rhs)
{
    if (lhs < 0 || rhs < 0)
        return -1ll;
    return lhs * rhs;
}

auto operator*(matrix const& a, matrix const& b) -> matrix
{
    matrix res = a;
    auto tn = a.n;
    for (auto i = 0; i < tn; i++)
        for (auto j = 0; j < tn; j++) {
            res.a[i][j] = 0;
            for (auto k = 0; k < tn; k++)
                res.a[i][j] = add(res.a[i][j], mul(a.a[i][k], b.a[k][j]));
        }
    return res;
}

matrix a;

int n, m;
int s;
ll k;

void add_edge(int u, int v)
{
    a.a[u][v]++;
}

matrix res[maxl];

auto count(matrix const& mat)
{
    auto sum = 0ll;
    auto tmp = mat * a;
    for (auto i = 1; i <= n; i++)
        sum = add(sum, tmp.a[s][3 * i] - 1);
    return sum;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m >> k;
    s = 0;
    a.n = 3 * n + 1;
    for (auto i = 1; i <= n; i++) {
        add_edge(3 * i - 2, 3 * i - 1);
        add_edge(3 * i - 1, 3 * i);
        add_edge(s, 3 * i);
    }

    for (auto i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        add_edge(3 * u, 3 * v - w + 1);
    }

    add_edge(s, s);

    res[0] = a;
    auto i = 0;
    if (count(res[i]) < k)  {
        for (i++; i < maxl; i++) {
            res[i] = res[i - 1] * res[i - 1];
            auto tmp = count(res[i]);
            // std::cerr << i << " : " << tmp << "\n";
            if (tmp < 0 || tmp >= k)
                break;
        }
    }

    // std::cerr << "========================================\n";
    // std::cerr << a << "\n";

    if (i == maxl) {
        std::cout << "-1\n";
        return 0;
    }

    if (i == 0) {
        std::cout << "1\n";
        return 0;
    }

    auto len = (1ll)<<(i-1);
    auto ans = res[i - 1];
    for (auto j = i - 2; j >= 0; j--) {
        auto tmp = ans * res[j];
        auto c = count(tmp);
        if (c >= 0 && c < k) {
            ans = tmp;
            len += (1ll) << j;
        }
    }
    std::cout << len + 1 << "\n";
}

