// Ask user for text input
// Calculate and store the number of letters
// Calculate and store the number of words
// Calculate and store the number of sentences
// Apply the formula
// Print grade as specified

#include <cs50.h>
#include <stdio.h>
#include <ctype.h> //use to count letters
#include <math.h> //use to calculate
#include <string.h> //use to handle text

// Prototype functions
int count_Letters(string text);
int count_Words(string text);
int count_Sentences(string text);
int coleman_Index(int, int, int);
void print_Grade(int index);

int l, w, s, index;

int main(void)
{
    string text = get_string("Text: "); //Ask user to input text and save in string called text
    count_Letters(text); //int called l to save letters in text
    count_Words(text); //int called w to save words in text
    count_Sentences(text); //int called s to save sentences in text
    coleman_Index(l, w, s); //int called index to compute the calculation

    print_Grade(index);
}

int count_Letters(string text)
{
    int Letters = 0; //set an interger called Letters to zero
    for (int i = 0; text[i] != '\0'; i++)   //if text array output is not equal to zero then add one to index counter
                                            // text[i] is used to increment from text[0] which is the first char in the string
                                            // it will continue incrementing until the \0 which is at the end of all strings as a char
    {
        if (isalpha(text[i]) > 0)
        {
            Letters++;
        }
    }
    return l = Letters;
}

int count_Words(string text)
{
    int Words = 1; //set an interger called Words to zero
    for (int i = 0; text[i] != '\0'; i++) //if text array output is not equal to zero then add one to index counter   {
// text[i] is used to increment from text[0] which is the first char in the string
// it will continue incrementing until the \0 which is at the end of all strings as a char
    {
        if ((text[i]) == ' ') //if any char in the text string is a space then add one to the count Words
        {
            Words++;
        }
    }
    return w = Words;
}

int count_Sentences(string text)
{
    int Sentences = 0; //set an interger called Sentences to zero
    for (int i = 0; text[i] != '\0'; i++)   //if text array output is not equal to zero then add one to index counter   {
                                            // text[i] is used to increment from text[0] which is the first char in the string
                                            // it will continue incrementing until the \0 which is at the end of all strings as a char
    {
        if ((text[i]) == '!' || text[i] == '.' || text[i] == '?') //if any char in the text string is a space then add one to the count Words
        {
            Sentences++;
        }
    }
    return s = Sentences;
}

int coleman_Index(int a, int b, int c)
{
    return index = round(0.0588*(a/((float)b/100))-0.296*(c/((float)b/100))-15.8);
}

void print_Grade(int grade)
{
    //calculate the number of letters and sentences per 100 words

    if (grade < 1)
    {
        printf("Before Grade 1");
    }
    else if (grade > 0 && grade < 16)
    {
        printf("Grade %i\n", grade);
    }
    else
    {
        printf("Grade 16+\n");
    }



}
