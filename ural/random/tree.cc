#include <iostream>
#include <ctime>
#include <vector>
#include <cstdlib>

int const maxn = 200;
int map[maxn][maxn];
int n = 20;

int main()
{
	std::srand(std::time(0));
	for (int i = 1; i <= 1; i++) {
		std::cout << n << '\n';
		std::vector<int> a;
		std::vector<int> b{1};
		for (int i = 2; i <= n; i++) a.push_back(i);
		for (int i = 1; i < n; i++) {
			int x = rand() % a.size();
			int y = rand() % b.size();
			std::cout << a[x] << ' ' << b[y] << '\n';
			b.push_back(a[x]);
			a.erase(a.begin() + x);
		}
	}
}

