// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <string>
#include <stack>

int n, k;
std::string s;

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> k >> s;
    std::string ans(n, '#');
    std::stack<int> st;
    auto count = 0;
    for (auto i = 0; i < n; i++) {
        if (s[i] == '(')
            st.push(i);
        else {
            if (st.empty()) continue;
            auto l = st.top();
            st.pop();
            count += 2;
            ans[l] = s[l];
            ans[i] = s[i];
            if (count == k)
                break;
        }
    }
    ans.erase(std::remove_if(ans.begin(), ans.end(), [](char ch) {
        return ch == '#';
    }), ans.end());
    std::cout << ans << "\n";
}

