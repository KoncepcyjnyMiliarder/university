#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <iomanip>
/*
5 11 23
1 2 3
2 3 4
3 4 5
4 5 6
1 3 4
2 4 5
3 5 6
1 4 2
2 5 3
1 5 2
3 2 30
*/

//implementacje algorytmu dinica znalazlem w internecie
const int inf = 1071026353;
int n, m, que[233], dis[233];
int to[2333], pre[2333], c[2333], last[233], cur[233], en;

inline void clear()
{
  en = 1;
  memset(last, 0, sizeof last);
}

inline void addedge(int f, int t, int fl)
{
  to[++en] = t;
  c[en] = fl;
  pre[en] = last[f];
  last[f] = en;
  to[++en] = f;
  c[en] = 0;
  pre[en] = last[t];
  last[t] = en;
}

bool bfs()
{
  memset(dis, -1, sizeof dis);
  int h, r, now;
  que[h = r = 0] = n;
  dis[n] = 0;
  while (h <= r)
  {
    now = que[h++];
    for (int i = last[now]; i; i = pre[i])
    {
      if (c[i ^ 1] && dis[to[i]] == -1)
      {
        dis[to[i]] = dis[now] + 1;
        que[++r] = to[i];
      }
    }
  }
  return dis[1] != -1;
}

int dfs(int now, int flow)
{
  if (now == n)
    return flow;
  int ret = 0, tmp;
  for (int i = cur[now]; i; i = pre[i])
  {
    cur[now] = i;
    if (c[i] && dis[to[i]] + 1 == dis[now])
    {
      tmp = dfs(to[i], std::min(flow - ret, c[i]));
      ret += tmp;
      c[i] -= tmp;
      c[i ^ 1] += tmp;
      if (ret == flow)
        break;
    }
  }
  return ret;
}

int dinic()
{
  int ret = 0;
  while (bfs())
  {
    memcpy(cur, last, sizeof last);
    ret += dfs(1, inf);
  }
  return ret;
}
//koniec

struct edge
{
  int from, to, weight;
};

int main()
{
  int x;
  std::cin >> n >> m >> x;
  std::vector<edge> edges(m);
  for (auto& e : edges)
    std::cin >> e.from >> e.to >> e.weight;

  double upper_bound = std::max_element(edges.begin(), edges.end(), [](const edge & less, const edge & e)
  {
    return less.weight < e.weight;
  })->weight;

  double lower_bound = 0, middle;
  double epsilon = 1e-9;
  //while ((upper_bound - lower_bound) * x / std::max(upper_bound, 1.0) > epsilon)
  while (upper_bound - lower_bound > epsilon)
  {
    middle = (lower_bound + upper_bound) / 2;
    clear();
    for (auto& e : edges)
      addedge(e.from, e.to, e.weight / middle);
    if (dinic() >= x)
      lower_bound = middle;
    else
      upper_bound = middle;
  }
  middle *= x;
  if (middle < 1.0)
    middle = 1.0;
  std::cout << std::setprecision(10) << middle;
  return 0;
}