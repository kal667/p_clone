#include <stdio.h>
#include "pop_direct_branch.c"

int pow2(int x)
{
  return x*x;
}

int main ()
{
  int a = 10;
  int p;
  p = pow2(a);
  printf("pow2 of A = %d\n", p);
  return 0;
}
