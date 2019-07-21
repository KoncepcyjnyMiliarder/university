#include <iostream>
#include <string>

void do_the_trick(const std::string& s)
{
  for (int i = 0; i < s.size() / 2; ++i)
  {
    int diff = s[i] - s[s.size() - 1 - i];
    if (diff > 2 || diff < -2 || diff == 1 || diff == -1)
    {
      std::cout << "NO\n";
      return;
    }
  }
  std::cout << "YES\n";
}

int main()
{
  int t;
  std::cin >> t;
  while (t--)
  {
    unsigned n;
    std::cin >> n;
    std::string s;
    std::cin >> s;
    do_the_trick(s);
  }
  return 0;
}