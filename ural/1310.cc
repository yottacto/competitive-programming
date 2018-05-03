// ml:run = $bin < input
#include <iostream>
#include <string>
#include <vector>
#include <array>

int l, m, k;

template <class T>
struct solver
{
    solver()
    {
        for (auto now = 1; now <= m; now++)
            f[1][now][now % k] = T{1};
        for (int i = 2; i <= l; i++)
            for (auto now = 1; now <= m; now++)
            for (auto prev = 1; prev <= m; prev++)
                for (auto r = 0; r < k; r++)
                    f[i][now][(r + now) % k] +=
                        f[i - 1][prev][r];
    }

    void operator()(T n)
    {
        auto r = 0;
        for (auto i = l; i >= 1; i--) {
            auto j = 1;
            for (; !(n < f[i][j][r]); j++)
                n -= f[i][j][r];
            std::cout << j << " ";
            r = (r - j) % k;
            if (r < 0) r += k;
            // std::cerr << " :: " << n << " " << r << "\n";
        }
        std::cout << "\n";
    }

    std::array<std::array<std::array<T, 51>, 51>, 101> f;
};

struct big_integer
{
    // single digit
    big_integer(int x = 0) : a{x} {}

    big_integer(std::string const& s)
    {
        for (auto it = s.crbegin(); it != s.crend(); ++it)
            a.emplace_back(*it - '0');
    }

    auto size() const { return a.size(); }
    auto      & operator[](int x)       { return a[x]; }
    auto const& operator[](int x) const { return a[x]; }

    void operator+=(big_integer const& rhs)
    {
        auto len = std::max(size(), rhs.size());
        a.resize(len);
        for (auto i = 0u; i < len; i++) {
            if (i < rhs.size())
                a[i] += rhs[i];
            if (a[i] >= 10) {
                a[i] -= 10;
                if (i == len - 1)
                    a.emplace_back(0);
                a[i + 1]++;
            }
        }
    }

    // big - small
    void operator-=(big_integer const& rhs)
    {
        for (auto i = 0u; i < size(); i++) {
            if (i < rhs.size())
                a[i] -= rhs[i];
            if (a[i] < 0) {
                a[i] += 10;
                a[i + 1]--;
            }
        }
        auto len = size();
        while (len > 1 && !a[len - 1])
            len--;
        a.resize(len);
    }

    std::vector<int> a;
};

inline auto operator+(big_integer lhs, big_integer const& rhs)
{
    lhs += rhs;
    return lhs;
}

inline auto operator-(big_integer lhs, big_integer const& rhs)
{
    lhs -= rhs;
    return lhs;
}

inline auto operator<(big_integer const& lhs, big_integer const& rhs)
{
    if (lhs.size() != rhs.size())
        return lhs.size() < rhs.size();
    for (int i = lhs.size() - 1; i >= 0; i--)
        if (lhs[i] != rhs[i])
            return lhs[i] < rhs[i];
    return false;
}

inline auto& operator>>(std::istream& is, big_integer& a)
{
    std::string s;
    is >> s;
    a = big_integer{s};
    return is;
}

inline auto& operator<<(std::ostream& os, big_integer const& a)
{
    for (auto it = a.a.crbegin(); it != a.a.crend(); ++it)
        os << *it;
    return os;
}

int main()
{
    std::cin >> l >> m >> k;
    big_integer n;
    std::cin >> n;
    solver<big_integer>{}(n);
}

