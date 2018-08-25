// ml:run = $bin < input
#include <iostream>
#include <string>

int n, m;
std::string s;
std::string t;

void print(bool yes)
{
    if (yes)
        std::cout << "YES\n";
    else
        std::cout << "NO\n";
}

auto check()
{
    auto p = s.find('*');
    std::cerr << s.substr(p + 1) << " : " << t.substr(t.size() - (s.size() - p - 1)) << "\n";
    return s.substr(0, p) == t.substr(0, p)
        && s.substr(p + 1) == t.substr(t.size() - (s.size() - p - 1));
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    std::cin >> s >> t;
    if (s.find('*') == std::string::npos)
        print(s == t);
    else {
        if (s.size() - 1 > t.size())
            print(false);
        else
            print(check());
    }
}

