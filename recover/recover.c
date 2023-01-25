#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // checks the numbers of arguments
    if (argc != 2)
    {
        fprintf(stderr, "Usage: ./recover infile\n");
        return 1;
    }

    // open the file
    FILE *file = fopen(argv[1], "r");

    if (file == NULL)
    {
        fprintf(stderr, "Could not open %s.\n", argv[1]);
        return 2;
    }

    // output file
    FILE *outputfile = NULL;

    // buffer
    BYTE buf[512];

    //numbers of jpeg files
    int count = 0;

    // the file name
    char fname[8] = {0};


    while (fread(buf, sizeof(BYTE) * 512, 1, file) == 1)
    {
        //a jpeg is found
        if (buf[0] == 0xFF && buf[1] == 0xD8 && buf[2] == 0xFF && (buf[3] & 0xF0) == 0xE0)
        {

            if (outputfile != NULL)
            {
                fclose(outputfile);
            }
            sprintf(fname, "%03d.jpg", count++);

            //open the file to write
            outputfile = fopen(fname, "w");
        }

        // writing the bytes
        if (outputfile != NULL)
        {
            fwrite(buf, sizeof(BYTE) * 512, 1, outputfile);
        }
    }


    // close the outputfile
    if (outputfile != NULL)
    {
        fclose(outputfile);
    }

    //close the input file
    fclose(file);

    return 0;
}