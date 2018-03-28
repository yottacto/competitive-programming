// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <iterator>
#include <numeric>
#include <vector>

int main()
{
    int n;
    std::cin >> n;
    std::vector<int> v;
    std::copy(
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{},
        std::back_inserter(v)
    );
    auto avg = std::accumulate(std::begin(v), std::end(v), 0.) / (n + 1);
    auto mad_sum = std::accumulate(std::begin(v), std::end(v), 0., [avg](auto last, auto x) {
        return last + std::max(x - avg, 0.);
    });

    std::for_each(std::begin(v), std::end(v), [avg, mad_sum](auto x) {
        auto get = int(std::max(x - avg, 0.) * 100. / mad_sum + 1e-7);
        std::cout << get << " ";
    });
    std::cout << "\n";
}

