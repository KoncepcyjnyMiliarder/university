#include <iostream>

int main()
{
  int n;
  //holds parent of vertex, except for 0 and max
  int parents[1001] = {};
  //holds count of occurences as min in input pairs, means how many edges vertice is from source (max)
  int distance_from_source[1001] = {};
  scanf("%d", &n);
  for (int i = 0; i < n - 1; ++i)
  {
    int max_a, max_b;
    scanf("%d%d", &max_a, &max_b);
    if (max_b != n || max_a >= n || max_a < 1)
    {
      printf("NO");
      return 0;
    }
    ++distance_from_source[max_a];
  }
  //stack-like temp thingy, im aimin for 0 dynamic alloc :D
  //always ascending
  int unused_values[1001] = {};
  int unused_size = 0;
  for (int i = 1; i < n; ++i)
  {
    if (distance_from_source[i] == 0)
      unused_values[unused_size++] = i;
    else
    {
      if (distance_from_source[i] - 1 > unused_size)
      {
        printf("NO");
        return 0;
      }
      int current_vert = i;
      while (distance_from_source[i]-- > 1)
      {
        int next_vert = unused_values[--unused_size];
        parents[current_vert] = next_vert;
        current_vert = next_vert;
      }
      parents[current_vert] = n;
    }
  }
  if(unused_size != 0)
  {
    printf("NO");
    return 0;
  }
  printf("YES\n");
  for (int i = 1; i < n; ++i)
    printf("%d %d\n", i, parents[i]);
  return 0;
}