// ml:run = $bin < input
#include <iostream>
#include <string>

bool cannot[30];
bool vis[30];
std::string s;
int n;

void clear()
{
    for (int i = 0; i < 26; i++)
        vis[i] = false;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    auto determined = false;
    auto ans = 0;
    auto tot = 26;
    for (int i = 0; i < n - 1; i++) {
        char ch; std::cin >> ch >> s;
        if (ch == '.') {
            for (auto ch : s) {
                auto j = ch - 'a';
                if (cannot[j]) continue;
                cannot[j] = true;
                tot--;
            }
            if (tot == 1) determined = true;
        } else if (ch == '!') {
            if (determined) ans++;
            clear();
            for (auto ch : s) vis[ch - 'a'] = true;
            for (auto j = 0; j < 26; j++) {
                if (vis[j] || cannot[j]) continue;
                cannot[j] = true;
                tot--;
            }
            if (tot == 1) determined = true;
        } else {
            if (determined) ans++;
            if (cannot[s[0] - 'a']) continue;
            cannot[s[0] - 'a'] = true;
            tot--;
            if (tot == 1) determined = true;
        }
    }
    std::cout << ans << "\n";
}

