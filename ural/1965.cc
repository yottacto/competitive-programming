// ml:run = $bin < input
// ml:opt = 0
// ml:ccf += -g
#include <iostream>
#include <iterator>
#include <algorithm>
#include <functional>
#include <vector>

auto constexpr inf = 200001;
std::vector<int> a;
int n;
auto less = std::less<int>{};
auto greater = std::greater<int>{};

template <class Compare>
auto same_order(Compare comp)
{
    // std::cerr << "same\n";

    std::vector<int> ra{inf};
    std::vector<int> rb{inf};
    if (comp(0, ra[0]))
        ra[0] = 0;
    if (comp(0, rb[0]))
        rb[0] = 0;

    for (auto i : a) {
        // ensure when comp = less, ra.back() > rb.back()
        if (comp(ra.back(), rb.back()))
            std::swap(ra, rb);

        if (comp(ra.back(), i))
            ra.emplace_back(i);
        else if (comp(rb.back(), i))
            rb.emplace_back(i);
        else
            return false;
    }

    if (ra.size() > rb.size())
        std::swap(ra, rb);
    if (ra.size() == 1) {
        ra.emplace_back(rb.back());
        rb.pop_back();
    }

    std::cout << ra.size() - 1 << " " << rb.size() - 1 << "\n";
    for (auto i = 1u; i < ra.size(); i++)
        std::cout << ra[i] << " ";
    std::cout << "\n";
    for (auto i = 1u; i < rb.size(); i++)
        std::cout << rb[i] << " ";
    std::cout << "\n";
    return true;
}

template <class Vec, class Compare>
auto longest(Vec& id, Compare comp)
{
    std::vector<int> from(n + 1);
    std::vector<int> pos(n + 1);

    auto init = inf;
    if (!comp(0, inf))
        init = 0;
    std::vector<int> v(n + 1, init);
    v[0] = init ? 0 : inf;

    auto len = 0;
    auto last = 0;
    for (auto i = 0; i < n; i++) {
        auto p = std::lower_bound(std::begin(v), std::end(v), a[i], comp) - std::begin(v);
        v[p] = a[i];
        pos[p] = i + 1;
        from[i + 1] = pos[p - 1];
        len = std::max(len, (int)p);
        if (p == len)
            last = i + 1;
    }
    id.resize(len);
    for (auto i = 0; last; i++) {
        id[len - i - 1] = last - 1;
        last = from[last];
    }
    return len;
}

template <class Vec, class Compare>
auto check(Vec const& v, Compare comp)
{
    auto p = 0u;
    auto last = inf;
    if (comp(0, last))
        last = 0;
    for (auto i = 0; i < n; i++) {
        if (p < v.size() && v[p] == i) {
            p++;
            continue;
        }
        if (!comp(last, a[i]))
            return false;
        last = a[i];
    }
    return true;
}

template <class Vec>
void fill_remain(Vec& to_fill, Vec const& occupied)
{
    to_fill.clear();
    auto p = 0u;
    for (auto i = 0; i < n; i++) {
        if (p < occupied.size() && occupied[p] == i) {
            p++;
            continue;
        }
        to_fill.emplace_back(i);
    }
}

auto diff_order()
{
    // std::cerr << "diff\n";

    std::vector<int> id0;
    std::vector<int> id1;
    if (longest(id0, less) > longest(id1, greater)) {
        if (!check(id0, greater))
            return false;
        fill_remain(id1, id0);
    } else {
        if (!check(id1, less))
            return false;
        fill_remain(id0, id1);
    }

    if (id0.size() > id1.size())
        std::swap(id0, id1);
    if (id0.empty()) {
        id0.emplace_back(id1.back());
        id1.pop_back();
    }

    std::cout << id0.size() << " " << id1.size() << "\n";
    for (auto i : id0)
        std::cout << a[i] << " ";
    std::cout << "\n";
    for (auto i : id1)
        std::cout << a[i] << " ";
    std::cout << "\n";
    return true;
}

int main()
{
    std::cin >> n;
    a.resize(n);
    for (auto& i : a)
        std::cin >> i;

    if (same_order(less)
        || same_order(greater)
        || diff_order()) {
        return 0;
    }
    std::cout << "Fail\n";
}

