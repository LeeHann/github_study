#include <stdio.h>

int main(){
  char a = 0x12, b = 0x34;
  short c = 0x5678;

  int *pt;
  pt = &a;

  printf("%x \n", pt);

  return 0;
}