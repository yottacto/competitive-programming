// ml:run = $bin < input
#include <iostream>
#include <string>
#include <unordered_map>

auto constexpr maxn = 1000007;
int end[maxn];
int equal[maxn];
int sum[maxn];
std::unordered_map<int, int> last;
int n;
std::string s;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> s;
    for (auto i = 1; i <= n; i++)
        sum[i] = sum[i - 1] + (s[i-1] == 'p' ? +1 : -1);

    for (auto i = n; i >= 0; i--) {
        if (!last.count(sum[i])) {
            equal[i] = n + 1;
        } else {
            equal[i] = last[sum[i]];
        }
        last[sum[i]] = i;
    }

    end[n] = n;
    for (auto i = n - 1; i >= 0; i--) {
        if (s[i] == 'j') {
            end[i] = i;
        } else if (i == n - 1) {
            end[i] = i + 1;
        } else if (equal[i] == n + 1) {
            end[i] = end[i + 1];
        } else {
            auto a = end[i+1];
            auto b = end[equal[i]];
            auto less = [](int a, int b) {
                return sum[a] < sum[b]
                    || (sum[a] == sum[b] && a < b);
            };
            end[i] = less(a, b) ? b : a;
        }
    }
    auto ans = 0;
    for (auto i = n; i >= 1; i--) {
        if (s[i - 1] == 'j')
            continue;
        ans = std::max(ans, end[i-1] - i + 1);
    }
    std::cout << ans << "\n";

    // for (auto i = 1; i <= n; i++)
    //     std::cout << sum[i] << " ";
    // std::cout << "\n";

    // for (auto i = 1; i <= n; i++)
    //     std::cout << equal[i] << " ";
    // std::cout << "\n";

    // for (auto i = 1; i <= n; i++)
    //     std::cout << end[i] << " ";
    // std::cout << "\n";
}

