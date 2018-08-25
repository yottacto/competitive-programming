// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <vector>
#include <stack>

auto constexpr inf = 1<<30;
auto constexpr maxn = 200007;
int a[maxn];
bool vis[maxn];
int change_color[maxn];
int last_pos[maxn];
int st[maxn][30];
int n, q;
bool last;

auto first_non_zero()
{
    for (auto i = 1; i <= n; i++)
        if (a[i]) return a[i];
    return q;
}

auto first_zero_pos()
{
    for (auto i = 1; i <= n; i++)
        if (!a[i]) return i;
    return -1;
}

void apply_color()
{
    std::stack<int> st;
    for (auto i = 1; i <= n; i++) {
        if (!a[i]) {
            if (!st.empty()) a[i] = st.top();
        } else {
            if (change_color[i] > 0)
                st.push(change_color[i]);
            else if (change_color[i] < 0)
                st.pop();
        }
    }
}

auto log2(int len)
{
    int tmp = 0;
    for (; (1 << tmp) <= len; tmp++);
    return tmp - 1;
}

auto find_min(int l, int r)
{
    int k = log2(r - l + 1);
    if (st[l][k] < st[r - (1<<k) + 1][k])
        return st[l][k];
    else
        return st[r - (1<<k) + 1][k];
}

void init_st()
{
    int len = log2(n);
    for (int i = 1; i <= n; i++) st[i][0] = a[i] ? a[i] : inf;
    for (int l = 1; l <= len; l++)
        for (int i = 1; (i + (1<<l) - 1) <= n; i++)
            if (st[i][l - 1] < st[i + (1<<(l-1))][l - 1])
                st[i][l] = st[i][l - 1];
            else
                st[i][l] = st[i + (1 << (l-1))][l - 1];
}

void work()
{
    if (!last) {
        auto p = first_zero_pos();
        if (p == -1) {
            std::cout << "NO\n";
            return;
        }
        a[p] = q;
        last_pos[q] = p;
    }

    vis[0] = true;
    for (auto i = 1; i <= n; i++) {
        if (vis[a[i]]) continue;
        auto min = find_min(i, last_pos[a[i]]);
        if (a[i] > min) {
            std::cout << "NO\n";
            return;
        }
        change_color[i] += a[i];
        change_color[last_pos[a[i]]] += -a[i];
        vis[a[i]] = true;
    }

    apply_color();

    if (!a[1]) a[0] = first_non_zero();
    for (auto i = 1; i <= n; i++)
        if (!a[i]) a[i] = a[i - 1];

    std::cout << "YES\n";
    for (auto i = 1; i <= n; i++)
        std::cout << a[i] << " ";
    std::cout << "\n";
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> q;
    for (auto i = 1; i <= n; i++) {
        std::cin >> a[i];
        if (a[i])
            last_pos[a[i]] = i;
        if (a[i] == q) last = true;
    }
    init_st();

    work();
}

