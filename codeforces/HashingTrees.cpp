#include <iostream>
#include <vector>

int main()
{
  int h;
  scanf("%d", &h);
  std::vector<int> verts_on_each_level(h + 1);
  scanf("%d", &verts_on_each_level[0]);
  int ambigious_level = 0;
  for (int i = 1; i < h + 1; ++i)
  {
    scanf("%d", &verts_on_each_level[i]);
    if (ambigious_level == 0 && verts_on_each_level[i - 1] > 1 && verts_on_each_level[i] > 1)
      ambigious_level = i;
  }
  if (ambigious_level == 0)
  {
    puts("perfect");
    return 0;
  }
  puts("ambiguous");
  //every next node rooted to first possible
  int previous_root = 0;
  for (int i = 0; i < h + 1; ++i)
  {
    for (int k = 0; k < verts_on_each_level[i]; ++k)
      printf("%d ", previous_root);
    previous_root += verts_on_each_level[i];
  }
  putchar('\n');
  //on ambigious level put first to other than the rest
  previous_root = 0;
  for (int i = 0; i < h + 1; ++i)
  {
    if (i == ambigious_level)
    {
      printf("%d ", previous_root);
      for (int k = 1; k < verts_on_each_level[i]; ++k)
        printf("%d ", previous_root - 1);
    }
    else
    {
      for (int k = 0; k < verts_on_each_level[i]; ++k)
        printf("%d ", previous_root);
    }
    previous_root += verts_on_each_level[i];
  }
  putchar('\n');
  return 0;
}