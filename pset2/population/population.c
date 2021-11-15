#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
    // TODO: Prompt for start size
  int a;
  do
  {
      a = get_int("Starting population size: ");
  }
  while (a < 9);

    // TODO: Prompt for end size
    int b;
  do
  {
      b = get_int("Ending population size: ");
  }
  while (b < a);

    // TODO: Calculate number of years until we reach threshold
   int n =0;
   int pop=a;
   if (a!=b){
     do
   {
     pop=pop-pop/4+pop/3;
     n++;
   }
   while (pop<b);

   }
   

    // TODO: Print number of years
    printf("Years: %i\n", n);
}