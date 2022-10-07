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

void tabulate(void)
{
    int j = 0; // eleição primeiro turno

    for (int k = 0; k < candidate_count; k++)
    {  // candidato 1

        if (candidates[k].eliminated == false)
        { // se o candidato não foi eliminado faço a contagem de votos

            for (int i = 0; i < voter_count; i++)
            { // verificar o voto de cada eleitor

                if (preferences[i][j] == k)
                {
                    candidates[k].votes++;
                }

            }

        }
        else
        { // candidato foi eliminado
            j = j + 1;

            for (int i = 0; i < voter_count; i++)
            { // verificar o voto de cada eleitor

                if (preferences[i][j] == k)
                {
                    candidates[k].votes++;
                }

            }
        }
        printf("candidato %i / votes %i\n", k, candidates[k].votes);
    }

    return;
}

//////////////////
#include <cs50.h>
#include <stdio.h>
#include <strings.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for vote
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
typedef struct
{
    string name;
    int votes;
    bool eliminated;
}
candidate;

// Array of candidates
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
int voter_count;
int candidate_count;

// Function prototypes
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    candidate_count = argc - 1;
    if (candidate_count > MAX_CANDIDATES)
    {
        printf("Maximum number of candidates is %i\n", MAX_CANDIDATES);
        return 2;
    }
    for (int i = 0; i < candidate_count; i++)
    {
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
        candidates[i].eliminated = false;
    }

    voter_count = get_int("Number of voters: ");
    if (voter_count > MAX_VOTERS)
    {
        printf("Maximum number of voters is %i\n", MAX_VOTERS);
        return 3;
    }

    // Keep querying for votes
    for (int i = 0; i < voter_count; i++)
    {

        // Query for each rank
        for (int j = 0; j < candidate_count; j++)
        {
            string name = get_string("Rank %i: ", j + 1);

            // Record vote, unless it's invalid
            if (!vote(i, j, name))
            {
                printf("Invalid vote.\n");
                return 4;
            }
        }

        printf("\n");

    }

    // Keep holding runoffs until winner exists
    while (true)
    {
        // Calculate votes given remaining candidates
        tabulate();

        // Check if election has been won
        bool won = print_winner();
        if (won)
        {
            break;
        }

        // Eliminate last-place candidates
        int min = find_min();
        bool tie = is_tie(min);

        // If tie, everyone wins
        if (tie)
        {
            for (int i = 0; i < candidate_count; i++)
            {
                if (!candidates[i].eliminated)
                {
                    printf("empate%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        eliminate(min);

        // Reset vote counts back to zero
        for (int i = 0; i < candidate_count; i++)
        {
            candidates[i].votes = 0;
        }
    }
    return 0;
}

// Record preference if vote is valid
bool vote(int voter, int rank, string name)
{
    for (int i = 0; i < candidate_count; i++) {
        if (strcasecmp(name, candidates[i].name) == 0) {
         preferences[voter][rank] = i;
         return true;
        }
    }

    return false;
}

// Tabulate votes for non-eliminated candidates - Contagem de votos
void tabulate(void)
{

    for (int i = 0; i < voter_count; i++)
    {
        int j = 0;
        if (candidates[preferences[i][j]].eliminated == false) // candidato não eliminado
        {
            candidates[preferences[i][j]].votes++;
        }
        else // Candidato eliminado
        {
            do{
                j = j + 1;
            } while (candidates[preferences[i][j]].eliminated == true);

            candidates[preferences[i][j]].votes++;

        }

    }
    for (int k = 0; k < candidate_count; k++) {
        printf("candidato %i / votes %i\n", k, candidates[k].votes);
    }

    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    string winner;

    for (int i = 0; i < candidate_count; i++)
    {

        if (candidates[i].eliminated == false)
        {
            if (candidates[i].votes > 0.5 * voter_count)
            {
                winner = candidates[i].name;
                printf("winner %s\n", winner);
                return true;
            }
        }
    }

    return false;
}

// Return the minimum number of votes any remaining candidate has
int find_min(void) {

    int min = voter_count; // o máximo de votos que o candidato pode receber corresponde ao número total de eleitores
    printf("min inicializado %i\n", min);

    for (int k = 0; k < candidate_count; k++) {
        if (candidates[k].eliminated == false) {
            if (candidates[k].votes < min) {
                min = candidates[k].votes;
            }
        }
    }
    printf("min %i\n",min);
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    int non_eliminated = 0;

    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].eliminated == false)
        {
            non_eliminated++;
        }
    }
    printf("non-eliminated %i\n", non_eliminated);

    int tie = 0;

    for (int n = 0; n < non_eliminated; n++)
    {
        if (candidates[n].votes == min)
        {
            tie++;
        }
    }
    printf("tie %i\n", tie);
    if (tie == non_eliminated)
    {
        return true;
    }
    else
    {
        return false;
    }

}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    for (int k = 0; k < candidate_count; k++)
    {
        if (candidates[k].eliminated == false)
        {
            if (candidates[k].votes == min)
            {
                candidates[k].eliminated = true;
                printf("posição candidato eliminado %i\n", k);
            }
        }
    }
    return;
}