#include <iostream>

unsigned long long mymax(unsigned long long a, unsigned long long b)
{
  return a > b ? a : b;
}

int main()
{
  unsigned long long n;
  std::cin >> n;
  if (n < 3)
  {
    std::cout << n;
    return 0;
  }
  if (n % 2)
  {
    std::cout << n*(n - 1)*(n - 2);
    return 0;
  }
  auto a = n * (n - 1) * (n - 2) / 2;
  auto b = (n - 3) * (n - 1) * (n - 2);
  auto c = n * (n - 1) * (n - 3);
  if (n % 3 == 0)
    c = 0;
  std::cout << mymax(mymax(a, b), c);
  return 0;
}