// ml:run = $bin < input
#include <bits/stdc++.h>

int n, k;
std::string s;
// left, right
int pos[2];
char ch[2] = {'(', ')'};

void find(int b, int p)
{
    while (pos[b] < n && s[pos[b]] == ch[!b])
        pos[b]++;
    std::cout << p + 1 << " " << pos[b] + 1 << "\n";
    std::swap(s[pos[b]], s[p]);
    pos[b]++;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> n >> k;
        std::cin >> s;
        std::cout << n << "\n";
        pos[0] = pos[1] = 0;
        for (auto i = 0; i < k - 1; i++) {
            find(0, 2 * i);
            find(1, 2 * i + 1);
        }
        auto r = n - (k - 1) * 2;
        for (auto i = 0; i < r/2; i++)
            find(0, 2 * (k - 1) + i);
        for (auto i = 0; i < r/2; i++)
            find(1, 2 * (k - 1) + r/2 + i);
    }
}

