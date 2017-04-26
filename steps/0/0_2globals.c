#include <stdio.h>
 
/* global variable declaration */
int g, z;
 
int main () {

  /* local variable declaration */
  int a, b;
 
  /* actual initialization */
  a = 10;
  b = 20;
  g = a + b;
  z = a - b;
 
  printf ("value of a = %d, b = %d and g = %d, z = %d\n", a, b, g, z);
 
  return 0;
}