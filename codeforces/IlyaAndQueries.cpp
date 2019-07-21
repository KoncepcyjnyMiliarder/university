#include <iostream>
#include <string>
#include <vector>

int main()
{
  std::string text;
  std::cin >> text;
  std::vector<unsigned> repeats(text.size());
  for (unsigned i = 1; i < repeats.size(); ++i)
    repeats[i] = repeats[i - 1] + (text[i] == text[i - 1] ? 1 : 0);
  int m;
  scanf("%d", &m);
  while (m--)
  {
    int l, m;
    scanf("%d%d", &l, &m);
    printf("%u\n", repeats[m - 1] - repeats[l - 1]);
  }
  return 0;
}