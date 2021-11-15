#include <cs50.h>
#include <stdio.h>

int main(void)
{
  int a;
  do
  {
      a = get_int("Height: ");
  }
  while (a < 1||a>100);
  
  for (int i=0; i<a;i++){
      for(int j=0; j<a-i-1;j++)
      {
          printf(" ");
      }
      for(int k=0; k<i+1;k++)
      {
          printf("#");
      }
      printf("  ");
      for(int k=0; k<i+1;k++)
      {
          printf("#");
      }
      printf("\n");
  }

}