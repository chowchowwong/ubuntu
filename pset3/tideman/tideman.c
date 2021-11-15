#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>


// Max number of candidates
#define MAX 9

// preferences[i][j] is number of voters who prefer i over j
int preferences[MAX][MAX];

// locked[i][j] means i is locked in over j
bool locked[MAX][MAX];

// Each pair has a winner, loser
typedef struct
{
    int winner;
    int loser;
}
pair;

// haha of candidates
string candidates[MAX];
pair pairs[MAX * (MAX - 1) / 2];

int pair_count;
int candidate_count;

// Function prototypes
bool vote(int rank, string name, int ranks[]);
void record_preferences(int ranks[]);
void add_pairs(void);
void sort_pairs(void);
void lock_pairs(void);
void print_winner(void);
void mergesort(pair haha[], int start, int end);
bool is_cycle(int winner,int loser);


int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate haha of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX)
    {
        printf("Maximum number of candidates is %i\n", MAX);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i] = argv[i + 1];
    }

    // Clear graph of locked in pairs
    for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            locked[i][j] = false;
        }
    }

    pair_count = 0;
    int voter_count = get_int("Number of voters: ");

    // Query for votes
    for (int i = 0; i < voter_count; i++)
    {
        // ranks[i] is voter's ith preference
        int ranks[candidate_count];

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            if (!vote(j, name, ranks))
            {
                printf("Invalid vote.\n");
                return 3;
            }
        }

        record_preferences(ranks);

        printf("\n");
    }

    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    // TODO
    for (int i=0;i<candidate_count;i++)
    {
        if (strcmp(name, candidates[i])==0)
        {
            ranks[rank]=i;
            return true;
        }
    }
    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{
    // TODO
    for (int i=0;i<candidate_count;i++)
    {
        for(int j=i+1;j<candidate_count;j++)
        {
            preferences[ranks[i]][ranks[j]]++;
            //testing
            // printf("preferences[%i][%i]:%i\n",ranks[i],ranks[j],preferences[ranks[i]][ranks[j]]);
            // for(int a=0;a<candidate_count;a++)
            // {
            //     for(int b=0;b<candidate_count;b++)
            //     {
            //         printf("%i__",preferences[a][b]);
            //     }
            //     printf("\n");
            // }
            //testing
        }
    }
    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    // TODO
    for (int i=0;i<candidate_count;i++)
    {
        for(int j=i+1;j<candidate_count;j++)
        {
            if (preferences[i][j]>preferences[j][i])
            {
                pairs[pair_count].winner=i;
                pairs[pair_count].loser=j;
                pair_count++;
            }
            else if (preferences[i][j]<preferences[j][i])
            {
                pairs[pair_count].winner=j;
                pairs[pair_count].loser=i;
                pair_count++;
            }
        }
    }
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    // TODO
    for (int i=0;i<pair_count;i++)
    {
        printf("pair[%i].winner: %i  pair[%i].loser: %i\n",i,pairs[i].winner,i,pairs[i].loser);
    }
    mergesort(pairs,0,pair_count-1);
    for (int i=0;i<pair_count;i++)
    {
        printf("pair[%i].winner: %i  pair[%i].loser: %i\n",i,pairs[i].winner,i,pairs[i].loser);
    }
    return;
}

void mergesort(pair haha[], int start, int end)
{
    if (end>start)
    {
        int median = floor((start+end)/2);
        mergesort(haha,start,median);
        mergesort(haha,median+1, end);
        int i,j,k;
        pair left[median-start+1],right[end-median];
        for(int a=0;a<=median-start;a++)
        {
            left[a]=haha[start+a];
        }
        for(int a=0;a<end-median;a++)
        {
            right[a]=haha[median+1+a];
        }
        //testing
        // printf("left:");
        // for (int a=0;a<=median-start;a++)
        // {
        //     printf("%i,%i ",left[a].winner,left[a].loser);
        // }
        // printf("\n");
        // printf("right:");
        // for (int a=0;a<end-median;a++)
        // {
        //     printf("%i,%i ",right[a].winner,right[a].loser);
        // }
        // printf("\n");
        //testing
        i=0;
        j=0;
        k=start;
        while(i<=median-start&&j<end-median)
        {
            if ((preferences[left[i].winner][left[i].loser]-preferences[left[i].loser][left[i].winner])<(preferences[right[j].winner][right[j].loser]-preferences[right[j].loser][right[j].winner]))
            {
                haha[k]=right[j];
                j++;
                k++;
            }
            else
            {
                haha[k]=left[i];
                i++;
                k++;
            }
        }
        while (i>median-start&&j<end-median)
        {
            haha[k]=right[j];
            k++;
            j++;
        }
        while (i<=median-start&&j==end-median)
        {
            haha[k]=left[i];
            k++;
            i++;
        }
        //testing
        //printf("haha:");
        // for (int a=0;a<pair_count;a++)
        // {
        //     printf("%i,%i ",haha[a].winner,haha[a].loser);
        // }
        // printf("\n");
        //testing
    }
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void)
{
    // TODO
    //testing
    // for (int a=0;a<candidate_count;a++)
    // {
    //     for(int b=0;b<candidate_count;b++)
    //     {
    //         printf("%s ",locked[a][b]?"true":"false");
    //     }
    //     printf("\n");
    // }
    // printf("\n");
    //testing
    for (int i=0;i<pair_count;i++)\
    {
        if (!is_cycle(pairs[i].winner,pairs[i].loser))
        {
            locked[pairs[i].winner][pairs[i].loser]=true;
        }
        //testing
        for (int a=0;a<candidate_count;a++)
        {
            for(int b=0;b<candidate_count;b++)
            {
                printf("%s ",locked[a][b]?"true":"false");
            }
            printf("\n");
        }
        printf("\n");
        //testing
    }
    
        
    return;
}
bool is_cycle(int winner,int loser)
{
    for(int j=0;j<candidate_count;j++)
    {
        if (locked[loser][j]==true)
        {
            if(winner ==j)
            {
                //testing
                printf("backedge: %i,%i\n j=%i\n",winner,loser,j);
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
            }
            
        }
    }
    return false;
}

// Print the winner of the election
void print_winner(void)
{
    // TODO
    int win[candidate_count];
    for (int i=0;i<candidate_count;i++)
    {
        win[i]=0;
    }
    //testing
    // for (int i=0;i<candidate_count;i++)
    // {
    //     printf("%i ",win[i]);
    // }
    // printf("\n");
    //testing
    for (int i=0;i<candidate_count;i++)
    {
        for(int j=0;j<candidate_count;j++)
        {
            if (locked[i][j]==false)
            {
                win[j]++;
            }
        }
    }
    for (int i=0;i<candidate_count;i++)
    {
        if (win[i]==candidate_count)
        {
            printf("%s\n",candidates[i]);
        }
    }
    //testing
    // for (int i=0;i<candidate_count;i++)
    // {
    //     printf("candidate count=%i\n%i\n",candidate_count,win[i]);
    // }
    //testing
    return;
}

