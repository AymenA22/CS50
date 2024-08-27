#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>

#define BLOCK_SIZE 512 // given information

int main(int argc, char *argv[])
{
    // check for correct usage wiwh a message if incorrect or return 1 if ok
    if (argc !=2)
    {
        printf("Usage ./recover IMAGE\n");
        return 1;
    }

    // open the image file

    char *file = argv[1];
    FILE *raw_file = fopen(file, "r"); // given in notes

    if(raw_file == NULL)
    {
        printf("Could not open %s.\n", file);
        return 1;
    }

    // Initilise variables

    bool found_jpg = false; // flag to keep track if a jpeg has been fouund
    int jpg_count = 0; // couunter for how many jpegs have neeb fouund
    uint8_t buffer[BLOCK_SIZE]; // buffer to store a block of data from the image
    char jpg_name[8]; // Array to store the filename of the current jpeg
    FILE *outptr = NULL; // Pointer to the current Jpeg file

    // read the image given in the

    while (fread(buffer, BLOCK_SIZE, 1, raw_file) == 1)
    {
        // Check if marks the start of a new kpeg
        if (buffer[0] == 0xff && buffer [1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        // above given in notes
        {
            if (found_jpg)
            {
                fclose(outptr);
            }
            else
            {
                found_jpg = true;
            }

            // open a new jpeg file - given in notes

            sprintf(jpg_name, "%03d.jpg", jpg_count); // generates the filename for the new jpeg image based on the jpeg count variable
            // the %03d gives 3 decimal places

            // open a new jpeg file with the generated filname
            outptr = fopen(jpg_name, "w");

            // Check if the output is null

            if (outptr == NULL)
            {
                fclose(raw_file);
                printf("Could not create %s. \n", jpg_name);
                return 1;
            }
            // increment the couunter for each jpeg we fouund
            jpg_count++;
        }


        // write the current block to the current jpg file if one is open

        if (found_jpg)
        {
            fwrite(buffer, BLOCK_SIZE, 1, outptr);
        }

        // close the forensic image file and the last jpeg file if one was open
        fclose(raw_file);
        if(found_jpg)
        {
            fclose(outptr);
        }

        // exit program

        return 0;
    }



/*



// open memory card
    FILE *f = fopen(filename, "r"); // r is read mode
    every 3 bytes of JPEG starts with
    0xff
    0xd8
    0xff
    last byte starts with 0xe0 through to 0xef

    all JPEGS are stored back to back

    Memory card is a load of 512 byte chunks

    keep searching each block until the above sequence is found

    use a buffer of bytes

    buffer[0] == 0xff // first byte of buffer
    buffer[1] ==

    (buffer[3] & 0xf0) == 0xe0

    just look at the first 4 bits of this 8 bit byte and set the remaining 4 bits to 0
    this means 0xe0 0xe1 0xe2 all become oxe0 because we cleared out the last 4 bits

    now we can just compare the result to oxe0 to determing if this byte is the 4th byte in a jpeg

    if all these conditions are true then this 512 block represents a new file


    then keep writing until the next sequence of 0xff is found, then create a new file

    keep repeating this process until you reach the end of the memory card

    how to read data

    fread(data, size, number, inptr);
    data = pointer to where to store data you are reading
    size = size of each element to read
    number = number of elements to read
    inptr = File * to read from


    create a new file
        keep track of how many jpeg files

        sprintf(filename, "%03i.jpg, 2);
        make sure filename has enought memory

        open a new file
        FILE *img = fopen(filename, "w"); // w writes

        fwrite(data, size, number, outptr);




// look for beginning of a JPEG
// Open a new JPEG file
// Write 512 bytes until a new JPEG is found

int arr[10];
fread(arr, sizeof(int), 10, ptr);

then

int arr[10];
fwrite(arr,sizeof(int), 10, ptr);

or

double* arr2 = malloc(sizeof(double) * 80);
fread(arr2, sizeof(double), 80, ptr);



or

char c;
fread(&c, sizeof(char), 1, ptr);



// Stop ad the end of the file


}

    buffer

    char *s = get_string("s: ");
    if (s == NULL)
    {
        return 1;
    }

    char t* = malloc(strlen(s) + 1);
    if (t == NULL)
    {
        return 1;
    }

    strcpy(t, s);

    if (strlen(t) > 0)
    {
        t[0] = toupper(t[0]);
    }

    printf("s: %s\n", s);
    printf("t: $s\n", t);

    // free malloc t
    free(t);

    return 0;
*/

