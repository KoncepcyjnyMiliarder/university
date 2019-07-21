

#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::string number;
  std::cin >> number;

  for (auto& elem : number)
  {
    if (elem == '0' || elem == '8')
    {
      printf("YES\n%c\n", elem);
      return 0;
    }
    elem -= '0';
  }

  while (number.size() && number.back() % 2 == 1)
    number.pop_back();

  if (number.size() < 2)
  {
    puts("NO");
    return 0;
  }

  //0 - nie moge uzyskac takiej reszty z zadnych poprzednich
  //w przeciwnym wypadku liczba, ktora daje taka wartosc
  int tab[100][8] = {};

  tab[0][number.front() % 8] = number.front();
  for (int i = 1; i < number.size(); ++i)
  {
    for (int k = 0; k < 8; ++k)
      tab[i][k] = tab[i - 1][k];
    for (int k = 0; k < 8; ++k)
    {
      if ((tab[i - 1][k] * 10 + number[i]) % 8 == 0)
      {
        printf("YES\n%d%d", tab[i - 1][k], number[i]);
        return 0;
      }
      if (tab[i - 1][k] && tab[i - 1][k] < 10)
        tab[i][(tab[i - 1][k] * 10 + number[i]) % 8] = tab[i - 1][k] * 10 + number[i];
      tab[i][number[i] % 8] = number[i];
    }
    for (int k = 0; k < 8; ++k)
    {
      if (tab[i - 1][k] && tab[i][k] > tab[i - 1][k])
        tab[i][k] = tab[i - 1][k];
      //printf("%d ", tab[i][k]);
    }
    putchar('\n');
  }
  puts("NO");
  return 0;
}