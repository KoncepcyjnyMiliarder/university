#include <iostream>

unsigned long long most_significant_bit(unsigned long long val)
{
  unsigned long long res = 1;
  while (val)
  {
    res <<= 1;
    val >>= 1;
  }
  return res;
}

int main()
{
  unsigned long long l, r;
  std::cin >> l >> r;
  if (l == r)
  {
    puts("0");
    return 0;
  }
  std::cout << most_significant_bit(l ^ r) - 1 << std::endl;
  return 0;
}