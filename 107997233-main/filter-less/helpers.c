#include "helpers.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // create an integer that can hold the average colour reading
    int average = 0;
    // iterate through all rows of the picture (array)
    for (int row = 0; row < width; row++)
    {
        // for every column, iterate through each row of the picture (array)
        for (int column = 0; column < height; column++)
        {
            // set the int "average" to the sum of the red green and blue and then divide by 3
            // use 3.00 to improve accuracy and +0.5 to eliminate any rounding issues
            average = round((image[row][column].rgbtRed + image[row][column].rgbtGreen + image[row][column].rgbtBlue) / 3.0);
            // set the image row and columns to the new average that was calculated
            image[row][column].rgbtRed = average;
            image[row][column].rgbtGreen = average;
            image[row][column].rgbtBlue = average;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    // iterate through all rows of the picture (array)
    for (int row = 0; row < width; row++)
    {
        // for every row, iterate through each rcolumn of the picture (array)
        for (int column = 0; column < height; column++)
        {
            // create integers that can hold the original red green and blue values
            int originalRed = image[row][column].rgbtRed;
            int originalGreen = image[row][column].rgbtGreen;
            int originalBlue = image[row][column].rgbtBlue;

            // create new variables for the sepia red green and blue
            // calculate the new values by rouunding the sum of the calculated original values

            int newRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int newGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int newBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            // print the new colour value if the values are less than 255 otherwise ignore the values and set to 255
            image[row][column].rgbtRed = fmin(255, newRed);
            image[row][column].rgbtGreen = fmin(255, newGreen);
            image[row][column].rgbtBlue = fmin(255, newBlue);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // need a temp memory location to hold the pixel info
    // iterate through all rows of the picture (array)
    for (int row = 0; row < height; row++)
    {
        // for every row, iterate through each rcolumn of the picture (array)
        for (int column = 0; column < width / 2; column++)
        {
            // swap the pixels one at a time by storing the original pixel in a temporary variable
            // then make the original pixel equal to the last pixel (width - 1 - column)
            // then make the last pixel equal to the original pixel (temporary variable)
            RGBTRIPLE temp = image[row][column];
            // swap the pixels one at a time by in the row and column by making the row and column
            // equal to the width - 1 - the column number
            image[row][column] = image[row][width - 1 - column]; // swaps the pixels
            image[row][width - 1 - column] = temp;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])

{
    RGBTRIPLE temp[height][width];
    // iterate through all rows of the picture (array)
    for (int row = 0; row < height; row++)
    {
        // for every row, iterate through each rcolumn of the picture (array)
        for (int column = 0; column < width; column++)
        {
            // copy the original pixels to the temporary array
            temp[row][column] = image[row][column];
        }
    }
    // iterate through all rows of the picture (array)
    for (int row = 0; row < height; row++)
    {
        // for every row, iterate through each rcolumn of the picture (array)
        for (int column = 0; column < width; column++)
        {
            // create variables to store the values for the total red, total green and total blue
            int totalRed = 0;
            int totalGreen = 0;
            int totalBlue = 0;
            // create a variable for a counter with enough decimal places for accuracy
            float counter = 0.00;

            // create a 3 x 3 grid which we can iterate through to get the surrounding pixels values
            for (int x = -1; x < 2; x++)
            {
                for (int y = -1; y < 2; y++)
                {
                    // calculate the coordinates of the current pixel
                    int currentX = row + x;
                    int currentY = column + y;
                    // set criteria to ensure the current pixel is within the range of the array
                    if (currentX < 0 || currentX > (height - 1) || currentY < 0 || currentY > (width - 1))
                    {
                        continue;
                    }
                    // add the red value to the total variable totalRed
                    totalRed += image[currentX][currentY].rgbtRed;
                    // add the red value to the total variable totalGreen
                    totalGreen += image[currentX][currentY].rgbtGreen;
                    // add the red value to the total variable totalBlue
                    totalBlue += image[currentX][currentY].rgbtBlue;
                    // add one to the counter
                    counter++;
                }
            }
            // set the values of the temporary array to the total value divided by the counter value
            temp[row][column].rgbtRed = round(totalRed / counter) + 0.5;
            temp[row][column].rgbtGreen = round(totalGreen / counter) + 0.5;
            temp[row][column].rgbtBlue = round(totalBlue / counter) + 0.5;
        }
    }
    // iterate through all rows of the picture (array)
    for (int row = 0; row < height; row++)
    {
        // for every row, iterate through each rcolumn of the picture (array)
        for (int column = 0; column < width; column++)
        {
            // make the current pixel value equal to the temporary pixel value that has been calculated
            image[row][column] = temp[row][column];
        }
    }
    return;
}