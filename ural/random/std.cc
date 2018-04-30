// ml:run = cp $bin std
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <string>

using ll = long long;

int n, k;
std::string s;

auto check(int l, int r)
{
    auto len = r - l + 1;
    for (auto i = 0; i < len; i++)
        if (s[l + i] != s[r - i])
            return false;
    return true;
}

auto query(ll l, ll r)
{
    auto count = 0ll;
    for (auto i = l; i <= r; i++)
        for (auto j = i; j <= r; j++) {
            if (j - i + 1 > k)
                continue;
            count += check(i - 1, j - 1);
        }
    return count;
}

void cover(int l, int r, char ch)
{
    for (auto i = l; i <= r; i++)
        s[i - 1] = ch;
}

int main()
{
    std::ios::sync_with_stdio(false);

    std::cin >> s >> k;
    n = s.size();

    int q;
    std::cin >> q;
    while (q--) {
        int id, l, r;
        std::cin >> id >> l >> r;
        if (id == 2) {
            std::cout << query(l, r) << "\n";
        } else {
            char ch;
            std::cin >> ch;
            cover(l, r, ch);
        }
    }
}

