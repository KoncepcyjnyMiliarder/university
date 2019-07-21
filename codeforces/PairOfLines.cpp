#include <iostream>
#include <algorithm>

struct line
{
  long long start_x;
  long long start_y;
  long long step_x;
  long long step_y;
};

int gcd(long long a, long long b)
{
  if (a < 0)
    a *= -1;
  if (b < 0)
    b *= -1;
  if (a < b)
    std::swap(a, b);
  while (a % b)
  {
    auto c = a % b;
    a = b;
    b = c;
  }
  return b;
}

line make_line(long long first_x, long long first_y, long long second_x, long long second_y)
{
  if (first_x == second_x)
    return { first_x, 0, 0, 1 };
  if (first_y == second_y)
    return { 0, first_y, 1, 0 };
  auto delta_x = second_x - first_x;
  auto delta_y = second_y - first_y;
  if (delta_x < 0)
  {
    delta_x *= -1;
    delta_y *= -1;
  }
  auto delta_gcd = gcd(delta_x, delta_y);
  return { first_x, first_y, delta_x / delta_gcd, delta_y / delta_gcd };
}

bool belongs(const line& l, long long x, long long y)
{
  if (l.step_x == 0)
    return x == l.start_x;
  if (l.step_y == 0)
    return y == l.start_y;
  auto delta_x = x - l.start_x;
  auto delta_y = y - l.start_y;
  return (delta_x % l.step_x == 0 && delta_y % l.step_y == 0 && delta_x / l.step_x == delta_y / l.step_y);
}

enum optional_line_status
{
  no_point,
  one_point,
  found
};

int main()
{
  int n;
  scanf("%d", &n);
  if (n <= 4)
  {
    puts("YES");
    return 0;
  }
  long long first_x, first_y, second_x, second_y, third_x, third_y;
  scanf("%I64d%I64d%I64d%I64d%I64d%I64d", &first_x, &first_y, &second_x, &second_y, &third_x, &third_y);
  line original_line = make_line(first_x, first_y, second_x, second_y);
  line optional_line;
  long long optional_x;
  long long optional_y;
  int loop_start = 3;
  optional_line_status optst = no_point;
  if (!belongs(original_line, third_x, third_y))
  {
    loop_start = 4;
    long long fourth_x, fourth_y;
    scanf("%I64d%I64d", &fourth_x, &fourth_y);
    if (belongs(original_line, fourth_x, fourth_y))
    {
      optst = one_point;
      optional_x = third_x;
      optional_y = third_y;
    }
    else if (belongs(original_line = make_line(first_x, first_y, third_x, third_y), fourth_x, fourth_y))
    {
      optst = one_point;
      optional_x = second_x;
      optional_y = second_y;
    }
    else if (belongs(original_line = make_line(second_x, second_y, third_x, third_y), fourth_x, fourth_y))
    {
      optst = one_point;
      optional_x = first_x;
      optional_y = first_y;
    }
    else
    {
      optst = found;
      loop_start = 5;
      long long fifth_x, fifth_y;
      scanf("%I64d%I64d", &fifth_x, &fifth_y);
      original_line = make_line(first_x, first_y, second_x, second_y);
      optional_line = make_line(third_x, third_y, fourth_x, fourth_y);
      if (!belongs(original_line, fifth_x, fifth_y) && !belongs(optional_line, fifth_x, fifth_y))
      {
        original_line = make_line(first_x, first_y, third_x, third_y);
        optional_line = make_line(second_x, second_y, fourth_x, fourth_y);
        if (!belongs(original_line, fifth_x, fifth_y) && !belongs(optional_line, fifth_x, fifth_y))
        {
          original_line = make_line(first_x, first_y, fourth_x, fourth_y);
          optional_line = make_line(second_x, second_y, third_x, third_y);
          if (!belongs(original_line, fifth_x, fifth_y) && !belongs(optional_line, fifth_x, fifth_y))
          {
            puts("NO");
            return 0;
          }
        }
      }
    }
  }
  for (int i = loop_start; i < n; ++i)
  {
    long long x, y;
    scanf("%I64d%I64d", &x, &y);
    switch (optst)
    {
      case no_point:
        if (!belongs(original_line, x, y))
        {
          optional_x = x;
          optional_y = y;
          optst = one_point;
        }
        break;
      case one_point:
        if (!belongs(original_line, x, y))
        {
          optional_line = make_line(optional_x, optional_y, x, y);
          optst = found;
        }
        break;
      case found:
        if (!belongs(original_line, x, y)
            && !belongs(optional_line, x, y))
        {
          puts("NO");
          return 0;
        }
        break;
    }
  }
  puts("YES");
  return 0;
}