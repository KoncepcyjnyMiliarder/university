#include <iostream>
#include <string>

int main()
{
  std::string a, b;
  std::cin >> a >> b;
  if (a == b)
  {
    std::cout << -1 << std::endl;
    return 0;
  }
  if (a.size() > b.size())
    std::cout << a.size() << std::endl;
  else
    std::cout << b.size() << std::endl;
  return 0;
}