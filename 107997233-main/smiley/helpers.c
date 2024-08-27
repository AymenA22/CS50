#include "helpers.h"

void colorize(int height, int width, RGBTRIPLE image[height][width])
{
    // Change all black pixels to a color of your choosing

    // cycle through the array
    // If a pixel is black then change the colour

    // Look in every row and every column

    for (int i = 0; i < width; i++) // cycle through all rows of the array while the width row is less than the width
    {
        for (int j = 0; j < height; j++) // cycle through all columns of the array while the width row is less than the height
        {
            if (image[j][i].rgbtRed == 0 && image[j][i].rgbtGreen == 0 &&
                image[j][i].rgbtBlue == 0) // check if each pixel in the array is black (0, 0, 0)
            { // if the pixel in the array is black then make the current pixel in the array a different colour
                image[j][i].rgbtRed = 127;
                image[j][i].rgbtGreen = 0;
                image[j][i].rgbtBlue = 255;
            }
        }
    }
}