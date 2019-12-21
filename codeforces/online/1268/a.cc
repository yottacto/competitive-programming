// ml:run = $bin < input
#include <bits/stdc++.h>

int n, k;
std::vector<int> a;
std::vector<int> b;

void print(std::vector<int> const& a)
{
    std::cout << n << "\n";
    for (auto i = 0; i < n; i++)
        std::cout << a[i];
    std::cout << "\n";
}

template <class Vec>
bool ge(Vec const& a, Vec const& b)
{
    for (auto i = 0; i < n; i++)
        if (a[i] > b[i])
            return true;
        else if (a[i] < b[i])
            return false;
    return true;
}

bool check_equal()
{
    b = a;
    for (auto i = k; i < n; i++)
        b[i] = b[i - k];
    return ge(b, a);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    std::cin >> n >> k;
    a.resize(n);
    for (auto i = 0; i < n; i++) {
        char ch;
        std::cin >> ch;
        a[i] = ch - '0';
    }

    if (check_equal()) {
        print(b);
        return 0;
    }

    b = a;
    b[k - 1]++;
    for (auto i = k - 1; i >= 1; i--) {
        if (b[i] >= 10) {
            b[i - 1]++;
            b[i] -= 10;
        }
    }
    for (auto i = k; i < n; i++)
        b[i] = b[i - k];
    print(b);

}

