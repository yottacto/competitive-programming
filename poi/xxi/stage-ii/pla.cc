// ml:run = $bin < input
#include <cstdio>
#include <deque>

auto constexpr maxn = 1000007;
int a[maxn];
int f[maxn];
int n, q;

auto dp(int k)
{
    f[1] = 0;
    std::deque<int> dq;
    dq.emplace_back(1);
    for (auto i = 2; i <= n; i++) {
        while (!dq.empty() && dq.front() < i - k)
            dq.pop_front();
        f[i] = f[dq.front()] + (a[dq.front()] <= a[i]);
        while (!dq.empty() && (
            f[i] < f[dq.back()] || (f[i] == f[dq.back()] && a[i] >= a[dq.back()])
        ))
            dq.pop_back();
        dq.emplace_back(i);
    }
    return f[n];
}

int main()
{
    std::scanf("%d", &n);
    for (auto i = 1; i <= n; i++)
        std::scanf("%d", &a[i]);
    std::scanf("%d", &q);
    for (auto i = 0; i < q; i++) {
        int k;
        std::scanf("%d", &k);
        std::printf("%d\n", dp(k));
    }
}

