#include <iostream>
#include <algorithm>
#include <string>

auto part(std::string const& s)
{
    return std::count(s.begin(), s.end(), ' ');
}

auto step1()
{
    std::string s;
    do {
        std::cout << "next 0 1\n";
        std::cout.flush();
        std::getline(std::cin, s);
        std::cerr << ">> " << s << "\n";
        std::cout << "next 1\n";
        std::cout.flush();
        std::getline(std::cin, s);
        std::cerr << ">> " << s << "\n";
    } while (part(s) == 3);
    return part(s) == 1;
}

auto step2()
{
    std::string s;
    do {
        std::cout << "next 0 1 2 3 4 5 6 7 8 9\n";
        std::cout.flush();
        std::getline(std::cin, s);
    } while (part(s) != 1);
    return true;
}

int main()
{
    std::string s;
    if (step1() || step2())
        std::cout << "done\n";
}

