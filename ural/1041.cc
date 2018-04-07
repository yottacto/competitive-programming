// ml:run = $bin < input
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <vector>

long double constexpr eps = 1e-20;

template <class T>
T abs(T x) { return x < 0 ? -x : x; }

auto equal(long double lhs, long double rhs) { return abs(lhs - rhs) <= eps; }
auto less(long double lhs, long double rhs) { return lhs + eps < rhs; }

struct item
{
    int value;
    int id;
    std::vector<long double> v;
};

int n, m;
std::vector<item> mat;

void swap_col(int c0, int c1)
{
    for (auto i = 0; i < m; i++)
        std::swap(mat[i].v[c0], mat[i].v[c1]);
}

void print()
{
    for (auto const& row : mat) {
        std::cerr << row.id << ", " << row.value << " : ";
        for (auto i : row.v)
            std::cerr << std::fixed << std::setprecision(0) << i << " ";
        std::cerr << "\n";
    }
    std::cerr << "==================\n";
}

int main()
{
    std::cin >> m >> n;
    mat.resize(m);
    for (auto& row : mat) {
        row.v.resize(n);
        for (auto i = 0; i < n; i++)
            std::cin >> row.v[i];
    }
    for (auto i = 0; i < m; i++) {
        std::cin >> mat[i].value;
        mat[i].id = i + 1;
    }
    std::sort(std::begin(mat), std::end(mat), [](item const& lhs, item const& rhs) {
        return lhs.value < rhs.value
            || (lhs.value == rhs.value && lhs.id < rhs.id);
    });

    auto sum = 0;
    std::vector<int> ans;
    for (auto i = 0; (int)ans.size() < n && i < m; i++) {
        // which dimenison
        int d = ans.size();
        auto p = d;
        while (p < n && equal(mat[i].v[p], 0))
            p++;
        if (p == n)
            continue;

        // std::cout << "i = " << i << " p = " << p << " before swap\n";
        // print();

        swap_col(p, d);

        // std::cout << "i = " << i << " after swap\n";
        // print();

        sum += mat[i].value;
        ans.emplace_back(mat[i].id);

        for (auto j = i + 1; j < m; j++) {
            if (equal(mat[j].v[d], 0))
                continue;

            auto scale = mat[j].v[d] / mat[i].v[d];
            for (auto k = 0; k < n; k++)
                mat[j].v[k] -= scale * mat[i].v[k];
        }

        // std::cout << "i = " << i << " end\n";
        // print();

    }

    // std::cerr << "ans.size() = " << ans.size() << "\n";

    if ((int)ans.size() != n)
        std::cout << "0\n";
    else {
        std::cout << sum << "\n";
        std::sort(std::begin(ans), std::end(ans));
        std::copy(std::begin(ans), std::end(ans), std::ostream_iterator<int>{std::cout, "\n"});
    }
}

