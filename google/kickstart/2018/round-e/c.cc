// ml:run = $bin < C-small-attempt0.in > c-small-0.out
// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <iterator>
#include <numeric>
#include <algorithm>
#include <utility>
#include <vector>
#include <queue>
#include <string>

auto constexpr maxn = 30;
int a[maxn];
int b[maxn];
int id[maxn];
bool vis[maxn];
int record[maxn];
int sum[3];
int n;

int id2[maxn];
bool vis2[maxn];
int record2[maxn];
int sum2[3];
int suma;
int sumb;

double ans = 0;
int tot = 0;

auto frac(int n)
{
    auto res = 1;
    for (auto i = 1; i <= n; i++)
        res *= i;
    return res;
}

void dfs2(int start, int depth)
{
    int* tid;
    bool* tvis;
    if (depth == n + 1) {
        tid = new int[3*n+1];
        tvis = new bool[3*n+1];
        for (auto i = 1; i <= 3 * n; i++) {
            tid[i] = id2[i];
            tvis[i] = vis2[i];
        }
        auto len = 1;
        for (auto i = 1; i <= 3 * n; i++)
            if (vis2[i]) {
                std::swap(id2[len], id2[i]);
                std::swap(vis2[len], vis2[i]);
                len++;
            }
        start = n + 1;
    }
    if (depth == 2 * n + 1) {
        sum2[0] = sum2[1] = sum2[2] = 0;
        for (auto i = 0; i < 2; i++) {
            for (auto j = 1; j <= n; j++)
                sum2[i] += b[record2[j + i * n]];
        }
        sum2[2] = sumb - sum2[0] - sum2[1];
        auto count = 0;
        for (auto i = 0; i < 3; i++)
            if (sum[i] > sum2[i])
                count++;
        if (count >= 2)
            tot += frac(n) * frac(n) * frac(n);
        return;
    }
    for (auto i = start; i <= 3 * n; i++) {
        vis2[i] = true;
        record2[depth] = id2[i];
        dfs2(i + 1, depth + 1);
        vis2[i] = false;
    }
    if (depth == n + 1) {
        for (auto i = 1; i <= 3 * n; i++) {
            id2[i] = tid[i];
            vis2[i] = tvis[i];
        }
        delete[] tid;
        delete[] tvis;
    }
}


auto calc() -> double
{
    std::iota(id2, id2 + 3 * n + 1, 0);
    std::fill(vis2, vis2 + 3 * n + 1, false);
    tot = 0;
    dfs2(1, 1);
    return (double)tot / frac(3*n);
}

void dfs(int start, int depth)
{
    int* tid;
    bool* tvis;
    if (depth == n + 1) {
        tid = new int[3*n+1];
        tvis = new bool[3*n+1];
        for (auto i = 1; i <= 3 * n; i++) {
            tid[i] = id[i];
            tvis[i] = vis[i];
        }
        auto len = 1;
        for (auto i = 1; i <= 3 * n; i++)
            if (vis[i]) {
                std::swap(id[len], id[i]);
                std::swap(vis[len], vis[i]);
                len++;
            }
        start = n + 1;
    }
    if (depth == 2 * n + 1) {
        sum[0] = sum[1] = sum[2] = 0;
        for (auto i = 0; i < 2; i++)
            for (auto j = 1; j <= n; j++)
                sum[i] += a[record[j + i * n]];
        sum[2] = suma - sum[0] - sum[1];
        ans = std::max(ans, calc());
        return;
    }
    for (auto i = start; i <= 3 * n; i++) {
        vis[i] = true;
        record[depth] = id[i];
        dfs(i + 1, depth + 1);
        vis[i] = false;
    }
    if (depth == n + 1) {
        for (auto i = 1; i <= 3 * n; i++) {
            id[i] = tid[i];
            vis[i] = tvis[i];
        }
        delete[] tid;
        delete[] tvis;
    }
}

void init()
{
    ans = 0;
    std::iota(id, id + 3 * n + 1, 0);
    std::fill(vis, vis + 3 * n + 1, false);
}

int main()
{
    std::ios::sync_with_stdio(false);
    int T; std::cin >> T;
    for (auto ti = 1; ti <= T; ti++) {
        std::cout << "Case #" << ti << ": ";
        std::cin >> n;
        suma = sumb = 0;
        for (auto i = 1; i <= 3 * n; i++) {
            std::cin >> a[i];
            suma += a[i];
        }
        for (auto i = 1; i <= 3 * n; i++) {
            std::cin >> b[i];
            sumb += b[i];
        }

        init();
        dfs(1, 1);
        std::cout << std::fixed << std::setprecision(9) << ans << "\n";
    }
}

