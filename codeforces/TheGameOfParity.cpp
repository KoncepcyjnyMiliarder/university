#include <iostream>

int main()
{
  int n, k;
  scanf("%d%d", &n, &k);
  int even = 0;
  int odd = 0;
  for (int i = 0; i < n; ++i)
  {
    int a;
    scanf("%d", &a);
    (a % 2 == 0) ? ++even : ++odd;
  }

  int to_kill = n - k;
  if (to_kill == 0)
  {
    puts(odd % 2 ? "Stannis" : "Daenerys");
    return 0;
  }

  if (k % 2)
  {
    if ((even <= odd && to_kill / 2 >= even) || (to_kill % 2 && to_kill / 2 < odd))
      puts("Stannis");
    else
      puts("Daenerys");
    return 0;
  }
  if (even > odd)
    even = odd;
  if (to_kill % 2 && to_kill / 2 < even)
    puts("Stannis");
  else
    puts("Daenerys");
  return 0;
}