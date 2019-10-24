// ml:run = $bin < input
#include <bits/stdc++.h>

using ll = long long;

int n;
ll s;
std::vector<ll> l;
std::vector<ll> r;

bool judge(ll mid)
{
    auto sum = 0ll;
    auto count_less = 0;
    auto count_greater = 0;
    for (auto i = 0; i < n; i++)
        if (r[i] < mid) {
            count_less++;
            sum += l[i];
        }
    for (auto i = 0; i < n; i++)
        if (l[i] > mid) {
            count_greater++;
            sum += l[i];
        }
    if (count_less > n/2 || count_greater > n/2)
        return false;
    std::vector<ll> tmpl;
    for (auto i = 0; i < n; i++)
        if (l[i] <= mid && mid <= r[i]) {
            tmpl.emplace_back(l[i]);
        }
    std::sort(tmpl.begin(), tmpl.end());
    for (auto i = 0; i < n/2 - count_less; i++)
        sum += tmpl[i];
    sum += (n/2 - count_greater + 1) * mid;
    return sum <= s;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n >> s;
        l.clear();
        r.clear();
        l.resize(n);
        r.resize(n);
        ll maxr{0};
        for (auto i = 0; i < n; i++) {
            std::cin >> l[i] >> r[i];
            maxr = std::max(maxr, r[i]);
        }

        auto tmpl = l;
        std::sort(tmpl.begin(), tmpl.end());

        ll tl{tmpl[n / 2]};
        ll tr{maxr};
        while (tl + 1 < tr) {
            auto mid = (tl + tr) / 2;
            if (judge(mid))
                tl = mid;
            else
                tr = mid;
        }
        if (judge(tr))
            tl = tr;
        std::cout << tl << "\n";
    }
}

