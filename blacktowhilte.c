#include <stdio.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0

int main()
{
    int choice, i, j, k;

    // Loop to continuously ask for user's choice until 6 is entered
    do
    {
        printf("Select the filter for Image.\n");
        printf("1.Black to White.\n");
        printf("2.RGB to gray\n");
        scanf("%d", &choice);

        switch (choice)
        {
            //******************************BLACK TO WHITE*****************************************
            case 1:
                FILE *fIn = fopen("lena512.bmp", "r"); // Open input file
                FILE *fOut = fopen("b_w.bmp", "w+");   // Open output file

                unsigned char byte[54];         // to get the image header
                unsigned char colorTable[1024]; // to get the color table

                if (fIn == NULL) // Check if the input file has not been opened successfully
                {
                    printf("File does not exist.\n");
                }

                // Read the 54 byte header from fIn
                for (i = 0; i < 54; i++)
                {
                    byte[i] = getc(fIn);
                }

                // Write the header to fOut
                fwrite(byte, sizeof(unsigned char), 54, fOut);

                // Extract image height, width, and bitDepth from imageHeader
                int height = *(int *)&byte[18];
                int width = *(int *)&byte[22];
                int bitDepth = *(int *)&byte[28];

                printf("width: %d\n", width);
                printf("height: %d\n", height);

                int size = height * width; // Calculate image size

                // If ColorTable is present, extract it
                if (bitDepth <= 8)
                {
                    fread(colorTable, sizeof(unsigned char), 1024, fIn);
                    fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
                }

                unsigned char buffer[size]; // To store the image data

                // Read image data
                fread(buffer, sizeof(unsigned char), size, fIn);

                // Convert black to white and write back to the output image
                for (i = 0; i < size; i++)
                {
                    buffer[i] = (buffer[i] > THRESHOLD) ? WHITE : BLACK;
                }

                fwrite(buffer, sizeof(unsigned char), size, fOut);

                // Close files
                fclose(fIn); 
                fclose(fOut);
                break;

            //************************************ RGB TO GRAY ************************************************
            case 2:
                FILE *fIN = fopen("lena_color.bmp", "r");    // Input File name
                FILE *fOUT = fopen("lena_gray.bmp", "w");     // Output File name

                unsigned char byte[54];

                if (fIN == NULL)
                {
                    printf("File does not exist.\n");
                }

                // Read the 54 byte header from fIn
                for (i = 0; i < 54; i++)
                {
                    byte[i] = getc(fIN);
                }

                // Write the header to fOut
                fwrite(byte, sizeof(unsigned char), 54, fOUT);

                // Extract image height, width, and bitDepth from imageHeader
                height = *(int *)&byte[18];
                width = *(int *)&byte[22];
                bitDepth = *(int *)&byte[28];

                printf("width: %d\n", width);
                printf("height: %d\n", height);

                size = height * width; // Calculate image size

                // 2D buffer to store RGB values
                unsigned char buffer[size][3];

                // Convert RGB to grayscale
                for (i = 0; i < size; i++)
                {
                    int y = 0;
                    buffer[i][2] = getc(fIN);  // Blue
                    buffer[i][1] = getc(fIN);  // Green
                    buffer[i][0] = getc(fIN);  // Red

                    // Conversion formula for RGB to grayscale
                    y = (buffer[i][0] * 0.3) + (buffer[i][1] * 0.59) + (buffer[i][2] * 0.11);

                    putc(y, fOUT);  // Write grayscale value to output
                    putc(y, fOUT);
                    putc(y, fOUT);
                }

                // Close files
                fclose(fOUT);
                fclose(fIN);

                // Measure and print execution time
                // Note: The variables 'start' and 'stop' are not declared or initialized in your code.
                // Include <time.h> and properly declare and initialize these variables to measure time.
                // stop = clock();
                // printf("\nCLOCKS_PER_SEC = %ld\n", stop-start); 
                // printf("%lf ms\n",((double)(stop-start) * 1000.0)/CLOCKS_PER_SEC );
                return 0;
        }
    }
    while (choice != 6);  // Exit loop when choice is 6

    return 0;
}
