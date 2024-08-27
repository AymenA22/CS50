#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
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

// Numbers of voters and candidates - Global Variables
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
                    printf("%s\n", candidates[i].name);
                }
            }
            break;
        }

        // Eliminate anyone with minimum number of votes
        // Determine the fewest number ofo votes anyone still in the election received
        // If it is a tie then return tie.
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
    // TODO
    // Count through voter and apply their name selection to the rank to position the vote
    // Keep cycling through each candidate and compare to the names in the candidate
    // Only update if the name is a match to a candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false;
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // TODO
    // Cycle through all candidates that have not been eliminated and update
    // the number of votes
    for (int i = 0; i < voter_count; i++)
    {
        for (int j= 0; j < candidate_count; j++)
        {
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break; // break out of voter to continue tablulating or else it will only count one vote
            }
        }
    }
    return;
}

// Print the winner of the election, if there is one
bool print_winner(void)
{
    // TODO
    // Check if more than half of the votes
    for (int i = 0; i < candidate_count; i++) // cycle through the candidate_count
    {
        // if the number of votes for each candidate index is more than half the voter couunt
        if (candidates[i].votes > voter_count / 2)
        {
            //print name of winning candidate
            printf("%s\n", candidates[i].name);
            return true; // exit program
        }
    }
    return false; // continue program
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // TODO
    // cycle through the candidates. If they have not been eliminated and not lower than the minimum, assign the minium to this candidate
    int min = voter_count;

    for (int i = 0; i < candidate_count; i++)
    {
        // if the name of candidates index is less than the minimum AND is not yet eliminated
        if (candidates[i].votes < min && candidates[i].eliminated == false)
        {
            // set the minimum int to the number of votes
            min = candidates[i].votes;
        }
    }
    // return min insteaad of 0 because if candidate is lower than min they are already eliminated
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // TODO
    // if the election votes is equal to the minium add one to eliminate else if equal to minimum add one to the count
    int eliminate = 0;
    int counter = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if(!candidates[i].eliminated)
        {
            eliminate++;
        }
        if (candidates[i].votes == min)
        {
            counter++;
        }
    }
    if (eliminate == counter)
    {
        return true;
    }
    return false;
}

// Eliminate the candidate (or candidates) in last place
void eliminate(int min)
{
    // TODO
    // If the total vote count is equal
    for (int i = 0; i < candidate_count; i++)
    {
        if (candidates[i].votes == min)
        {
            candidates[i].eliminated = true;
        }
    }
    return;
}