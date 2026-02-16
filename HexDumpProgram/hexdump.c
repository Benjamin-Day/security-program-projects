#include <stdio.h>
#include <stdlib.h>
#include <stdio_ext.h>

void endfile(unsigned char magicNum[]);

void intro(unsigned char magicNum[]);

int main (void)
{  
    int offset = 0;
    int character = 0;
    float count = 0;
    unsigned char magicNum[5] = "\0";
    char filename[50] = "\0";
    unsigned char val[16];

    // Get filename from user.
    printf("Enter the filename to hex dump: ");
    scanf(" %s", filename);

    // Clear stdin to avoid feed issues on first print
    __fpurge(stdin);

    // Open file and check for errors.
    FILE *f = NULL;
    f = fopen(filename, "rb");
    if (!f)
    {
        fprintf(stderr, "file error (last)\n");
        exit(1);
    } 

    //  Collect first 4 bytes for magic number.
    for (int i = 0; i < 4; i++)
    {
        fread(&magicNum[i], 1, 1, f);
    }

    // Call function to print magic number and file type.
    intro(magicNum);

    // Reset f to read from the start of the file.
    fseek(f, 0, SEEK_SET);

    printf("\n=================================================================================\n");
    printf("| Offset |                  Hexadecimal Data                 | Character Format |\n");
    printf("=================================================================================\n");

    // While for whole file.
    while (!feof(f))
    {
        // To print 10 lines
        for (int j = 0; j < 10; j++)
        {
            // Reset all positions to null incase nothing is read.
            for (int i = 0; i < 16; i++)
            {
                val[i] = '\0';
            }

            // Read 16 bytes from the file.
            for (int i = 0; i < 16; i++)
            {
                fread(&val[i], 1, 1, f);
            }

            // Print the position of first byte in the column.
            printf("| %06x | ", offset);
            offset = offset + 16;
            
            // Print out the bytes that were read.
            for (int i = 0; i < 16; i++)
            {
                printf("%02hhx ", val[i]);
                if (i == 7)
                {
                    printf("  ");
                }
            }

            printf("| ");

            // Print out character for the byte if it is within character range.
            for (int i = 0; i < 16; i++)
            {
                // Increment character counters to keep track of bytes read.
                if (val[i] > 32 && val[i] < 127)
                {
                    printf("%c", val[i]);
                }
                else
                {
                    printf(".");
                }
            }
            printf(" |\n");
        }
        printf("\t\t\t10 lines printed... PAUSING\n\t\t\tPress enter to continue\n");
        getchar();
    }

    fseek(f, 0, SEEK_SET);

    // Call function to print end of file message and magic number.
    endfile(magicNum);

    fclose(f);

    return 0;
}

// Function to print magic number and file type.
void intro(unsigned char magicNum[])
{
    printf("\nMagic number: 0x%02hhx%02hhx%02hhx%02hhx", magicNum[3], magicNum[2], magicNum[1], magicNum[0]);
    printf("\tFile Type: ");

    // Print bytes accounting for little endian.
    for (int i = 0; i < 4; i++)
    {
        if (magicNum[i] > 32 && magicNum[i] < 127)
        {
            printf("%c", magicNum[i]);
        }
    }
}

// function to print end of file message and magic number.
void endfile(unsigned char magicNum[])
{
    printf("\t\t\tEnd of file reached\n");
    printf("\nMagic Number: 0x");

    // Print bytes according to little endian.
    for (int i = 3; i >= 0; i--)
    {
        printf("%02hhx", magicNum[i]);
    }
}
