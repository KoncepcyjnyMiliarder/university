#include <iostream>
#include <cmath>

int buf[3001] = {};

bool isprime(int val)
{
  int root = sqrt(val) + 1;
  for (int i = 2; i < root; ++i)
    if (val % i == 0)
      return false;
  return true;
}

int main()
{
  int n;
  std::cin >> n;
  if (n < 4)
  {
    std::cout << 0 << std::endl;
    return 0;
  }
  for (int i = 2; i < n + 1; ++i)
  {
    if (!isprime(i))
      continue;
    for (int k = 0; k < 3000; k += i)
      ++buf[k];
  }
  int sum = 0;
  for (int i = 4; i <= n; ++i)
    if (buf[i] == 2)
      ++sum;
  std::cout << sum << std::endl;
}