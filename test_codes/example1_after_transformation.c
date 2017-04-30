#include <stdio.h>
#include "pop_direct_branch.c"

int g = 0;

int pow2(int x)
{
  return x*x;
}

void pow2_clone(int x)
{
  g = x*x;
  pop_direct_branch();
  return;
}

int main ()
{
  int a = 10;
  int p;
  pow2_clone(a);
  p = g;
  printf("pow2 of A = %d\n", p);
  return 0;
}
