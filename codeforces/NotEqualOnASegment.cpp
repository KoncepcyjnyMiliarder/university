#include <iostream>
#include <vector>

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<int> values(n);
  std::vector<int> previous_different(n);
  int last_val;
  scanf("%d", &last_val);
  previous_different[0] = -1;
  values[0] = last_val;
  for (int i = 1; i < n; ++i)
  {
    int val;
    scanf("%d", &val);
    values[i] = val;
    if (val == last_val)
      previous_different[i] = previous_different[i - 1];
    else
    {
      last_val = val;
      previous_different[i] = i - 1;
    }
  }
  /*
  for (auto& e : buf)
  printf("%d ", e);
  */
  while (m--)
  {
    int l, p, x;
    scanf("%d%d%d", &l, &p, &x);
    p -= 1;
    l -= 1;
    if (values[p] != x)
    {
      printf("%d\n", p + 1);
      continue;
    }
    if (previous_different[p] == -1)
    {
      printf("-1\n");
      continue;
    }
    if (p - previous_different[p] <= p - l)
    {
      printf("%d\n", previous_different[p] + 1);
      continue;
    }
    printf("-1\n");
  }
  return 0;
}