#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

int attempt_with_def(const std::vector<int>& jiro_atk, const std::vector<int>& jiro_def, std::vector<int>& ciel)
{
  auto it = ciel.begin();
  for (const auto& jdef : jiro_def)
  {
    while (*it <= jdef && it != ciel.end()) ++it;
    if (it == ciel.end())
    {
      //printf("papa1\n");
      return 0;
    }
    it = ciel.erase(it);
  }
  it = ciel.begin();
  int res = 0;
  for (const auto& jatk : jiro_atk)
  {
    while (*it < jatk && it != ciel.end()) ++it;
    if (it == ciel.end())
    {
      //printf("papa2\n");
      return res;
    }
    res += *it - jatk;
    ciel.erase(it);
  }
  return std::accumulate(ciel.begin(), ciel.end(), res);
}

int attempt_atk_only(const std::vector<int>& jiro_atk, const std::vector<int>& ciel)
{
  int res = 0;
  auto ciel_it = ciel.rbegin();
  auto jiro_it = jiro_atk.begin();
  while(ciel_it != ciel.rend() && jiro_it != jiro_atk.end())
  {
    int profit = *ciel_it - *jiro_it;
    if (profit <= 0)
      return res;
    res += profit;
    ++ciel_it;
    ++jiro_it;
  }
  return res;
}

int main()
{
  int n, m; //jiro n, ciel m, ciel atakuje
  scanf("%d%d", &n, &m);
  std::vector<int> ciel(m);
  std::vector<int> jiro_atk;
  std::vector<int> jiro_def;
  jiro_atk.reserve(n);
  jiro_def.reserve(n);

  for (int i = 0; i < n; i++)
  {
    char position[4];
    int strength;
    scanf("%s%d", position, &strength);
    if (position[0] == 'A')
      jiro_atk.push_back(strength);
    else
      jiro_def.push_back(strength);
  }
  std::sort(jiro_atk.begin(), jiro_atk.end());
  std::sort(jiro_def.begin(), jiro_def.end());

  for (int i = 0; i < m; i++)
    scanf("%d", &ciel[i]);
  std::sort(ciel.begin(), ciel.end());

  int maxval = attempt_atk_only(jiro_atk, ciel);
  if (n <= m)
    maxval = std::max(maxval, attempt_with_def(jiro_atk, jiro_def, ciel));

  printf("%d\n", maxval);
  return 0;
}