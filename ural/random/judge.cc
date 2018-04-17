// ml:run = cp $bin judge
#include <iostream>
#include <sstream>
#include <string>
#include <functional>
#include <map>
#include <fstream>
#include <vector>

auto less = std::less<int>{};
auto greater = std::greater<int>{};

std::vector<int> da;
std::vector<int> a;
std::vector<int> b;

std::map<int, int> pos;

bool vis[200000];

auto judge()
{
    std::ifstream fin{"bfdiff.out1"};
    std::string s;
    std::getline(fin, s);
    if (s == "Fail")
        return true;
    std::stringstream buf{s};
    int na, nb;
    buf >> na >> nb;
    a.resize(na);
    for (auto& i : a)
        fin >> i;

    b.resize(nb);
    for (auto& i : b)
        fin >> i;

    vis[a[0]] = true;
    for (auto i = 1; i < na; i++) {
        if (vis[a[i]]) return false;
        if ((a[0] < a[1]) != (a[i - 1] < a[i]))
            return false;
        if (pos[a[i - 1]] > pos[a[i]])
            return false;
        vis[a[i]] = true;
    }

    if (vis[b[0]])
        return false;
    vis[b[0]] = true;
    for (auto i = 1; i < nb; i++) {
        if (vis[b[i]]) return false;
        if ((b[0] < b[1]) != (b[i - 1] < b[i]))
            return false;
        if (pos[b[i - 1]] > pos[b[i]])
            return false;
        vis[b[i]] = true;
    }

    return true;
}

int main()
{
    {
        std::ifstream fin{"bfdiff.in"};
        int n;
        fin >> n;
        da.resize(n);
        for (auto i = 0; i < n; i++) {
            fin >> da[i];
            pos[da[i]] = i;
        }
    }

    if (judge())
        std::cout << "YES\n\n";
    else
        std::cout << "NO\n\n";
}

