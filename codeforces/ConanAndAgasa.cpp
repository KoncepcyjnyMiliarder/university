#include <iostream>
#include <vector>

int main()
{
  int n;
  scanf("%d", &n);
  int tab[100001] = {};
  for(int i = 0; i < n; ++i)
  {
    int val;
    scanf("%d", &val);
    ++tab[val];
  }
  for (int i = 0; i < 100001; ++i)
  {
    if (tab[i] % 2)
    {
      puts("Conan");
      return 0;
    }
  }
  puts("Agasa");
  return 0;
}