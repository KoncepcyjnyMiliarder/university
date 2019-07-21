#include <iostream>

int main()
{
  bool tab[1001] = {};
  int n, m;
  scanf("%d%d", &n, &m);
  for (int i = 1; i <= m; ++i)
  {
    int from, to;
    scanf("%d%d", &from, &to);
    tab[from] = true;
    tab[to] = true;
  }
  for (int i = 1; i <= n; ++i)
  {
    if (tab[i] == false)
    {
      printf("%d\n", n - 1);
      for (int k = 1; k <= n; ++k)
      {
        if (k != i)
          printf("%d %d\n", i, k);
      }
      return 0;
    }
  }
}