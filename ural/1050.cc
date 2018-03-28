// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <cctype>
#include <vector>
#include <string>

std::vector<std::vector<std::string>> a;
std::string s;
auto it = 0u;
bool left;
bool end;
int left_line;
int left_pos;

void new_paragraph()
{
    if (left)
        a[left_line][left_pos] = "";
    left = false;
}

bool getcommand(std::string& word)
{
    if (s[it] != '\\')
        return false;
    it++;

    if (it != s.size() && s[it] == '"')
        it++;

    word = "";
    while (it != s.size() && std::isalpha(s[it]))
        word += s[it++];

    return true;
}

bool getword()
{
    if (s[it] == '\\' || s[it] == '"')
        return false;
    while (it != s.size() && (s[it] != '\\' && s[it] != '"'))
        it++;

    return true;
}

bool getquote()
{
    if (s[it] == '"') {
        it++;
        return true;
    }
    return false;
}

bool blank_line()
{
    return std::all_of(s.begin(), s.end(), [](char ch) {
        return std::isblank(ch);
    });
}

int main()
{
    for (auto line = 0; !end; line++) {
        std::getline(std::cin, s);
        a.emplace_back(std::vector<std::string>{});

        for (auto ch : s)
            a[line].emplace_back(1, ch);

        if (blank_line()) {
            new_paragraph();
            continue;
        }

        for (it = 0; it != s.size(); ) {
            std::string word;
            if (getcommand(word)) {
                if (word == "par")
                    new_paragraph();
                if (word == "endinput") {
                    end = true;
                    new_paragraph();
                    break;
                }
                continue;
            }
            if (getword()) {
                continue;
            }
            if (getquote()) {
                if (left) {
                    left = false;
                    a[left_line][left_pos] = "``";
                    a[line][it - 1] = "''";
                } else {
                    left = true;
                    left_line = line;
                    left_pos = it - 1;
                }
                continue;
            }
        }
    }

    for (auto const& v : a) {
        for (auto const& str : v)
            std::cout << str;
        std::cout << "\n";
    }
}

