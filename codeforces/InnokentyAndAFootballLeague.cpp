#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <set>

struct team_data
{
  std::string basic_choice;
  std::string alt_choice;
  unsigned final_choice;
};

int main()
{
  int n;
  std::cin >> n;
  std::vector<team_data> teams(n);
  std::map<std::string, unsigned> basic_choice_count;
  for (int i = 0; i < n; i++)
  {
    std::string club, town;
    std::cin >> club >> town;
    club.resize(3);
    teams[i].basic_choice = club;
    ++basic_choice_count[club];
    club.resize(2);
    club += town.front();
    teams[i].alt_choice = club;
    teams[i].final_choice = 0;
  }

  std::set<std::string> used_shortcuts;
  for (auto& team : teams)
  {
    if (basic_choice_count[team.basic_choice] > 1)
    {
      team.final_choice = 2;
      if (!used_shortcuts.insert(team.alt_choice).second)
      {
        puts("NO");
        return 0;
      }
    }
  }

  while (1)
  {
    bool again = false;
    for (auto& team : teams)
    {
      if (team.final_choice == 0)
      {
        if (used_shortcuts.count(team.basic_choice) != 0)
        {
          if (used_shortcuts.count(team.alt_choice) != 0)
          {
            puts("NO");
            return 0;
          }
          team.final_choice = 2;
          used_shortcuts.insert(team.alt_choice);
          again = true;
        }
        else if (used_shortcuts.count(team.alt_choice) != 0)
        {
          team.final_choice = 1;
          used_shortcuts.insert(team.basic_choice);
          again = true;
        }
      }
    }
    if (!again)
      break;
  }

  puts("YES");
  for (auto& team : teams)
    puts((team.final_choice == 2) ? team.alt_choice.c_str() : team.basic_choice.c_str());
  return 0;
}