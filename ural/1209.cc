// ml:run = $bin < input
#include <iostream>
#include <cmath>

int zero_one(long long i)
{
    long long a = (i-1) * 2;
    long long q = std::sqrt(a);
    return q * (q+1) == a;
}

int main()
{
    long long n;
    std::cin >> n;
    for (int i = 0; i < n; ++i) {
        int num = 0;
        std::cin >> num;
        std::cout << zero_one(num) << "\n";
    }
}

