// ml:run = cp $bin bug
#include <iostream>
#include <iomanip>
#include <iterator>
#include <algorithm>
#include <vector>

using value_type = long long;
auto constexpr mo = 991'744'687ll;

struct item
{
    int value;
    int id;
    std::vector<value_type> v;
};

int n, m;
std::vector<item> mat;

void swap_col(int c0, int c1)
{
    for (auto i = 0; i < m; i++)
        std::swap(mat[i].v[c0], mat[i].v[c1]);
}

int main()
{
    std::cin >> m >> n;
    mat.resize(m);
    for (auto& row : mat) {
        row.v.resize(n);
        for (auto& i : row.v) {
            std::cin >> i;
            i = (i + mo) % mo;
        }
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
        // which dimenison currently deal with
        int d = ans.size();
        auto p = d;
        while (p < n && mat[i].v[p] == 0)
            p++;
        if (p == n)
            continue;

        swap_col(p, d);

        sum += mat[i].value;
        ans.emplace_back(mat[i].id);

        for (auto j = i + 1; j < m; j++) {
            if (mat[j].v[d] == 0)
                continue;

            auto si = mat[i].v[d];
            auto sj = mat[j].v[d];
            for (auto k = d; k < n; k++) {
                mat[j].v[k] = (mat[j].v[k] * si) % mo;
                mat[j].v[k] -= (mat[i].v[k] * sj) % mo;
                mat[j].v[k] = (mat[j].v[k] + mo) % mo;
            }
        }
    }

    if ((int)ans.size() != n)
        std::cout << "0\n";
    else {
        std::cout << sum << "\n";
        std::sort(std::begin(ans), std::end(ans));
        std::copy(std::begin(ans), std::end(ans), std::ostream_iterator<int>{std::cout, "\n"});
    }
}

