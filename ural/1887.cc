// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <vector>

auto constexpr maxn = 30;
auto constexpr eps  = 1e-8;

int a[maxn];
int b[maxn];
int c[maxn];
double psum[maxn][12];
double p[12];
double f[2000];
int n;

template <class T>
T abs(T x)
{
    return x < 0 ? -x : x;
}

auto equal(double lhs, double rhs)
{
    return abs(rhs - lhs) < eps;
}

void input(int a[])
{
    for (auto i = 1; i <= n; i++)
        std::cin >> a[i];
}

auto dp(int state)
{
    if (state == 1023) return 0.;
    if (f[state] > eps)
        return f[state];
    auto pstay = 0.;
    for (auto i = 0; i < 10; i++) {
        if (state & (1 << i)) {
            pstay += p[i];
            continue;
        }
        f[state] += (dp(state ^ (1 << i)) + 1.) * p[i];
    }
    f[state] = (f[state] + pstay) / (1. - pstay);
    return f[state];
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;

    input(a);
    input(b);
    input(c);

    for (auto i = 1; i <= n; i++) {
        std::vector<double> count(11);
        for (auto j = 0; j < 10; j++)
            count[(a[i] * j * j + b[i] * j + c[i]) % 11]++;

        if (i == 1) {
            for (auto j = 0; j < 11; j++)
                psum[i][j] = count[j] / 10.;
            continue;
        }

        for (auto prev = 0; prev < 11; prev++)
            for (auto now = 0; now < 11; now++) {
                psum[i][(prev * now) % 11] +=
                    psum[i - 1][prev] * count[now] / 10.;
            }
    }

    for (auto i = 0; i < 11; i++)
        p[i % 10] += psum[n][i];

    // auto sum = 0.;
    // for (auto i = 0; i < 10; i++) {
    //     sum += p[i];
    //     std::cout << p[i] << " ";
    // }
    // std::cout << "\n";
    // std::cout << sum << "\n";

    for (auto i = 0; i < 10; i++)
        if (equal(p[i], 0)) {
            std::cout << "-1\n";
            return 0;
        }

    std::cout << std::fixed << std::setprecision(10)
        << dp(0) << "\n";
}

