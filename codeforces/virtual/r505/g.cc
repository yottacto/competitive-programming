// ml:run = $bin < input
#include <iostream>
#include <vector>

using ll = long long;

static auto constexpr maxn = 600;
static auto constexpr mo = 1000000007ll;

int a[maxn];
int count[maxn];
ll pow2[maxn];
int n;

ll mul(ll lhs, ll rhs)
{
    return (lhs * rhs) % mo;
}

ll add(ll lhs, ll rhs)
{
    return (lhs + rhs) % mo;
}

void init()
{
    pow2[0] = 1;
    for (auto i = 1; i < maxn; i++)
        pow2[i] = mul(pow2[i - 1],  2);
}

int main()
{
    std::ios::sync_with_stdio(false);
    init();

    std::cin >> n;
    for (auto i = 1; i <= n; i++) {
        std::cin >> a[i];
        if (a[i] == -1) continue;
        count[a[i]]++;
    }
    auto sum = 0ll;
    for (auto i = 1; i <= n; i++)
        sum = add(sum, pow2[count[i]] - 1);

    auto ans = (pow2[n - 1] - 1 - sum) % mo;
    ans = (ans + mo) % mo;

    std::cout << ans << "\n";
}

