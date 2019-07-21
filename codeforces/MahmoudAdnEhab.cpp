#include <iostream>
#include <vector>
#include <list>

unsigned long long nodes_of_each_color[2] = {};
std::vector<char> colors;
std::vector<std::list<int>> adj_lists;

void dfs(int index, char color)
{
  colors[index] = color;
  ++nodes_of_each_color[color % 2];
  color = color % 2 + 1;
  for (const auto& e : adj_lists[index])
  {
    if (colors[e] == 0)
      dfs(e, color);
  }
}

int main()
{
  int n;
  scanf("%d", &n);
  colors.resize(n + 1);
  adj_lists.resize(n + 1);

  for (int i = 0; i < n - 1; ++i)
  {
    int u, v;
    scanf("%d%d", &u, &v);
    adj_lists[u].push_front(v);
    adj_lists[v].push_front(u);
  }
  dfs(1, 1);
  //printf("%llu\n", nodes_of_each_color[0] * nodes_of_each_color[1] - n + 1);
  std::cout << nodes_of_each_color[0] * nodes_of_each_color[1] - n + 1;
}