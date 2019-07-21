#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  int n, aa, bb;
  scanf("%d%d%d", &n, &aa, &bb);
  long long lower = aa;
  long long upper = bb;
  std::vector<std::pair<long long, long long>> samples(n);
  for(int i = 0; i < n; ++i)
  {
    int k, b;
    scanf("%d%d", &k, &b);
    samples[i].first = k * lower + b;
    samples[i].second = k * upper + b;
  }
  std::sort(samples.begin(), samples.end());
  for (int i = 1; i < n; ++i)
  {
    if (samples[i - 1].first < samples[i].first && samples[i - 1].second > samples[i].second)
    {
      printf("YES\n");
      return 0;
    }
  }
  printf("NO\n");
  return 0;
}