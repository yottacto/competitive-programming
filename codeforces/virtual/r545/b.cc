// ml:run = $bin < input
#include <iostream>
#include <string>

auto constexpr maxn = 500007;
int next[maxn];
std::string s;
std::string t;
int count0;
int count1;

void get_next(std::string const& s)
{
    int k = -1, j = 0, len2 = s.size();
    next[0] = -1;
    while (j < len2) {
        if (k == -1 || s[j] == s[k])
            next[++j] = ++k;
        else
            k = next[k];
    }
}

auto not_enough(int c0, int c1)
{
    return (c0 > count0 || c1 > count1);
}

auto use(int c0, int c1)
{
    count0 -= c0;
    count1 -= c1;
    return std::string(c0, '0') + std::string(c1, '1');
}

auto work()
{
    get_next(t);
    auto countt0 = 0;
    auto countt1 = 0;
    for (auto ch : t)
        if (ch == '0')
            countt0++;
        else
            countt1++;
    if (not_enough(countt0, countt1))
        return use(count0, count1);
    auto res = t;
    count0 -= countt0;
    count1 -= countt1;
    auto extend0 = 0;
    auto extend1 = 0;
    int len = t.size();
    for (auto i = next[len]; i < len; i++)
        if (t[i] == '0')
            extend0++;
        else
            extend1++;
    // std::cerr << next[len] << " " << extend0 << " " << extend1 << " " << count0 << " " << count1 << "~\n";
    while (!not_enough(extend0, extend1)) {
        res += t.substr(next[len]);
        // std::cerr << ":: " << t.substr(next[len]) << "\n";
        count0 -= extend0;
        count1 -= extend1;
    }
    return res + use(count0, count1);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> s >> t;
    for (auto ch : s)
        if (ch == '0')
            count0++;
        else
            count1++;

    std::cout << work() << "\n";
}

