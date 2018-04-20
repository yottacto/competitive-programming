// ml:run = cp $bin bug
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <iterator>
#include <algorithm>
#include <vector>

namespace avl
{

    struct node
    {
        operator bool() const;

        auto is_right() const
        {
            return parent->child[1] == this;
        }

        void set_child(bool is_right, node* u)
        {
            child[is_right] = u;
            u->parent = this;
        }

        node* parent;
        node* child[2];
        int key;
        int height;
        int balance_factor;
        int size;
    };

    node tnull;
    node* null = &tnull;

    node::operator bool() const
    {
        return this != null;
    }

    auto constexpr maxn = 20000;

    template <class T>
    T abs(T x) { return x < 0 ? -x : x; }

    struct tree
    {
        std::vector<node> data;
        node* now;
        node* root;

        tree(int cap = maxn)
        {
            data.resize(cap);
            now = data.data();
            root = null;
            root->parent = root->child[0] = root->child[1] = null;
        }

        auto alloc(int key)
        {
            now->key = key;
            now->child[0] = now->child[1] = now->parent = null;
            now->height = now->size = 1;
            now->balance_factor = 0;
            return now++;
        }

        void update(node* u)
        {
            auto hleft  = u->child[0]->height;
            auto hright = u->child[1]->height;
            u->height = std::max(hleft, hright) + 1;
            u->balance_factor = hright - hleft;
            u->size = u->child[0]->size + u->child[1]->size + 1;
        }

        auto rotate(node* u)
        {
            auto is_right = u->is_right();
            auto p = u->parent;
            p->parent->set_child(p->is_right(), u);
            p->set_child(is_right, u->child[!is_right]);
            u->set_child(!is_right, p);
            if (p == root) root = u;
            update(p);
        }

        void adjust(node* u)
        {
            for (auto p = u->parent; *p; p = u->parent) {
                auto t1 = u->is_right() ? +1 : -1;
                auto t2 = p->balance_factor;
                if (t1 + t2 == 0) {
                    update(p);
                    break;
                }
                if (abs(t1 + t2) == 1) {
                    update(p);
                    u = p;
                    continue;
                }
                auto t3 = u->balance_factor;
                if (t1 + t3 == 0) {
                    u = u->child[(t3 + 1)/2];
                    rotate(u);
                }
                rotate(u);
                update(u);
            }
            for (; *u; u = u->parent)
                update(u);
        }

        auto insert(node* u, int key)
        {
            if (!*u)
                return root = alloc(key);
            for (; ; ) {
                auto is_right = u->key < key;
                if (!*u->child[is_right]) {
                    auto new_node = alloc(key);
                    u->set_child(is_right, new_node);
                    return new_node;
                }
                u = u->child[is_right];
            }
        }

        void insert(int key)
        {
            auto u = insert(root, key);
            adjust(u);
        }

        auto le_count(int key)
        {
            auto ret = 0;
            auto u = root;
            while (*u) {
                if (key < u->key)
                    u = u->child[0];
                else {
                    ret += u->child[0]->size + 1;
                    if (!*u->child[1])
                        break;
                    u = u->child[1];
                }
            }
            return ret;
        }

        void print(node* u) const
        {
            if (!*u) { std::cout << " [ ] "; return; }

            std::cout << " [";
            if (*u->child[0])
                print(u->child[0]);
            if (*u)
                std::cout << " " << u->key << ", " << u->size << " ";
            if (*u->child[1])
                print(u->child[1]);
            std::cout << "] ";
        }

        void print() const
        {
            print(root);
        }
    };
}

struct point
{
    int x;
    int y;
    int id;
};

auto operator<(point const& lhs, point const& rhs)
{
    return lhs.x < rhs.x
        || (lhs.x == rhs.x && lhs.y < rhs.y);
}

int n;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    std::vector<int> ans(n);
    std::vector<point> points(n);
    for (auto i = 0; i < n; i++) {
        std::cin >> points[i].x >> points[i].y;
        points[i].id = i;
    }
    std::sort(std::begin(points), std::end(points));

    avl::tree avt;
    for (auto const& p : points) {

        // std::cerr << "->" << avt.le_count(p.y) << "\n";

        ans[avt.le_count(p.y)]++;
        avt.insert(p.y);

        // avt.print();
        // std::cerr << "\n";

    }
    for (auto i : ans)
        std::cout << i << "\n";

    // avt.print();
    // std::cout << "\n";
}

