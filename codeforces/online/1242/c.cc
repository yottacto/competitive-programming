// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;

int k;
std::vector<std::vector<ll>> a;
std::vector<ll> sums;
std::unordered_map<int, int> pos;
ll avg;

struct data
{
    ll x;
    int id;
};

std::unordered_set<int> vis;
std::vector<std::vector<data>> circles;
std::vector<int> states;

void no_solution()
{
    std::cout << "no\n";
    exit(0);
}

void get_circle(int i, ll out)
{
    std::vector<data> circle;
    auto ti = i;
    auto cur = out;
    auto st = 0;
    do {
        auto next = avg - (sums[ti] - cur);
        if (std::abs(next) >= 1000000000ll)
            return;
        if (!pos.count(next) || (st & (1<<pos.at(next))))
            return;
        ti = pos.at(next);
        st |= 1 << ti;
        cur = next;
        circle.emplace_back(data{cur, ti});
    } while (ti != i);
    if (cur != out)
        return;

    states.emplace_back(st);
    circles.emplace_back(circle);
    for (auto const& d : circle)
        vis.emplace(d.x);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> k;
    a.resize(k);
    sums.resize(k);
    auto sum = 0ll;
    for (auto i = 0; i < k; i++) {
        int ni;
        std::cin >> ni;
        a[i].resize(ni);
        for (auto j = 0; j < ni; j++) {
            std::cin >> a[i][j];
            sum += a[i][j];
            sums[i] += a[i][j];
            pos[a[i][j]] = i;
        }
    }

    if (sum % k)
        no_solution();

    avg = sum / k;

    for (auto i = 0; i < k; i++) {
        for (auto out : a[i]) {
            if (vis.count(out))
                continue;
            get_circle(i, out);
        }
    }

    auto maxs = 1<<k;
    std::unordered_map<int, int> all;
    for (auto i = 0u; i < states.size(); i++)
        all[states[i]] = i;

    std::vector<char> f(maxs);
    std::vector<int> jump(maxs);
    f[0] = true;
    for (auto st = 0; st < maxs; st++) {
        for (auto sub_st = st; sub_st; sub_st = (sub_st - 1) & st) {
            if (!all.count(sub_st))
                continue;
            auto i = all[sub_st];
            if (f[st ^ states[i]]) {
                f[st] = true;
                jump[st] = i;
                break;
            }
        }
    }

    if (!f[maxs - 1])
        no_solution();
    std::cout << "yes\n";

    std::vector<int> choose(k);
    std::vector<int> to(k);

    auto st = maxs - 1;
    for (; st; ) {
        auto tn = jump[st];
        auto const& c = circles[tn];
        int m = c.size();
        for (auto i = 1; i < m; i++) {
            choose[c[i].id] = c[i].x;
            to[c[i].id] = c[i - 1].id;
        }
        choose[c[0].id] = c[0].x;
        to[c[0].id] = c[m - 1].id;
        st ^= states[tn];
    }

    for (auto i = 0; i < k; i++)
        std::cout << choose[i] << " " << to[i] + 1 << "\n";
}

