// ml:run = $bin < input
#include <bits/stdc++.h>

std::vector<int> a;
std::vector<int> ua;
int n;

int p, q;
int max;

std::unordered_map<int, int> count;

void fill(int r, int c)
{
    for (auto& p : count)
        p.second = std::min(r, p.second);
    std::vector<int> b;
    b.resize(r * c);
    int t = ua.size() - 1;
    for (auto i = 0; i < c; i++)
        for (auto j = 0; j < r; j++) {
            if (!count[ua[t]])
                t--;
            b[j * c + ((i + j) % c)] = ua[t];
            count[ua[t]]--;
        }
    for (auto i = 0; i < p; i++) {
        for (auto j = 0; j < q; j++)
            std::cout << b[i * c + j] << " ";
        std::cout << "\n";
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n;
    a.resize(n);
    for (auto i = 0; i < n; i++)
        std::cin >> a[i];

    for (auto i : a)
        count[i]++;

    // r for rows
    ua = a;
    std::sort(ua.begin(), ua.end(), [&](auto const& a, auto const& b) {
        return count[a] < count[b]
            || (count[a] == count[b] && a > b);
    });
    ua.erase(std::unique(ua.begin(), ua.end()), ua.end());

    auto j = 0;
    auto sum = 0;
    int tn = ua.size();
    for (auto r = 1; r * r <= n; r++) {
        while (j < tn && count[ua[j]] < r)
            j++;
        sum += tn - j;
        auto c = std::max(r, sum / r);
        if (sum >= r * c && r * c >= max) {
            max = r * c;
            p = r;
            q = c;
        }
    }
    std::cout << max << "\n";
    std::cout << p << " " << q << "\n";
    fill(p, q);
}

