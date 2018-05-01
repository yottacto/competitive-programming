// ml:run = $bin < input
#include <iostream>
#include <vector>
#include <string>

std::string s;
int n;

std::vector<std::vector<int>> seq;
std::vector<int> ends[2];

auto run()
{
    for (auto i = 0; i < n; i++) {
        auto now = s[i] - '0';
        if (now == 0) {
            if (ends[1].empty()) {
                seq.emplace_back(1, i + 1);
                ends[0].emplace_back(seq.size() - 1);
            } else {
                auto id = ends[1].back();
                seq[id].emplace_back(i + 1);
                ends[1].pop_back();
                ends[0].emplace_back(id);
            }
        } else {
            if (ends[0].empty())
                return false;
            auto id = ends[0].back();
            seq[id].emplace_back(i + 1);
            ends[0].pop_back();
            ends[1].emplace_back(id);
        }
    }
    return ends[1].empty();
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> s;
    n = s.size();
    if (run()) {
        std::cout << seq.size() << "\n";
        for (auto const& v : seq) {
            std::cout << v.size();
            for (auto i : v)
                std::cout << "  " << i;
            std::cout << "\n";
        }
    } else
        std::cout << "-1\n";
}

