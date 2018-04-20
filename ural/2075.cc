// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>

#define DEBUG 0
#define FACTOR 0
#define HEIGHT 0
#define VALUE 1
#define SUM 0

using ll = long long;
auto constexpr inf = 1ll << 50;

int n;
ll last_time, t;
ll straw_height{inf};
ll all;

struct data { ll l; ll r; std::string name; };
std::vector<data> ans;

struct pos { std::string name; ll prev_sum; ll h; };
pos p;

namespace avl
{

struct node
{
    void set_child(bool right, node* u) { child[right] = u; u->parent = this; }
    auto is_right() const { return parent->child[1] == this; }

    operator bool() const;

    node* parent;
    node* child[2];
    int height;
    int balance_factor;

    std::string key;
    ll value;
    ll sum;
};

node* null{new node};
node::operator bool() const { return this != null; }

auto constexpr maxn = 100010;

struct tree
{
    tree() : data(maxn), now{data.data()}, root{null}
    {
        null->parent = null->child[0] = null->child[1] = null;
    }

    node* alloc(std::string const& key, ll value);
    void update(node* u);
    void rotate(node* u);
    void adjust(node* u);
    node* find(std::string const& key) const;
    node* insert(node* u, std::string const& key, ll value);

    void insert(std::string const& key, ll value);
    void remove(std::string const& key);
    void update(std::string const& key, ll delta);
    pos get_pos(ll h);

    void print(node* u) const;
    void print() const;

    std::vector<node> data;
    node* now;
    node* root;
};

auto tree::alloc(std::string const& key, ll value) -> node*
{
    now->key = key;
    now->value = now->sum = value;
    now->height = 1;
    now->balance_factor = 0;
    now->parent = now->child[0] = now->child[1] = null;
    return now++;
}

void tree::update(node* u)
{
    auto hl = u->child[0]->height;
    auto hr = u->child[1]->height;
    u->height = std::max(hl, hr) + 1;
    u->balance_factor = hr - hl;
    u->sum = u->child[0]->sum + u->child[1]->sum + u->value;
}

void tree::rotate(node* u)
{
    auto p = u->parent;
    auto right = u->is_right();
    p->parent->set_child(p->is_right(), u);
    p->set_child(right, u->child[!right]);
    u->set_child(!right, p);
    if (root == p)
        root = u;
    update(p);
}

void tree::adjust(node* u)
{
    for (; *u; u = u->parent) {
        update(u);
        if (abs(u->balance_factor) <= 1)
            continue;
        auto right = u->balance_factor > 1;
        u = u->child[right];
        if (u->balance_factor == (right ? -1 : +1)) {
            u = u->child[!right];
            rotate(u);
        }
        rotate(u);
        update(u);
    }
}

auto tree::find(std::string const& key) const -> node*
{
    auto u = root;
    for (; *u && u->key != key; )
        u = u->child[u->key < key];
    return u;
}

auto tree::insert(node* u, std::string const& key, ll value) -> node*
{
    if (!*root)
        return root = alloc(key, value);

    for (; ; ) {
        auto right = u->key < key;
        if (!*u->child[right]) {
            u->set_child(right, alloc(key, value));
            return u->child[right];
        }
        u = u->child[right];
    }
}

void tree::remove(std::string const& key)
{
    auto u = find(key);

    if (*u->child[0] && *u->child[1]) {
        auto next = u->child[1];
        while (*next->child[0])
            next = next->child[0];
        u->key = next->key;
        u->value = next->value;
        u = next;
    }
    auto tu = null;
    if (*u->child[0]) tu = u->child[0];
    if (*u->child[1]) tu = u->child[1];
    u->parent->set_child(u->is_right(), tu);
    if (root == u)
        root = tu;

    adjust(u->parent);

    print();
}

void tree::insert(std::string const& key, ll value)
{
    {
        auto u = find(key);
        if (*u) {
            update(key, value);
            return;
        }
    }
    auto u = insert(root, key, value);
    adjust(u->parent);
}

void tree::update(std::string const& key, ll delta)
{
    auto u = find(key);
    u->value += delta;
    u->sum += delta;
    u = u->parent;
    for (; *u; u = u->parent)
        update(u);
}

auto tree::get_pos(ll sum) -> pos
{
    if (!*root) return {};
    auto u = root;
    auto prev_sum = 0ll;
    for (; *u && !(u->child[0]->sum <= sum && sum < u->child[0]->sum + u->value); ) {
        if (sum >= u->child[0]->sum + u->value) {
            sum -= u->child[0]->sum + u->value;
            prev_sum += u->child[0]->sum + u->value;
            u = u->child[1];
        } else
            u = u->child[0];
    }
    if (!*u) return {};
    prev_sum += u->child[0]->sum;
    return {u->key, prev_sum, u->value};
}

void tree::print(node* u) const
{
    if (!*u) { std::cerr << " [ ] "; return; }

    std::cerr << " [";
    if (*u->child[0])
        print(u->child[0]);
    if (*u) {
        std::cerr << " " << u->key;
        #if FACTOR
        std::cerr << ", " << u->balance_factor;
        #endif
        #if HEIGHT
        std::cerr << ", " << u->height;
        #endif
        #if VALUE
        std::cerr << ", " << u->value;
        #endif
        #if SUM
        std::cerr << ", " << u->sum;
        #endif
        std::cerr << " ";
    }
    if (*u->child[1])
        print(u->child[1]);
    std::cerr << "] ";
}

void tree::print() const
{
    #if DEBUG
    print(root);
    std::cerr << "\n";
    #else
    #endif
}

} // namespace avl

avl::tree avt;

void drink()
{
    if (straw_height == inf)
        return;

    auto remain = t - last_time;
    for (; remain && straw_height < all; ) {
        auto cur = p.h - (straw_height - p.prev_sum);
        cur = std::min(remain, cur);
        ans.emplace_back(data{last_time, last_time + cur, p.name});
        last_time += cur;
        remain -= cur;
        all -= cur;
        if (cur == p.h)
            avt.remove(p.name);
        else
            avt.update(p.name, -cur);
        p = avt.get_pos(straw_height);
    }
    if (remain)
        straw_height = inf;
}

template <class Vec>
auto merge(Vec& v)
{
    Vec ret;
    if (v.empty()) return Vec{};
    for (auto i = 1u; i < v.size(); i++)
        if (v[i].name == v[i - 1].name && v[i - 1].r == v[i].l)
            v[i].l = v[i - 1].l;
        else
            ret.emplace_back(v[i - 1]);
    ret.emplace_back(v.back());
    return ret;
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 0; i < n; i++) {
        std::cin >> t;
        drink();
        last_time = t;

        std::string name;
        std::cin >> name;
        if (name == "fire") {
            straw_height = inf;

            avt.print();
            continue;
        }
        if (name == "Oleg") {
            ll h;
            std::cin >> h;
            straw_height = h;
            p = avt.get_pos(h);

            avt.print();
            continue;
        }
        // insert
        ll h;
        std::cin >> h;
        all += h;
        avt.insert(name, h);
        if (straw_height != inf)
            p = avt.get_pos(straw_height);

        avt.print();
    }

    t = last_time + all;
    drink();

    ans = merge(ans);
    for (auto const& d : ans)
        std::cout << d.l << "-" << d.r << " " << d.name << "\n";
}

