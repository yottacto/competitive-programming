// ml:run = $bin < input
#include <iostream>
#include <queue>
#include <vector>

int k, p, q;

struct data
{
    int count;
    int color;
};

auto operator<(data const& lhs, data const& rhs)
{
    return lhs.count < rhs.count
        || (lhs.count == rhs.count && rhs.color == q);
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> k >> p >> q;
    auto n = 0;
    std::priority_queue<data> pq;
    for (auto i = 0; i < k; i++) {
        data tmp;
        std::cin >> tmp.count;
        n += tmp.count;
        tmp.color = i + 1;
        if (tmp.color == p)
            tmp.count--;
        if (tmp.color == q)
            tmp.count--;
        if (tmp.count)
            pq.emplace(tmp);
    }
    if (![&]() {
        std::vector<int> ans;
        ans.emplace_back(p);
        for (auto i = 0; i < n - 2; i++) {
            auto now = pq.top();
            pq.pop();
            if (now.color == p) {
                if (pq.empty())
                    return false;
                auto tnow = pq.top();
                pq.pop();
                pq.emplace(now);
                ans.emplace_back(tnow.color);
                tnow.count--;
                p = tnow.color;
                if (tnow.count)
                    pq.emplace(tnow);
            } else {
                now.count--;
                p = now.color;
                ans.emplace_back(now.color);
                if (now.count)
                    pq.emplace(now);
            }
        }
        if (ans.back() == q)
            return false;
        for (auto i : ans)
            std::cout << i << " ";
        std::cout << q;
        return true;
    }())
        std::cout << "0";
}

