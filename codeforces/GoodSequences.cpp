#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  int n;
  std::cin >> n;
  std::vector<int> vals(n);
  for (int i = 0; i < n; i++)
    std::cin >> vals[i];

  if (n == 1)
  {
    std::cout << 1;
    return 0;
  }

  std::vector<std::vector<int>> dzielniki(100001);
  std::vector<bool> czy_pierwsza(100001, true);

  for (int i = 2; i < 100001; i++)
  {
    if (!czy_pierwsza[i])
      continue;

    for (int k = i; k < 100001; k += i)
    {
      dzielniki[k].push_back(i);
      czy_pierwsza[k] = false;
    }
  }

  std::vector<int> naj(100001, 1);

  for (int i = 0; i < n; i++)
  {
    if (dzielniki[vals[i]].empty())
      continue;
    int najdluzszy = 0;
    for (const auto& dzielnik : dzielniki[vals[i]])
      if (naj[dzielnik] > najdluzszy)
        najdluzszy = naj[dzielnik];
    for (const auto& dzielnik : dzielniki[vals[i]])
      if (naj[dzielnik] < najdluzszy + 1)
        naj[dzielnik] = najdluzszy + 1;

  }
  std::cout << *std::max_element(naj.begin(), naj.end()) - 1;
  return 0;
}