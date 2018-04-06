// ml:run = $bin < input
#include <iostream>

double sum[1000001];

int main()
{
   int l, r;
   std::cin >> l >> r;
   for (auto i = 1; i <= r; i++)
      for (auto j = i; j <= r; j += i)
         sum[j] += i;

   double ans = sum[l] / l;
   auto pos = l;
   for (auto i = l + 1; i <= r; i++)
       if (sum[i] / i < ans) {
           ans = sum[i] / i;
           pos = i;
       }
   std::cout << pos << "\n";
}

