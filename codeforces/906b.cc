// ml:run = $bin < input
#include <iostream>
#include <algorithm>
#include <vector>

std::vector<int> ans;
std::vector<int> in;
std::vector<int> out;
int n, m;

void transform(int now, int m)
{
    for (int i = 0; i < m; i++) {
        if (i & 1)
            out[i / 2] = in[i];
        else
            out[i / 2 + m / 2] = in[i];
    }
    if (now & 1) return;
    if (m & 1) {
        for (auto i = 1; i < m; i++)
            std::swap(out[i], out[i - 1]);
    } else {
        for (int i = 0; i < m/2; i++)
            std::swap(out[i], out[m - i - 1]);
    }
}

void work(int n, int m, int d, bool ver)
{
    in.resize(m);
    out.resize(m);
    for (int i = 1; i <= n; i++) {
        int start = ver ? i : (i - 1) * m + 1;
        for (int j = 0; j < m; j++)
            in[j] = start + j * d;
        transform(i, m);

        for (int j = 0; j < m; j++)
            if (ver) {
                ans[j * n + i - 1] = out[j];
            } else {
                ans[(i - 1) * m + j] = out[j];
            }
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin >> n >> m;
    if (n == m && n == 1) {
        std::cout << "YES\n1\n";
        return 0;
    }
    if (n == m && n == 3) {
        std::cout << "YES\n";
        std::cout <<
            "8 1 6\n"
            "3 5 7\n"
            "4 9 2\n";
        return 0;
    }
    if (n <= 3 && m <= 3) {
        std::cout << "NO\n";
        return 0;
    }

    std::cout << "YES\n";
    ans.resize(n * m);
    if (m <= 3)
        work(m, n, m, 1);
    else
        work(n, m, 1, 0);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++)
            std::cout << ans[i * m + j] << " ";
        std::cout << "\n";
    }
}

