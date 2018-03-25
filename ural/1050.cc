#include <iostream>
#include <cctype>
#include <vector>
#include <string>

std::vector<std::vector<std::string>> a;
std::string s;
auto it = 0u;
bool left;
int left_line;
int left_pos;

void new_paragraph()
{
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
    while (it != s.size() && (s[it] != '\\' || s[it] != '"'))
        it++;

    return true;
}

bool getquote()
{
    return s[it] == '"';
}

int main()
{
    for (auto line = 0; ; line++) {
        std::getline(std::cin, s);
        a.emplace_back(std::vector<std::string>{});

        // FIXME blank line?
        if (s.empty()) {
            new_paragraph();
            continue;
        }

        for (auto ch : s)
            a[line].emplace_back(1, ch);

        for (it = 0; it != s.size(); ) {
            std::string word;
            if (getcommand(word)) {
                if (word == "par")
                    new_paragraph();
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

