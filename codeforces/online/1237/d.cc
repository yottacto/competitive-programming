// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <deque>

auto constexpr maxn = 100007;
int a[maxn];
int right[maxn];
int right2[maxn];
int right_max[maxn];
int ans[maxn];
int n;

template <class T>
int get_max(int x, T const& dq)
{
    if (dq.empty())
        return x;
    return std::max(x, a[dq.front()]);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n;
    for (auto i = 0; i < n; i++)
        std::cin >> a[i];

    std::deque<int> dq;
    dq.emplace_back(0);
    auto j = 1;
    for (auto i = 0; i < n; i++) {
        while (j < n && 2 * a[j] >= get_max(-1, dq)) {
            while (!dq.empty() && a[j] >= a[dq.back()])
                dq.pop_back();
            dq.emplace_back(j);
            j++;
        }
        right[i] = j - 1;
        if (dq.front() == i)
            dq.pop_front();
    }

    right_max[n - 1] = a[n - 1];
    for (auto i = n - 2; i >= 0; i--)
        right_max[i] = std::max(right_max[i + 1], a[i]);

    dq.clear();
    j = 0;
    for (auto i = 0; i < n; i++) {
        while (j < n && 2 * a[j] >= get_max(right_max[i], dq)) {
            while (!dq.empty() && a[j] >= a[dq.back()])
                dq.pop_back();
            dq.emplace_back(j);
            j++;
        }
        right2[i] = j - 1;
    }


    // for (auto i = 0; i < n; i++)
    //     std::cout << right[i] << " ";
    // std::cout << "\n";


    for (auto i = 0; i < n; i++) {
        if (right[i] == n - 1) {
            if (right2[i] == n - 1) {
                if (right2[0] == n - 1)
                    ans[i] = -1;
                else
                    ans[i] = n - i + n + right2[0] + 1;
            } else {
                ans[i] = n - i + right2[i] + 1;
            }
        } else {
            ans[i] = right[i] - i + 1;
        }
        std::cout << ans[i] << " ";
    }
    std::cout << "\n";

}

