#include <stdio.h>
#include <stdlib.h>
#include <cs50.h>

// Submission for week 4 "Forensic JPEG recovery program"
// By Duncan Starkenburg aka EvilDunk

int main(int argc, char *argv[])
{
    FILE *file;
    // Check arg count
    if (argc == 2)
    {
        file = fopen(argv[1], "r");
        // Check if file can be opened
        if (file == NULL)
        {
            printf("Could not open file.\n");
            return 1;
        }
    }
    else
    {
        printf("Usage: ./recover <file>\n");
        return 1;
    }
    unsigned char buffer[512];
    int foundjpg = 0;
    int jpgamount = 0;
    char filename[8];
    FILE *img;
    // Repeat until end of card
    // Read 512 bytes to buffer
    while ((fread(buffer, 1, 512, file) != 0))
    {
        // If foundjpg == 0
        if (foundjpg == 0)
        {
            // If first four indicate jpg
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // Make new file called 000
                sprintf(filename, "%.3i.jpg", jpgamount);
                // Open file 000
                img = fopen(filename, "w");
                // Write 512 bytes to file
                fwrite(buffer, 1, 512, img);
                foundjpg = 1;
            }
            continue;
        }
        // If foundjpg == 1
        if (foundjpg == 1)
        {
            // If first four indicate jpg
            if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
            {
                // Close current file
                fclose(img);
                // Increment file counter
                jpgamount++;
                // Open next file
                sprintf(filename, "%.3i.jpg", jpgamount);
                img = fopen(filename, "w");
                // Write 512 bytes to file
                fwrite(buffer, 1, 512, img);
            }
            // Else
            else
            {
                // Write 512 bytes to open file
                fwrite(buffer, 1, 512, img);

            }
        }


    }

}
