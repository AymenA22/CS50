#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max voters and candidates - GLOBAL VARIABLE
#define MAX_VOTERS 100
#define MAX_CANDIDATES 9

// preferences[i][j] is jth preference for voter i
// i is how many rows from above 100
// j is how many columns from above 9
int preferences[MAX_VOTERS][MAX_CANDIDATES];

// Candidates have name, vote count, eliminated status
// Creating a new type

// candidate has a string called name e.g. Alice
// candidate has an interger for the number of votes
// candidate has a boolean cell for eliminated or not
typedef struct
{
    string name;
    int votes;
    bool eliminated;
} candidate;

// Array of candidates
// Create an array called candidates of length 9 from line 7
// The type of this array is "candidate" instead of "int" or "string"
candidate candidates[MAX_CANDIDATES];

// Numbers of voters and candidates
// Create Global Variables with no value assigned
int voter_count;
int candidate_count;

// Function prototypes
// Need to include these for the program to work
bool vote(int voter, int rank, string name);
void tabulate(void);
bool print_winner(void);
int find_min(void);
bool is_tie(int min);
void eliminate(int min);

// command line arguements
int main(int argc, string argv[])
{
    // Check for invalid usage
    // checking that there are at least two candidates in the election
    if (argc < 2)
    {
        printf("Usage: runoff [candidate ...]\n");
        return 1;
    }

    // Populate array of candidates
    // iterate through the candidates and put their input into the 2D array
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
    // Check that there are less than 100 voters
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
            // This checks if the vote is valid

            // i is the number of the voter
            // j is the rank
            // name is the name

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
            // if there is a winner then the program ends so use "break"
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

// Going to receive and voter, a rank, and a name

bool vote(int voter, int rank, string name)
{
    // if the candidates name is entered by the voter then add the voter and their rank to the preferences matrix
    // Called every time we get a rank and check if the vote is valid

    // Count through every voter and apply the candidate name they selected to the rank to position the vote
    // Keep cycling through each candidate and compare to the names in the candidate
    // Only update if the name is a match to a candidate
    for (int i = 0; i < candidate_count; i++)
    {
        if (strcmp(candidates[i].name, name) == 0)
        // if "true" the candidate selected is in the candidate name, execute the code below
        {
            preferences[voter][rank] = i;
            return true;
        }
    }
    return false; // if the above code is not executed then return false
}

// Tabulate votes for non-eliminated candidates
void tabulate(void)
{
    // Cycle through all candidates that have not been eliminated and update
    // the number of votes
    for (int i = 0; i < voter_count; i++)
    {
        for (int j = 0; j < candidate_count; j++)
        {
            // int candidate_number = preferences[i][j];
            if (candidates[preferences[i][j]].eliminated == false)
            {
                candidates[preferences[i][j]].votes++;
                break; // break out of voter to continue tablulating or else it will only count one vote
            }
        }
    }
    return;
}

// Print the winner of the election
bool print_winner(void)
{
    // Check if more than half of the votes
    int majority_of_votes = (voter_count / 2) + 1;

    for (int i = 0; i < candidate_count; i++) // cycle through the candidate_count
    {
        // if the number of votes for each candidate index is more than half the voter count
        if (candidates[i].votes >= majority_of_votes)
        {
            // print name of winning candidate
            printf("%s\n", candidates[i].name);
            return true; // exit program
        }
    }
    return false; // continue program
}

// Return the minimum number of votes any remaining candidate has
int find_min(void)
{
    // cycle through the candidates. If they have not been eliminated and not lower than the minimum, assign the minium to this
    // candidate
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
    // return min instead of 0 because if candidate is lower than min they are already eliminated
    return min;
}

// Return true if the election is tied between all candidates, false otherwise
bool is_tie(int min)
{
    // if the election votes is equal to the minium add one to eliminate else if equal to minimum add one to the count
    int eliminate = 0;
    int counter = 0;

    for (int i = 0; i < candidate_count; i++)
    {
        if (!candidates[i].eliminated)
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