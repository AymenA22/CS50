#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#define BlockSize 512 // Info given in spec - 512 bytes

int main(int argc, char *argv[])
{
    // check for correct usage with a message if incorrect and return 1
    if (argc != 2)
    {
        printf("Correct usage checker ./recover IMAGE\n");
        return 1;
    }

    // open the image file
    char *file = argv[1];
    FILE *raw_file = fopen(file, "r"); // Info given in spec
    if (raw_file == NULL)              // check if raw_file is NULL with a message if incorrect and return 1
    {
        printf("Sorry, couldn't open %s.\n", file);
        return 1;
    }

    // Initilise variables
    bool found_image = false;  // Boolean true false to keep track of whether a jpeg image has been found or not
    int image_count = 0;       // counter for how many jpeg images have been found
    uint8_t buffer[BlockSize]; // 8 bit int buffer to store a block of data from the image
    char image_name[8];        // Create an array to store the filename of the current jpeg image that is 8 bits long
    FILE *outptr = NULL;       // Create a pointer to the current jpeg file

    // read the image file given in the buffer blocks
    while (fread(buffer, 1, BlockSize, raw_file) == BlockSize)
    {
        // If the buffers 1st, 2nd, 3rd match 0xff 0xd8 0xff and 4th buffer can be any of 16 hex values
        // To simplify the 4th buffer compare buffer[3] & 0xf0 with 0xe0 and if true then image found and continue
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        // buffer[3] & 0xf0 == 0xe0 is the same as writing: xxxx 0000 & 1111 0000 == 1110 0000
        // when you add the binary values, if the result is equal to 1110 0000 then continue
        //
        {
            if (found_image)
            {
                fclose(outptr);
            }
            else
            {
                found_image = true;
            }

            // open a new jpeg file - Info given in spec
            sprintf(image_name, "%03d.jpg", image_count); // Create the file name for the new image based
            // on the image count variable. The %03d prints an int with 3 padded digits.

            // open a new jpeg file with the generated filname
            outptr = fopen(image_name, "w");

            // Check if the out pointer is NULL. If NULL, print a message stating the image could not be created.
            if (outptr == NULL)
            {
                fclose(raw_file);
                printf("Could not create %s. \n", image_name);
                return 3;
            }
            image_count++; // increment the image counter for each jpeg that is found
        }

        // If an image is found, write the current block to the open jpg file (out pointer)
        if (found_image)
        {
            fwrite(buffer, BlockSize, 1, outptr);
        }
    }

    // close the forensic image raw_file and the last jpeg file (out pointer) if one was open
    fclose(raw_file);
    if (found_image)
    {
        fclose(outptr);
    }
    // exit program
    return 0;
}