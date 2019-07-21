#include <iostream>
#include <vector>

int main()
{
  int a, b;
  std::cin >> a;
  std::vector<unsigned> istars(a);
  for (auto& elem : istars)
    std::cin >> elem;
  std::cin >> b;
  std::vector<unsigned> jstars(b);
  for (auto& elem : jstars)
    std::cin >> elem;
  unsigned max_ratio = 0;
  unsigned max_count = 0;
  for (auto i = istars.begin(); i != istars.end(); ++i)
    for (auto j = jstars.rbegin(); j != jstars.rend(); ++j)
      if(*j % *i == 0)
      {
        unsigned val = *j / *i;
        if (val == max_ratio)
          ++max_count;
        if (val > max_ratio)
        {
          max_ratio = val;
          max_count = 1;
        }
        break;
      }
  std::cout << max_count << std::endl;
  return 0;
}