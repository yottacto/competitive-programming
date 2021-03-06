// ml:run = $bin < input
#include <iostream>
#include <utility>
#include <vector>
#include <unordered_map>

auto constexpr maxn = 300007;
auto constexpr maxl = 32;
int root[maxn];
int n, q;
int r, rkey;
int min_answer, max_answer;

std::vector<std::vector<int>> tree;
std::unordered_map<int, int> id;
int gid;

struct node
{
    int l;
    int r;
    int count;
};

node pst[maxn * 40];
int alloc;

auto get_id(int x)
{
    if (id.count(x)) return id.at(x);
    return id[x] = ++gid;
}

template <class Compare = std::less<int>>
auto query(int now, int x, Compare comp = {}, int d = maxl - 1) -> int
{
    if (d < 0) return 0;

    auto cur_bit = (x >> d) & 1;
    if (
        (pst[pst[now].l].count && comp(cur_bit^1, cur_bit))
        || !pst[pst[now].r].count
    )
        return query(pst[now].l, x, comp, d - 1);
    else
        return (1<<d) | query(pst[now].r, x, comp, d - 1);
}

void find_ans(int v, int k)
{
    min_answer = query(root[v], k, std::greater<int>{}) ^ k;
    max_answer = query(root[v], k) ^ k;
}

void update(int& now, int pre, int x, int d = maxl - 1)
{
    pst[now = ++alloc] = pst[pre];
    pst[now].count++;

    if (d < 0) return;

    if (x & (1<<d))
        update(pst[now].r, pst[pre].r, x, d - 1);
    else
        update(pst[now].l, pst[pre].l, x, d - 1);
}

void add_edge(int u, int v, int k)
{
    update(root[get_id(v)], root[get_id(u)], k);
}

int main()
{
    std::ios::sync_with_stdio(false);
    id[0] = 0;
    std::cin >> n >> q;
    tree.resize(n + q + 1);
    std::cin >> r >> rkey;
    add_edge(0, r, rkey);
    for (auto i = 1; i < n; i++) {
        int u, v, k; std::cin >> u >> v >> k;
        add_edge(v, u, k);
    }

    auto last_answer = min_answer ^ max_answer;
    for (int opt, v, u, k; q-- && std::cin >> opt; ) {
        opt ^= last_answer;
        if (opt) {
            std::cin >> v >> k;
            v ^= last_answer;
            k ^= last_answer;
            find_ans(get_id(v), k);
            last_answer = min_answer ^ max_answer;
            std::cout << min_answer << " " << max_answer << "\n";
        } else {
            std::cin >> v >> u >> k;
            v ^= last_answer;
            u ^= last_answer;
            k ^= last_answer;
            add_edge(v, u, k);
        }
    }
}

