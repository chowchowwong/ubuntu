#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int compute_read(string word);

int main(void)
{
    // Get input string from user
    string word = get_string("Text: ");
    

    // Compute the readability index
    int index = compute_read(word);
   
    // TODO: Print the result
    if (index>=16)
    {
        printf("Grade 16+\n");
    }
    else if (index<1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n",index);
    }
}

int compute_read(string word)
{
    int index;
    int letterno=0;
    int wordno=1;
    int sentno=0;
    for (int i =0; i<strlen(word);i++)
    {
        if ((word[i]>= 'a' && word[i]<='z')||(word[i]>='A' && word[i]<='Z'))
        {
            letterno++;
        }
        else if (word[i]==' ' && i!=strlen(word)-1)
        {
            wordno++;
        }
        else if(word[i]=='.' ||word[i]=='!'||word[i]=='?')
        {
            sentno++;
        }
    }
    index = round(100*0.0588 * letterno / wordno - 100*0.296 * sentno / wordno - 15.8);
    //printf("%i letter(s)\n%i word(s)\n%i sentence(s)\nindex: %i\n",letterno,wordno,sentno,index);
    return index;
}