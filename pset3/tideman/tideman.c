#include <cs50.h>
#include <stdio.h>
#include <strings.h>

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
int size_pairs;
// Array of candidates
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

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: tideman [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
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
/*
    for (int i = 0; i < candidate_count; i++) {
        for (int j = 0; j < candidate_count; j++) {
                printf("%i ", preferences[i][j]);
        }
        printf("\n");
    }
*/
    add_pairs();
    sort_pairs();
    lock_pairs();
    print_winner();
    return 0;
}

// Update ranks given a new vote
bool vote(int rank, string name, int ranks[])
{
    for (int i = 0; i < candidate_count; i++) {
        if (strcasecmp(name, candidates[i]) == 0) {
            ranks[rank] = i;
            return true;
        }
    }

    return false;
}

// Update preferences given one voter's ranks
void record_preferences(int ranks[])
{

    for (int i = 0; i < candidate_count; i++) {
        for (int j = i; j < candidate_count; j++) {
            if (i == j) {
                preferences[i][j] = 0;
            }
            else {
                preferences[ranks[i]][ranks[j]] += 1;
            }
        }
    }

    return;
}

// Record pairs of candidates where one is preferred over the other
void add_pairs(void)
{
    for (int k = 0; k < (candidate_count * (candidate_count - 1) / 2); k++) {
        pairs[k].winner = 0;
        pairs[k].loser = 0;
    }


    int c = 0;
    for (int i = 0; i < candidate_count; i++) {

        for (int j = i + 1; j < candidate_count; j++) {

            if (preferences[i][j] > preferences[j][i]) {
                pairs[c].winner = i;
                pairs[c].loser = j;
                c = c + 1;
            }

            if (preferences[i][j] < preferences[j][i]) {
                pairs[c].winner = j;
                pairs[c].loser = i;
                c = c + 1;
            }
        }
    }

   size_pairs = c;
    //printf("%i\n", size_pairs);

/*
    for (int k = 0; k < size_pairs; k++) {
        printf("%i (%i,%i)\n",k,pairs[k].winner,pairs[k].loser);
    }
*/
    return;
}

// Sort pairs in decreasing order by strength of victory
void sort_pairs(void)
{
    int menor, maior;

    for (int i = 0; i < size_pairs - 1; i++) {
        maior = preferences[pairs[i].winner][pairs[i].loser];
        menor = 0;
        for (int j = i + 1; j < size_pairs; j++ ) {
           if (preferences[pairs[j].winner][pairs[j].loser] > maior) {
                maior = preferences[pairs[j].winner][pairs[j].loser];
                menor = preferences[pairs[i].winner][pairs[i].loser];
                preferences[pairs[i].winner][pairs[i].loser] = maior;
                preferences[pairs[j].winner][pairs[j].loser] = menor;
           }
        }

    }
/*
    for (int k = 0; k < size_pairs; k++) {
        printf("pos %i winner %i loser %i preferencia de i sobre j %i\n",k,pairs[k].winner,pairs[k].loser, preferences[pairs[k].winner][pairs[k].loser]);
    }
*/
    return;
}

// Lock pairs into the candidate graph in order, without creating cycles
void lock_pairs(void) // TÁ TUDO ERRADO A PARTIR DAQUI!!!
{
    for (int i = 0; i < size_pairs; i++) {
        locked[pairs[i].winner][pairs[i].loser] = true;
    }

 /*   for (int i = 0; i < candidate_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            printf("%d ",locked[i][j]);
        }
        printf("\n");
    }
*/
    return;
}

// Print the winner of the election
void print_winner(void)
{
    int cont_seta = 0;
    int winner;
    for (int i = 0; i < candidate_count; i++) {
        cont_seta = 0;
        for (int j = 0; j < candidate_count; j++) {
            if (locked[j][i] == true) {
                cont_seta++;
            }
        }
        if (cont_seta == 0) {
            winner = i;
        }
    }

    printf("%s\n", candidates[winner]);
    return;
}

