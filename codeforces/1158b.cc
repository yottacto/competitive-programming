// ml:run = $bin < input
// ml:std = c++14
#include <iostream>

int n, k;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k;
    auto a = (n - k) / 2;
    std::string s(a, '1');
    s += '0';
    std::string res;
    while (res.size() < n)
        res += s;
    res.erase(n);
    std::cout << res << "\n";
}

