#include <unordered_set>
#include <iostream>
#include <vector>

int main()
{
  int n, m;
  scanf("%d%d", &n, &m);
  std::vector<unsigned> values(n);
  for (int i = 0; i < n; ++i)
    scanf("%d", &values[i]);
  std::unordered_set<int> numbers;
  std::vector<unsigned> repetitions(n);
  for (int i = n - 1; i >= 0; --i)
  {
    numbers.insert(values[i]);
    repetitions[i] = numbers.size();
  }
  while (m--)
  {
    int l;
    scanf("%d", &l);
    printf("%d\n", repetitions[l - 1]);
  }
  return 0;
}