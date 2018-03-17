#include <iostream>
#include <iterator>
#include <algorithm>
#include <numeric>

int main()
{
    std::for_each(
        std::istream_iterator<int>{std::cin},
        std::istream_iterator<int>{},
        [](int x) {
            std::cout << (x > 6 ? "YES" : "NO") << "\n";
        }
    );
}

