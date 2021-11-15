#include <ctype.h>
#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

string sub(string arg, string word);

int main(int argc, char *argv[])
{
    if (argc>2 || argc<2)
    {
        printf("Please input only one argument.\n");
        return 1;
    }
    string arg=argv[1];
    for (int i=0;i<strlen(arg);i++)
    {
        if (islower(arg[i]))
        {
            arg[i]= toupper(arg[i]);
        }
    }
    for (int i=0;i<strlen(argv[1]);i++)
    {
        if (!(arg[i]>='A' && arg[i]<='Z'))
        {
            printf("Invalid code\n");
            return 1;
        }
        for (int j=i+1;j<26;j++)
        {
            if (arg[i]==arg[j])
            {
                printf("Repeated letter\n");
                return 1;
            }
        }
        
        if (strlen(arg)!=26)
        {
            printf("Invalid length\n");
            return 1;
        }
    }

    // Get input string from user
    string word = get_string("plaintext: ");

    // Transform word
    string cipher = sub(arg,word);

    // TODO: Print the cipherwtext
    printf("ciphertext: %s\n",cipher);
    return 0;
}

string sub(string arg, string word)
{
    int n = strlen(word);
    //printf("%i\n",n);
    //printf("%s\n",arg);
    string letter= (string)malloc(26);
    string Letter= (string)malloc(26);
    string argl= (string)malloc(26);
    strcpy(argl, arg);
    for (int i=0;i<26;i++)
    {
        argl[i]= tolower(argl[i]);
    }
    for (int i=0; i<26;i++)
    {
        letter[i]='a'+i;
        Letter[i]='A'+i;
    }
    //printf("%s\n%s\n",letter, Letter);
    //printf("%s\n%s\n",arg, argl);
    string cipher=(string)malloc(n);
    for (int i =0; i<n;i++)
    {
        if (islower(word[i]))
        {
            for (int j=0;j<26;j++)
            {
                if (word[i]==letter[j])
                {
                    cipher[i]=argl[j];
                    //printf("word[%i]: %c letter[%i]: %c\n",i,word[i],j,letter[j]);
                }
            }
        }
        else if (isupper(word[i]))
        {
            for (int j=0;j<26;j++)
            {
                if (word[i]==Letter[j])
                {
                    cipher[i]=arg[j];
                    //printf("word[%i]: %c Letter[%i]: %c\n",i,word[i],j,Letter[j]);
                }
            }
        }
        else
        {
            cipher[i]=word[i];
        }
    }
    //printf("%s\n",cipher);
    return cipher;
}