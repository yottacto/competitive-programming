// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <string>

auto constexpr maxn = 19700;

bool vaild[55][4][maxn];
int f[55][4][maxn];
std::pair<int, int> from[55][4][maxn];
std::string s;

auto decode(int state, int p, int ps)
{
    std::vector<int> v(4);
    for (auto i = 0; i < 3; i++, state /= 27)
        v[i] = state % 27;
    for (auto i = 3; i > p; i--)
        v[i] = v[i - 1];
    if (ps == 0)
        v[p] = 0;
    else
        v[p] = s[ps - 1] - 'a' + 1;
    return v;
}

auto encode(std::vector<int> v, int p)
{
    auto ret = 0;
    for (auto i = 3; i >= 0; i--) {
        if (i == p)
            continue;
        ret *= 27;
        ret += v[i];
    }
    return ret;
}

auto delta(int old, int now)
{
    if (!old)
        return std::string(now + 'a' - 1, '+');
    if (old < now)
        return std::string(now - old, '+');
    return std::string(old - now, '-');
}

auto restore(std::pair<int, int> pos)
{
    std::string ret;
    for (auto i = s.size(); i > 0; i--) {
        auto last = from[i][pos.first][pos.second];
        auto old_p = last.first;
        auto new_p = pos.first;
        auto v = decode(last.second, old_p, i - 1);
        std::string tmp;
        if (new_p < old_p) {
            tmp += std::string(old_p - new_p, '<');
        } else if (new_p > old_p) {
            tmp += std::string(new_p - old_p, '>');
        }
        tmp += delta(v[new_p], s[i - 1] - 'a' + 1);
        tmp += '.';
        ret = tmp + ret;
        pos = last;
    }
    return ret;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> s;
    vaild[0][0][0] = true;
    vaild[0][1][0] = true;
    for (auto i = 0u; i < s.size(); i++) {
        for (auto st = 0; st < maxn; st++) {
            for (auto old_p = 0; old_p < 4; old_p++) {
                if (!vaild[i][old_p][st])
                    continue;
                auto v = decode(st, old_p, i);
                for (auto new_p = 0; new_p < 4; new_p++) {
                    auto tmp = f[i][old_p][st];
                    if (new_p < old_p) {
                        tmp += old_p - new_p;
                    } else if (new_p > old_p) {
                        tmp += new_p - old_p;
                    }
                    tmp += delta(v[new_p], s[i] - 'a' + 1).size();
                    tmp++;
                    auto tst = encode(v, new_p);
                    if (!vaild[i + 1][new_p][tst]) {
                        vaild[i + 1][new_p][tst] = true;
                        f[i + 1][new_p][tst] = tmp;
                        from[i + 1][new_p][tst] = {old_p, st};
                    } else if (f[i + 1][new_p][tst] > tmp) {
                        f[i + 1][new_p][tst] = tmp;
                        from[i + 1][new_p][tst] = {old_p, st};
                    }

                }
            }
        }
    }

    auto ans = 2000;
    std::pair<int, int> pos;
    for (auto st = 0; st < maxn; st++)
        for (auto p = 0; p < 4; p++)
            if (vaild[s.size()][p][st] && ans > f[s.size()][p][st]) {
                ans = f[s.size()][p][st];
                pos = {p, st};
            }

    auto p = restore(pos);
    std::cout << p << "\n";
    // std::cout << p.size() << "\n";
    // std::cout << ans << "\n";
}

