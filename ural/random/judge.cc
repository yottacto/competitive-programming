// ml:run = cp $bin judge
#include <iostream>
#include <fstream>
#include <vector>

std::vector<double> a;
std::vector<double> b;

auto constexpr eps = 1e-6;

template <class T>
T abs(T x)
{
    return x < 0 ? -x : x;
}

auto judge()
{
    if (a.size() != b.size())
        return false;
    for (auto i = 0u; i < a.size(); i++)
        if (abs(a[i] - b[i]) / a[i] > eps)
            return false;
    return true;
}

int main()
{
    {
        std::ifstream fin{"bfdiff.out1"};
        for (double d; fin >> d; )
            a.emplace_back(d);
    }
    {
        std::ifstream fin{"bfdiff.out2"};
        for (double d; fin >> d; )
            b.emplace_back(d);
    }
    if (judge())
        std::cout << "YES\n\n";
    else
        std::cout << "NO\n\n";
}

