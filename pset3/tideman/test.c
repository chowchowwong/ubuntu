#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

bool is_cycle(int winner,int loser);
bool locked[4][4];
int main(void)
{
    
    for(int i=0;i<4;i++)
    {
        for(int j=0;j<4;j++)
        {
            locked[i][j]=false;
        }
    }
    int pairs[6][2];
    pairs[0][0]=0 ;
    pairs[0][1]=1 ;
    pairs[1][0]=0 ;
    pairs[1][1]=2 ;
    pairs[2][0]=0 ;
    pairs[2][1]=3 ;
    pairs[3][0]=2 ;
    pairs[3][1]=1 ;
    pairs[4][0]=1 ;
    pairs[4][1]=3 ;
    pairs[5][0]=3 ;
    pairs[5][1]=2 ;
    for (int i=0;i<6;i++)
    {
        if (is_cycle(pairs[i][0],pairs[i][1])==false)
        {
            locked[pairs[i][0]][pairs[i][1]]=true;
            printf("%s \n",is_cycle(pairs[i][0],pairs[i][1])?"true":"false");
        }
        //testing
        for (int a=0;a<4;a++)
        {
            for(int b=0;b<4;b++)
            {
                printf("%s ",locked[a][b]?"true":"false");
            }
            printf("\n");
        }
        printf("\n");
        //testing
    }
    
}
bool is_cycle(int winner,int loser)
{
    for(int j=0;j<4;j++)
    {
        if (locked[loser][j]==true)
        {
            if(winner ==j)
            {
                //testing
                printf("return true\n");
                //testing
                return true;
            }
            else
            {
               is_cycle(winner,j);
               if (is_cycle(winner,j)==true)
               {
                   return true;
               }
               else 
               {
                   return false;
               }
            }
            
        }
    }
    return false;
}