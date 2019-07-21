#include <iostream>
#include <algorithm>
#include <cmath>

struct circle
{
  long long x, y, r;
};

long double count_piece(long double r2, long double dist_sq, long double r1)
{
  long double alpha = std::acos((r2 * r2 + dist_sq - r1 * r1) / (2.0 * r2 * std::sqrt(dist_sq)));
  //printf("ALPHA %.10Lf\n", alpha);
  long double s = alpha * r2 * r2;
  //printf("S %.10Lf\n", s);
  long double t = r2 * r2 * std::sin(alpha) * std::cos(alpha);
  //printf("T %.10Lf\n", t);
  return s - t;
}

int main()
{
  constexpr double pi = 3.141592653589793238463;
  circle a, b;
  scanf("%I64d%I64d%I64d%I64d%I64d%I64d", &a.x, &a.y, &a.r, &b.x, &b.y, &b.r);
  if (a.r < b.r)
    std::swap(a, b);
  auto dist_sq = (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
  if (dist_sq >= (a.r + b.r) * (a.r + b.r))
  {
    puts("0");
    return 0;
  }
  if (dist_sq <= (a.r - b.r) * (a.r - b.r) || (a.x == b.x && a.y == b.y))
  {
    printf("%.10f\n", b.r * b.r * pi);
    return 0;
  }
  //count_piece(b.r, dist_sq, a.r)
  //count_piece(b.r, dist_sq, a.r)
  printf("%.10f\n", (double)(count_piece(b.r, dist_sq, a.r) + count_piece(a.r, dist_sq, b.r)));
  return 0;
}