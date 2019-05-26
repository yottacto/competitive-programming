// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

using ll = long long;
ll n;

auto get_v(ll n)
{
    std::vector<int> v;
    for (; n; n /= 10)
        v.emplace_back(n % 10);
    return v;
}

template <class Vec>
auto add(Vec v)
{
    int n = v.size();
    auto i = n - 1;
    for (; i >= 0; i--)
        if (v[i] & 1)
            break;
    if (i < 0)
        return v;
    v[i]++;
    for (auto j = 0; j < i; j++)
        v[j] = 0;
    for (auto j = i; j < n; j++) {
        if (v[j] & 1)
            v[j]++;
        if (v[i] == 10) {
            v[j] = 0;
            if (j == n - 1) {
                v.emplace_back(0);
                n++;
            }
            v[j + 1]++;
        }
    }
    return v;
}

template <class Vec>
auto sub(Vec v)
{
    int n = v.size();
    auto i = n - 1;
    for (; i >= 0; i--)
        if (v[i] & 1)
            break;
    if (i < 0)
        return v;
    v[i]--;
    for (auto j = 0; j < i; j++)
        v[j] = 8;
    return v;
}

template <class Vec>
auto v_to_integer(Vec const& v)
{
    auto res = ll{};
    int n = v.size();
    for (auto i = n - 1; i >= 0; i--)
        res = res * 10 + v[i];
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T;
    std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n;
        auto v = get_v(n);
        auto nadd = v_to_integer(add(v));
        auto nsub = v_to_integer(sub(v));
        // std::cout << nadd << " " << nsub << " ";
        std::cout << std::min(nadd - n, n - nsub) << "\n";
    }
}

