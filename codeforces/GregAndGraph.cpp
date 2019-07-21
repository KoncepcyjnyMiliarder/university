#include <iostream>
#include <vector>

/*
4
0 3 1 1
6 0 400 1
2 4 0 1
1 1 1 0
4 1 2 3
*/

int main()
{
  int n;
  std::cin >> n;
  std::vector<std::vector<unsigned long long>> distances(n, std::vector<unsigned long long>(n));
  for (int i = 0; i < n; ++i)
    for (int k = 0; k < n; ++k)
      std::cin >> distances[i][k];
  std::vector<int> to_remove(n);
  for (int i = 0; i < n; ++i)
  {
    int val;
    std::cin >> val;
    to_remove[n - i - 1] = val - 1;
  }
  std::vector<bool> removed(n);
  std::vector<unsigned long long> distance(n);
  for (int i = 0; i < n; ++i)
  {
    int missing = to_remove[i];
    removed[missing] = true;
    for (int k = 0; k < n; ++k)
      for (int l = 0; l < n; ++l)
      {
        if (distances[k][missing] + distances[missing][l] < distances[k][l])
          distances[k][l] = distances[k][missing] + distances[missing][l];
        if (removed[k] && removed[l])
          distance[i] += distances[k][l];
      }
  }
  std::cout << distance.back();
  distance.pop_back();
  while (!distance.empty())
  {
    std::cout << ' ' << distance.back();
    distance.pop_back();
  }
}