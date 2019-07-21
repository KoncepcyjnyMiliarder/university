#include <vector>
#include <iostream>
#include <queue>

int hokus_pokus(const std::vector<std::vector<bool>>& is_railway, bool road_type)
{
  std::vector<int> distance(is_railway.size(), 0);
  distance[0] = 1;
  std::queue<int> to_visit;
  to_visit.push(0);
  while (!to_visit.empty())
  {
    int top = to_visit.front();
    to_visit.pop();
    for (int i = 0; i < is_railway.size(); ++i)
    {
      if (distance[i] == 0 && is_railway[top][i] == road_type)
      {
        to_visit.push(i);
        //printf("Jade z %d to %d disttop %d\n", top, i, distance[top]);
        distance[i] = distance[top] + 1;
      }
    }
  }
  return distance.back() ? distance.back() - 1 : -1;
}

int main()
{
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<bool>> is_railway(n, std::vector<bool>(n));
  while (m--)
  {
    int u, v;
    std::cin >> u >> v;
    --u;
    --v;
    is_railway[u][v] = true;
    is_railway[v][u] = true;
  }
  std::cout << (is_railway[0][n - 1] ? hokus_pokus(is_railway, false) : hokus_pokus(is_railway, true)) << std::endl;
}