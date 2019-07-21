#include <iostream>
#include <vector>

struct operation
{
  int from;
  int to;
  int val;
};

int main()
{
  int n, m, k;
  scanf("%d%d%d", &n, &m, &k);
  std::vector<long long> values(100001);
  for (int i = 0; i < n; i++)
  {
    int val;
    scanf("%d", &val);
    values[i] = val;
  }
  std::vector<operation> ops(100001);
  for (int i = 0; i < m; i++)
  {
    scanf("%d%d%d", &ops[i].from, &ops[i].to, &ops[i].val);
    --ops[i].from;
    --ops[i].to;
  }
  std::vector<int> ranges(100001);
  for (int i = 0; i < k; i++)
  {
    int x, y;
    scanf("%d%d", &x, &y);
    ++ranges[x - 1];
    --ranges[y];
  }
  long long use_count = 0;
  std::vector<long long> accumulated(100001);
  for (int i = 0; i < m; i++)
  {
    use_count += ranges[i];
    accumulated[ops[i].from] += ops[i].val * use_count;
    accumulated[ops[i].to + 1] -= ops[i].val * use_count;
  }
  long long accumulator = accumulated[0];
  printf("%I64d", accumulator + values[0]);
  for (int i = 1; i < n; i++)
  {
    accumulator += accumulated[i];
    printf(" %I64d", accumulator + values[i]);
  }
  return 0;
}