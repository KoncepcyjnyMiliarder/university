#include <iostream>

int main()
{
  int r, d, n;
  scanf("%d%d%d", &r, &d, &n);
  int sum = 0;
  int lower_radius = (r - d);
  int upper_radius = r;
  while (n--)
  {
    int x, y, rad;
    scanf("%d%d%d", &x, &y, &rad);
    if (2 * rad > d)
      continue;
    int center_dist_sq = x * x + y * y;
    if (center_dist_sq >= (lower_radius + rad) * (lower_radius + rad) &&
        center_dist_sq <= (upper_radius - rad) * (upper_radius - rad))
      ++sum;
  }
  printf("%d\n", sum);
  return 0;
}