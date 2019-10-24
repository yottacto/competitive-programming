// ml:run = $bin < input
#include <bits/stdc++.h>

std::string s;
int n;

bool check(std::string const& s)
{
    if (n & 1)
        return false;
    auto l = 0;
    for (auto i = 0; i < n; i++)
        if (s[i] == '(')
            l++;
    return l == n - l;
}

int calc(std::string s)
{
    auto min = n;
    int p;
    auto sum = 0;
    for (auto i = 0; i < n; i++) {
        sum += (s[i] == '(') ? 1 : -1;
        if (sum < min) {
            min = sum;
            p = i;
        }
    }
    std::rotate(s.begin(), s.begin() + p + 1, s.end());
    sum = 0;
    auto res = 0;
    for (auto i = 0; i < n; i++) {
        sum += (s[i] == '(') ? 1 : -1;
        if (!sum)
            res++;
    }
    return res;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n;
    std::cin >> s;
    if (!check(s)) {
        std::cout << "0\n1 1\n";
        return 0;
    }
    auto res = calc(s);
    auto p1 = 1;
    auto p2 = 1;
    for (auto i = 0; i < n; i++) {
        for (auto j = i + 1; j < n; j++) {
            std::swap(s[i], s[j]);
            auto tmp = calc(s);
            if (tmp > res) {
                res = tmp;
                p1 = i + 1;
                p2 = j + 1;
            }
            std::swap(s[i], s[j]);
        }
    }
    std::cout << res << "\n";
    std::cout << p1 << " " << p2 << "\n";
}

