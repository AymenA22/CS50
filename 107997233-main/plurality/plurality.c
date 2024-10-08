#include <cs50.h>
#include <stdio.h>
#include <string.h>

// Max number of candidates
#define MAX 9

// Candidates have name and vote count
typedef struct
{
    string name; // name of candidate who was voted for
    int votes;
}
candidate;

// Array of candidates
candidate candidates[MAX];

// Number of candidates
int candidate_count;

// Function prototypes
bool vote(string name);
void print_winner(void);

int main(int argc, string argv[])
{
    // Check for invalid usage
    if (argc < 2)
    {
        printf("Usage: plurality [candidate ...]\n");
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
        candidates[i].name = argv[i + 1];
        candidates[i].votes = 0;
    }

    int voter_count = get_int("Number of voters: ");

    // Loop over all voters
    for (int i = 0; i < voter_count; i++)
    {
        string name = get_string("Vote: ");

        // Check for invalid vote
        if (!vote(name))
        {
            printf("Invalid vote.\n");
        }
    }

    // Display winner of election
    print_winner();
}

// Update vote totals given a new vote
bool vote(string name) // this brings in string name from main void
{
    for (int i = 0; i < candidate_count; i++) // for loop to increment through the candidate array
    {
        if (strcmp(candidates[i].name, name) == 0) // compare strings "candidate array position" against "name entered"
        {
            candidates[i].votes++; // if the if statement is returned as "True" then increment the candidate array position votes by 1
            return true; // return true to break loop and look at the next voters input      }
        }
    }
    return false; // return false
}

// Print the winner (or winners) of the election
void print_winner(void)
{
    int max_votes = 0; // create an interger for the maxmimum number of votes

    // Determine which candidate receives the highest number of votes

    for (int i = 0; i < candidate_count; i++) // for loop to increment through the candidate array
    {
        if (candidates[i].votes > max_votes) // if candidate [array position] is greater than to the maximum number of votes...
        {
            max_votes = candidates[i].votes; // make the maximum votes equal to the candidate array position for votes
        }
    }

    // Determine which candidate has the most votes
    for (int i = 0; i < candidate_count; i++) // for loop to increment through the candidate array
    {
        // if candidate [array position] is equal to the maximum number of votes, print below
        if (candidates[i].votes == max_votes)
        {
            printf("%s\n", candidates[i].name); // print the candidate with the most votes
        }
    }
    return;
}