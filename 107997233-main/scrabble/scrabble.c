#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

// Points assigned to each letter of the alphabet
int POINTS[] = {1, 3, 3, 2, 1, 4, 2, 4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1, 1, 1, 1, 4, 4, 8, 4, 10};

int compute_score(string word);

int main(void)
{
    // Get input words from both players
    string word1 = get_string("Player 1: "); // ask user 1 for text input and save it to "word1"
    string word2 = get_string("Player 2: "); // ask user 2 for text input and save it to "word2"

    // Score both words
    int score1 = compute_score(word1); // put word1 into "compute_score" and return and store the output to "score1"
    int score2 = compute_score(word2); // put word2 into "compute_score" and return and store the output to "score2"

    // TODO: Print the winner
    if (score1 > score2)
    {
        printf("Player 1 wins!\n"); // print the winner based on the computation
        // printf("with %d points\n", score1);
    }

    else if (score2 > score1)
    {
        printf("Player 2 wins!\n"); // print the winner based on the computation
        // printf("with %d points\n", score2);
    }

    else
    {
        printf("Tie!\n");
    }
}

int compute_score(string word)

// Compute and return score for string
{
    int score = 0;
    for (int i = 0; i < strlen(word); i++) // count how many characters are in the input
    {
        if (isupper(word[i])) // if character in position i of string word is uppercase
        {
            score = score + POINTS[word[i] - 65]; //-97 because ASCII 65 is 'a' - could you 'A' or -65
        }

        if (islower(word[i])) // if character in position i of string word is lowercase
        {
            score = score + POINTS[word[i] - 97]; //-97 because ASCII 97 is 'a' - could you 'a' or -97
        }
    }
    return score;
}