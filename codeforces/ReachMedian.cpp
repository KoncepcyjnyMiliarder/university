#include <iostream>
#include <vector>
#include <algorithm>

int main()
{
  unsigned n, s;
  scanf("%u%u", &n, &s);
  std::vector<unsigned> numbers(n);
  for(auto& elem : numbers)
    scanf("%d", &elem);
  std::sort(numbers.begin(), numbers.end());
  auto mid_iter = numbers.begin() + numbers.size() / 2;
  if (*mid_iter == s)
  {
    puts("0");
    return 0;
  }
  unsigned long long counter = 0;
  for (auto iter = numbers.begin(); iter != mid_iter; ++iter)
    if (*iter > s)
      counter += *iter - s;
  //printf("%u %u\n", *mid_iter, s);
  counter += *mid_iter > s ? *mid_iter - s : s - *mid_iter;
  for (auto iter = mid_iter + 1; iter != numbers.end(); ++iter)
    if (*iter < s)
      counter += s - *iter;
  //printf("%llu\n", counter);
  std::cout << counter << std::endl;
  return 0;
}