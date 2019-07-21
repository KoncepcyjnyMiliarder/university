#include <iostream>
#include <cmath>

int main()
{
  int n, m;
  std::cin >> n >> m;
  int a_root = std::sqrt(n) + 1;
  int b_root = std::sqrt(m) + 1;
  int counter = 0;
  for (int a = 0; a < a_root; ++a)
    for (int b = 0; b < b_root; ++b)
      if (a * a + b == n && b * b + a == m)
        ++counter;
  std::cout << counter << std::endl;
  return 0;
}