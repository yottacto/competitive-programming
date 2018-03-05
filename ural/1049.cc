// ml:run = $bin < input
#include <iostream>
#include <numeric>
#include <iterator>
#include <vector>
#include <map>

int main()
{
    std::vector<int> num{
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{}
    };

    using map_type = std::map<int, int>;
    map_type prime_factor;

    using std::begin;
    using std::end;
    prime_factor = std::accumulate(begin(num), end(num), prime_factor, [](map_type a, int b) {
        for (auto i = 2; i * i <= b; i++) {
            auto count = 0;
            for (; b % i == 0; b /= i)
                count++;
            if (count) a[i] += count;
        }
        if (b != 1) a[b]++;
        return a;
    });

    auto ans = std::accumulate(begin(prime_factor), end(prime_factor), 1, [](int c, std::pair<int, int> a) {
        return (c * (a.second + 1)) % 10;
    });

    std::cout << ans << "\n";

}

