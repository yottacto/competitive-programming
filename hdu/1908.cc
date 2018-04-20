// ml:run = time -p $bin < input > output
#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

namespace avl
{
    struct node
    {
        bool is_right() const
        {
            return parent->child[1] == this;
        }

        void set_child(bool is_right, node* u)
        {
            child[is_right] = u;
            u->parent = this;
        }

        operator bool() const;

        node* parent;
        node* child[2];
        int key;
        int value;
        int height;
        int balance_factor;
    };

    node* null = new node;
    node::operator bool() const { return this != null; }

    template <class T>
    T abs(T x) { return x < 0 ? -x : x; }

    #define DEBUG 1

    int const maxn = 100000;
    std::vector<node> data(maxn);
    node* now;

    struct tree
    {
        tree(int cap = maxn)
        {
            data.resize(cap);
            now = data.data();
            null->parent = null->child[0] = null->child[1] = null;
            root = null;
        }

        node* alloc(int key, int value);
        void update(node* u);
        void rotate(node* u);
        void adjust(node* u);

        void adjust_insert(node* u);
        void insert(int key, int value);
        node* insert(node* u, int key, int value);

        void adjust_remove(node* u);
        void remove(int key);
        node* remove(node* u, int key);

        node* find_max() const;
        node* find_min() const;

        int pop_max();
        int pop_min();

        void print(node* u) const;
        void print() const;

        node* root;
    };

    node* tree::alloc(int key, int value)
    {

        // node* u = new node;
        // u->key = key;
        // u->value = value;
        // u->parent = u->child[0] = u->child[1] = null;
        // u->height = 1;
        // u->balance_factor = 0;
        // return u;

        now->key = key;
        now->value = value;
        now->parent = now->child[0] = now->child[1] = null;
        now->height = 1;
        now->balance_factor = 0;
        return now++;

    }

    void tree::update(node* u)
    {
        int hl = u->child[0]->height;
        int hr = u->child[1]->height;
        u->height = std::max(hl, hr) + 1;
        u->balance_factor = hr - hl;
    }

    void tree::rotate(node* u)
    {
        node* p = u->parent;
        bool is_right = u->is_right();
        p->set_child(is_right, u->child[!is_right]);
        p->parent->set_child(p->is_right(), u);
        u->set_child(!is_right, p);
        if (root == p)
            root = u;
        update(p);
    }

    void tree::adjust_insert(node* u)
    {
        for (node* p = u->parent; *p; p = u->parent) {
            int t1 = u->is_right() ? +1 : -1;
            int t2 = p->balance_factor;
            if (t1 + t2 == 0) {
                update(p);
                break;
            }
            if (t2 == 0) {
                update(p);
                u = p;
                continue;
            }
            int t3 = u->balance_factor;
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

    void tree::adjust_remove(node* u)
    {
        node* tu = u;
        for (node* p = u->parent; *p; p = u->parent) {
            int t1 = u->is_right() ? +1 : -1;
            int t2 = p->balance_factor;
            if (t2 == 0) {
                update(p);
                break;
            }
            if (abs(t1 + t2) == 2) {
                update(p);
                u = p;
                continue;
            }
            int  h = p->height;
            u = p->child[!u->is_right()];
            int t3 = u->balance_factor;
            if (abs(t1 + t3) == 2) {
                u = u->child[(t3 + 1)/2];
                rotate(u);
            }
            rotate(u);
            update(u);
            if (u->height == h)
                break;
        }
        if (!root->height)
            root = null;
        else if (!tu->height)
            tu->parent->set_child(tu->is_right(), null);

        if (u->height)
            for (; *u; u = u->parent)
                update(u);
    }

    void tree::adjust(node* u)
    {
        for (; *u; u = u->parent) {
            update(u);
            if (abs(u->balance_factor) <= 1) continue;
            auto right = u->balance_factor > 1;
            u = u->child[right];
            if (u->balance_factor == (right ? -1 : 1)) {
                u = u->child[!right];
                rotate(u);
            }
            rotate(u);
            update(u);
        }
    }

    node* tree::insert(node* u, int key, int value)
    {
        if (!*root)
            return root = alloc(key, value);
        for (; ;) {
            bool is_right = u->key < key;
            if (!*u->child[is_right]) {
                u->set_child(is_right, alloc(key, value));
                return u->child[is_right];
            }
            u = u->child[is_right];
        }
    }

    void tree::insert(int key, int value)
    {
        node* u = insert(root, key, value);
        adjust(u->parent);
        // adjust_insert(u);
    }

    node* tree::remove(node* u, int key)
    {
        for (; u->key != key;)
            u = u->child[u->key < key];
        if (*u->child[0] && *u->child[1]) {
            node* next = u->child[1];
            while (*next->child[0])
                next = next->child[0];
            u->key = next->key;
            u->value = next->value;
            u = next;
        }
        node* tu = null;
        if (*u->child[0]) tu = u->child[0];
        if (*u->child[1]) tu = u->child[1];
        if (root == u) root = tu;
        u->parent->set_child(u->is_right(), tu);
        return tu;
    }

    void tree::remove(int key)
    {
        node* u = remove(root, key);
        // adjust_remove(u);
        adjust(u->parent);
    }

    node* tree::find_max() const
    {
        if (!*root) return root;
        node* u = root;
        for (; *u->child[1]; u = u->child[1])
            ;
        return u;
    }

    node* tree::find_min() const
    {
        if (!*root) return root;
        node* u = root;
        for (; *u->child[0]; u = u->child[0])
            ;
        return u;
    }

    int tree::pop_min()
    {
        node* u = find_min();
        if (!*u) return 0;
        remove(u->key);
        return u->value;
    }

    int tree::pop_max()
    {
        node* u = find_max();
        if (!*u) return 0;
        remove(u->key);
        return u->value;
    }

//     void tree::print(node* u) const
//     {
//         if (!*u) { std::cerr << " [ ] "; return; }

//         std::cerr << " [";
//         if (*u->child[0])
//             print(u->child[0]);
//         if (*u) {
//             std::cerr << " " << u->key;
//             #if FACTOR
//             std::cerr << ", " << u->size;
//             #endif
//             #if FACTOR
//             std::cerr << ", " << u->balance_factor;
//             #endif
//             #if HEIGHT
//             std::cerr << ", " << u->height;
//             #endif
//             std::cerr << " ";
//         }
//         if (*u->child[1])
//             print(u->child[1]);
//         std::cerr << "] ";
//     }

//     void tree::print() const
//     {
//         #if DEBUG
//         print(root);
//         std::cerr << "\n";
//         #else
//         #endif
//     }

}

int main()
{
    // std::ios::sync_with_stdio(false);
    avl::tree avt;
    std::vector<int> ans;
    for (int i; std::scanf("%d", &i) && i; ) {
        if (i == 1) {
            int id, p;
            std::scanf("%d%d", &id, &p);
            avt.insert(p, id);
        } else if (i == 2)
            // ans.push_back(avt.pop_max());
            std::printf("%d\n", avt.pop_max());
        else
            // ans.push_back(avt.pop_min());
            std::printf("%d\n", avt.pop_min());
        // avt.print();
    }
    // for (auto i : ans)
    //     std::cout << i << "\n";
}

