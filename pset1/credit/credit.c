#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{
  long a;
  do
  {
      a = get_long("Number: ");
  }
  while(a<0);
  //while (a < 4000000000000||a>=5600000000000000);
  // if (a < 4000000000000||a>=5600000000000000)
  // {
  //   printf("INVALID\n");
  // }
  int n;
  if (a>=4000000000000000&&a<5600000000000000){
    n=16;
  }
  else if (a>=340000000000000){
    n=15;
  }
  else if (a>=4000000000000){
    n=13;
  }
  else
  {
    n=0;
    printf("INVALID\n");
  }
  int digits[n];
  long temp = a;
  for (int i = n-1; i>=0;i--){
    digits[i]=temp%10;
    temp = (temp - digits[i])/10;
  }
  int check[n];
  check[0]=0;
  int b;
  int sum1=digits[n-1];
  for (int i=n-2; i>=0; i-=2)
  {
    if(i-1>=0)
    {
      sum1+=digits[i-1];
    }
    // printf("%i\n",sum1);
    b = digits[i]*2;
    for (int j = 0; j<2;j++)
    {
    check[i+j]=b%10;
    b = (b - check[i+j])/10;
    }
  }
  int sum2=0;
  for (int i=0; i<n;i++)
  {
    sum2+=check[i];
  }
  if ((sum1+sum2)%10==0)
  {
    if((n==13||n==16)&&digits[0]==4)
    {
      printf("VISA\n");
    }
    else if (n==15&&digits[0]==3&&(digits[1]==4||digits[1]==7))
    {
      printf("AMEX\n");
    }
    else if(n==16&&digits[0]==5&&(digits[1]==1||digits[1]==2||digits[1]==3||digits[1]==4||digits[1]==5))
    {
      printf("MASTERCARD\n");
    }
    else
    {
      printf("INVALID\n");
    }
  }
    else
    {
      printf("INVALID\n");
    }


  // printf("digits\n");
  // for (int i=0;i<n;i++)
  // {
  //   printf("%i\n",digits[i]);
  // }
  // printf("check\n");
  // for (int i=0;i<n;i++)
  // {
  //   printf("%i\n",check[i]);
  // }
  // printf("sum1:%i\nsum2:%i\n",sum1,sum2);

}