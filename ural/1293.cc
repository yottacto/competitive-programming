// ml:run = $bin < input
#include <iostream>
#include <iterator>
#include <functional>
#include <numeric>

int main()
{
    std::cout << std::accumulate(
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{},
        1,
        std::multiplies<int>{}
    ) * 2 << "\n";
}

