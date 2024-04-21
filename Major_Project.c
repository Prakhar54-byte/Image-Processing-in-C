//********************************************************************************ICS1020-MAJOR PROJECT*******************************************************************************************************************
/*CODE BY:
 NAMAN SONI(B23CM1026)
 ATANU KAYAL(B23EE1005) 
 PRAKHAR CHAUHAN(B23BB1038) 
 SOMYA JAINGIR(B23CI1036) 
 */

//OUTCOME OF CODE: TO APPLY DIFFERENT FILTERS ON BMP IMAGES WHICH HOLDS APPLICATIONS IN THE FIELD OF DEFENCE , BUILDING IMAGE FILTERS IN APPS, 
/*WHAT WE LEARNED : HOW TO READ IMAGE FILES , HOW TO PROCESS IMAGE FILES AND CREATE IMAGE FILES AFTER SUCESSFULLY IMPLEMENTING FEATURES,HOW THE COLOURS ARE MADE USING RGB COLOUR SET,
                    HOW TO ALTER RGB COLOUR LEVELS DURING IMAGE PROCESSING,etc. 
*/

//***********************************************************************************************************************************************************************************************************************

//Adding required libraries
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

//Defining Macros
//*************************************************ADD THE COMMENT AFTER COMMITING ANY CHANGE IN THE MACROS , MENTIONING THE OLD AND NEW VALUES************************************************************************
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0
#define MAX_COLOR 255
#define BRIGHTNESS_FACTOR 25
#define MAX_VALUE 255
//***********************************************************************************************************************************************************************************************************************

void rotate()
{
    //Opening the file to be processed in read mode
    FILE *fIn = fopen("lena512.bmp", "r");       
    //Opening the new file to be created in w+ mode
    FILE *fOut = fopen("lena_rotate.bmp", "w+"); \

    //Declaring variables
    int i, j, choice;
    unsigned char byte[54], colorTable[1024];
 
    //Check point to ensure the sucessfull opeing of the file
    if (fIn == NULL) 
    {
        printf("File does not exist.\n");
    }
    
    // reading the 54 byte header from fIn
    for (i = 0; i < 54; i++) 
    {
        byte[i] = getc(fIn);
    }
    
    // writing the header to the new bmp file
    fwrite(byte, sizeof(unsigned char), 54, fOut); 

    // extract image height, width and bitDepth from imageHeader
    int height = *(int *)&byte[18];
    int width = *(int *)&byte[22];
    int bitDepth = *(int *)&byte[28];

    printf("width: %d\n", width);
    printf("height: %d\n", height);
    
    //Calculating the image size for furthur use
    int size = height * width; 
    
    // if ColorTable present, extract it.
    if (bitDepth <= 8) 
    {
        fread(colorTable, sizeof(unsigned char), 1024, fIn);
        fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
    }
    
    // To store the image data
    unsigned char buffer[width][height]; 
    unsigned char out_buffer[width][height];

    //Reading the data stored in image
    fread(buffer, sizeof(unsigned char), size, fIn); 
    
    //Asking the chioce from the user about furthur actions
    printf("Enter your choice :\n");
    printf("1. Rotate right\n");
    printf("2. Rotate left\n");
    printf("3. Rotate 180\n");
    
    scanf("%d", &choice);
    
    // To rotate image in 3 different direction
    switch (choice) 
    {
    //TO ROTATE THE IMAGE RIGHT
    case 1:
        for (i = 0; i < width; i++) 
        {
            for (j = 0; j < height; j++)
            {
                //APPLYING MATRIX MANUPULATION
                out_buffer[j][height - 1 - i] = buffer[i][j];
            }
        }
        //EXITING
        break;
    
    //TO ROTATE THE IMAGE TO LEFT
    case 2:
        for (i = 0; i < width; i++) 
        {
            for (j = 0; j < height; j++)
            {
                //APPLYING MATRIX MANUPULATION
                out_buffer[j][i] = buffer[i][j];
            }
        }
        //EXITING
        break;
    
    //TO ROTATE THE IMAGE UPSIDE DOWN
    case 3:
        for (i = 0; i < width; i++) 
        {
            for (j = 0; j < height; j++)
            {
                out_buffer[width - i][j] = buffer[i][j];
            }
        }
        //EXITING
        break;

    //CASE TO HANDLE UNDESIRED INPUT
    default:
        break;
    }
    
    //WRITING BACK THE IMAGE
    fwrite(out_buffer, sizeof(unsigned char), size, fOut); 
     
    //CLOSING ALL THE OPENED FILE
    fclose(fIn);
    fclose(fOut);
}


int main()
{
    //DECLARING VARIABLES
    int choice, i, j, k, size;

    //IMPLENMENTING DO-WHILE LOOP
    do
    { 
        //TAKING USER CHOICE ABOUT SPECIFIC FILTER IMPLEMENTATION
        printf("Select the filter for Image.\n");
        printf("1. Black to White.\n");
        printf("2. RGB to gray.\n");
        printf("3. Increase brightness.\n");
        printf("4. Blur the Image.\n");
        printf("5. Blur to Gray.\n");
        printf("6. Colours to Sepia.\n");
        printf("7. Copy Image.\n");
        printf("8. Darken Image.\n");
        printf("9. Rotate Image.\n");
        printf("10. Negative Image.\n");
        printf("11. Exit.\n");

        scanf("%d", &choice);

        //CODE TO APPLY BLACK AND WHITE FILTER
        if (choice == 1)
        {                                          
            //OPENING INPUT AND OUTPUT FILES
            FILE *fIn = fopen("lena512.bmp", "r"); 
            FILE *fOut = fopen("b_2w.bmp", "w+");  
            
            
            //DECLARING VARIABLES
            int i;
            // TO GET THE IMAGE HEADER
            unsigned char byte[54];      
            // TO GET THE COLOURTABLE
            unsigned char colorTable[1024]; 
            
            //CHECKPOINT TO ENSURE THAT FILE IS SUCESSFULLY OPENED
            if (fIn == NULL) 
            {
                printf("File does not exist.\n");
            }

            //READING 54 BYTE HEADER 
            for (i = 0; i < 54; i++) 
            {
                byte[i] = getc(fIn);
            }

            //WRITING THE HEADER TO NEW IMAGE CREATED
            fwrite(byte, sizeof(unsigned char), 54, fOut); 

            // EXTRAXT IMAGE HEIGHT ,WIDTH AND BITDEPTH FROM IMAGE HEADER
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];
            
            //PRINTING 
            printf("width: %d\n", width);
            printf("height: %d\n", height);
            
            //CALCULATING IMAGE SIZE FOR FUTHUR USE
            int size = height * width; 

            //EXTRACTING COLOUR TABLE IF PRESENT
            if (bitDepth <= 8) 
            {
                fread(colorTable, sizeof(unsigned char), 1024, fIn);
                fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
            }

            //DECLARING VARIABLE TO STORE IMAGE DATA
            unsigned char buffer[size]; 
            
            //READING IMAGE DATA
            fread(buffer, sizeof(unsigned char), size, fIn); 
            
            //STORING BLACK AND WHITE COLOUR VALUES TO BUFFER 
            for (i = 0; i < size; i++) 
            {
                buffer[i] = (buffer[i] > THRESHOLD) ? WHITE : BLACK;
            }

            //WRITING OT THE NEW IMAGE
            fwrite(buffer, sizeof(unsigned char), size, fOut); 
            
            //CLOSING THE FILES 
            fclose(fIn);
            fclose(fOut);

            break;
        }
         
         
        //GREY FILTER
        else if (choice == 2)
        { 
            // Implement your code here
            clock_t start, stop;

            // STARTING TIME FOR PROFILING PURPOSE
            start = clock(); 
            
            //OPENING FILE TO WORK ON
            FILE *fIn = fopen("lena_color.bmp", "r"); 
            //OPENING NEW FILE TO BE CREATED
            FILE *fOut = fopen("lena_gray.bmp", "w+");
             
            //DECLARING VARIABLES
            int i, j, y;
            unsigned char byte[54];
            
            //CHECKING IF THE FILE IS OPENDED
            if (fIn == NULL) 
            {
                printf("File does not exist.\n");
            }
            
            //READING HEADER FROM BMP
            for (i = 0; i < 54; i++) 
            {
                byte[i] = getc(fIn);
            }
            
            //WRITING HEADER TO NEW OUTPUT FILE
            fwrite(byte, sizeof(unsigned char), 54, fOut); 

            //EXTRACTING HEIGHT , WIDTH AND BITDEPTH
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];
 
            //PRINTING HEIGHT AND WIDTH OF IMAGE 
            printf("width: %d\n", width);
            printf("height: %d\n", height);

            //IMAGE SIZE FOR FUTURE USE
            int size = height * width; 

            //STROING IMAGE DATA
            unsigned char buffe[size][3]; 
            
            //IMPLEMENTING RGB TO GREY
            for (i = 0; i < size; i++) 
            {
        
                y = 0;

                ///STORING RGB VALUES FORM INPUT IMAGE TO BUFFE
                buffe[i][2] = getc(fIn); // blue
                buffe[i][1] = getc(fIn); // green
                buffe[i][0] = getc(fIn); // red

                //APPLYING CONVERSION FORMULA FOR RGB TO GREY 
                //******REFERENCE FROM:- https://support.ptc.com/help/mathcad/r9.0/en/index.html#page/PTC_Mathcad_Help/example_grayscale_and_color_in_images.html******

                y = (buffe[i][0] * 0.3) + (buffe[i][1] * 0.59) + (buffe[i][2] * 0.11); // conversion formula of rgb to gray

                //PUTTING THE PROCESSED VALUE TO THE OUTPUT IMAGE
                putc(y, fOut);
                putc(y, fOut);
                putc(y, fOut);
            }

            //CLOSING THE FILE OPENED EARLIER
            fclose(fOut);
            fclose(fIn);

            //STOPPING THE CLOCK
            stop = clock();
            //PRINTING THE COLOCK_PER_SEC IN THE OUTPUT BMP IMAGE
            printf("\nCLOCKS_PER_SEC = %ld\n", stop - start);
            printf("%lf ms\n", ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC);
            break;
        }


        // Increase brightness(filter)
        else if (choice == 3)
        { 
            // Implement your code here
            // Opening the file on which we have to apply filter
            FILE *fIn = fopen("lena512.bmp", "r");    
            // Creating a new file 
            FILE *fOut = fopen("lena_bright.bmp", "w+"); 
            
            // declaring some variables 
            int i;
            unsigned char byte[54], colorTable[1024];

        // check if the input file has not been opened succesfully.
            if (fIn == NULL) 
            {
                printf("File does not exist.\n");
                exit(1);
            }

            // Reading 54 byte header from fIn
            for (i = 0; i < 54; i++)
            {
                byte[i] = getc(fIn);
            }

            // Writing back the header to new creater file fOut
            fwrite(byte, sizeof(unsigned char), 54, fOut); 

            // extracting the image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            // Print the width and height of the image
            printf("width: %d\n", width);
            printf("height: %d\n", height);

            //Calculate the size of the image
            int size = height * width;

            // if ColorTable present, extract it
            if (bitDepth <= 8) 
            {
                fread(colorTable, sizeof(unsigned char), 1024, fIn);
                fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
            }

            // Assigning varibales to store image data
            unsigned char buffer[size]; 
            int temp;

            // Reading the image data
            fread(buffer, sizeof(unsigned char), size, fIn); 

            // For increasing the brightness, we are increasing the pixel values
            for (i = 0; i < size; i++) 
            {
                temp = buffer[i] + BRIGHTNESS_FACTOR;
                buffer[i] = (temp > MAX_COLOR) ? MAX_COLOR : temp;
            }

            //Writing again to the output image (fOut)
            fwrite(buffer, sizeof(unsigned char), size, fOut); 

            // Close the files
            fclose(fIn);
            fclose(fOut);

            break;
        }


        // Blur the Image
        else if (choice == 4)
        { 
            // Implement your code here
            clock_t start, stop;

            // Note the start time for profiling purposes.
            start = clock(); 

            // Input File name for applying filter
            FILE *fIn = fopen("images/lena_color.bmp", "r"); 
            //Creating(output) a new file
            FILE *fOut = fopen("lena_blur_color.bmp", "w+"); 
            
            //Declaring variables
            int i, j, y, x;
            unsigned char byte[54];

            //Check whether the input files has not opened
            if (fIn == NULL) 
            {
                printf("File does not exist.\n");
            }

            //Reading the 54 byte header from the input file
            for (i = 0; i < 54; i++) 
            {
                byte[i] = getc(fIn);
            }

            // write the header back
            fwrite(byte, sizeof(unsigned char), 54, fOut); 

            // extracting image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];
            
            //Printing the width and the height of the image(file)
            printf("width: %d\n", width);
            printf("height: %d\n", height);

            //calculating the image size
            int size = height * width; 
            
            //Storing the data of the input image
            unsigned char buffe[size][3]; 
            //Storing the data of the output image
            unsigned char out[size][3];  

            // Reading the data of the image character by character
            for (i = 0; i < size; i++)
            {   
                // for blue
                buffe[i][2] = getc(fIn); 
                // for green
                buffe[i][1] = getc(fIn); 
                // for red
                buffe[i][0] = getc(fIn); 
            }

            // Initializing the blurrring kernel and doing some operations on it 
            float v = 1.0 / 9.0; 
            float kernel[3][3] = {{v, v, v},
                                  {v, v, v},
                                  {v, v, v}};

            for (x = 1; x < height - 1; x++)
            {
                for (y = 1; y < width - 1; y++)
                {
                    float sum0 = 0.0;
                    float sum1 = 0.0;
                    float sum2 = 0.0;
                    for (i = -1; i <= 1; ++i)
                    {
                        for (j = -1; j <= 1; ++j)
                        {
                            // matrix multiplication with kernel with every color plane
                            sum0 = sum0 + (float)kernel[i + 1][j + 1] * buffe[(x + i) * width + (y + j)][0];
                            sum1 = sum1 + (float)kernel[i + 1][j + 1] * buffe[(x + i) * width + (y + j)][1];
                            sum2 = sum2 + (float)kernel[i + 1][j + 1] * buffe[(x + i) * width + (y + j)][2];
                        }
                    }
                    out[(x)*width + (y)][0] = sum0;
                    out[(x)*width + (y)][1] = sum1;
                    out[(x)*width + (y)][2] = sum2;
                }
            }

            // write image data back to the file
            for (i = 0; i < size; i++) 
            {
                putc(out[i][2], fOut);
                putc(out[i][1], fOut);
                putc(out[i][0], fOut);
            }
            
            //Closing the files
            fclose(fOut);
            fclose(fIn);
            
            //Stopping the clock
            stop = clock();
            //printing the time(clocks_per_sec)
            printf("\nCLOCKS_PER_SEC = %ld\n", stop - start); // 1000000
            printf("%lf ms\n", ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC);
            break;
        }


        // Blur to Gray
        else if (choice == 5)
        { 
            // Implement your code here
            clock_t start, stop;

            //Starting time for profiling purpos/es.
            start = clock(); 
            //opening the input file
            FILE *fIn = fopen("Images/lena_color.bmp", "r"); 
            //creating a new file
            FILE *fOut = fopen("lena_gray.bmp", "w+");     

            //Declaring variables 
            int i, j, y;
            unsigned char byte[54];

            // check if the input file has not been opened succesfully.
            if (fIn == NULL) 
            {
                printf("File does not exist.\n");
            }

            // reading the 54 byte header from fIn(using loop)
            for (i = 0; i < 54; i++) 
            {
                byte[i] = getc(fIn);
            }

            // writing the header back to the fOut file
            fwrite(byte, sizeof(unsigned char), 54, fOut); 

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            // calculate image size
            int size = height * width; 

            // Declaring varibles to store the image data
            unsigned char buffer[size], outline[size]; 

            float v = 1.0 / 9.0;
            // Initializing the blurrring kernel
            float kernel[3][3] = {{v, v, v}, 
                                  {v, v, v},
                                  {v, v, v}};

            // Reading the image data into buffer
            fread(buffer, sizeof(unsigned char), size, fIn); 

            for (i = 0; i < size; i++)
            {
                // copy image data to out bufer
                outline[i] = buffer[i]; 
            }
            
            //Applying some operation on operation
            for (int x = 1; x < height - 1; x++)
            {
                for (y = 1; y < width - 1; y++)
                {
                    float sum = 0.0;
                    for (i = -1; i <= 1; ++i)
                    {
                        for (j = -1; j <= 1; ++j)
                        {
                            sum = sum + (float)kernel[i + 1][j + 1] * buffer[(x + i) * width + (y + j)]; // matrix multiplication with kernel
                        }
                    }
                    outline[(x)*width + (y)] = sum;
                }
            }

            // writing image data back to the file(fOut)
            fwrite(outline, sizeof(unsigned char), size, fOut);

            //Closing the files
            fclose(fIn);
            fclose(fOut);
            break;
        }


        // Colours to Sepia
        else if (choice == 6)
        { 
            // Implement your code here
            clock_t start, stop;

            // Note the start time for profiling purposes.
            start = clock(); 

            // Input File name for filteration
            FILE *fIn = fopen("lena_color.bmp", "r");   
            //Creating a new file 
            FILE *fOut = fopen("lena_sepia.bmp", "w+");

            //Declaring some varibles
            int i, r, g, b;
            unsigned char byte[54];

            // check if the input file has not been opened succesfully.
            if (fIn == NULL) 
            {
                printf("File does not exist.\n");
            }

            // reading the 54 byte header from fIn(Input file)
            for (i = 0; i < 54; i++) 
            {
                byte[i] = getc(fIn);
            }

            // write the header back to new file(fOut)
            fwrite(byte, sizeof(unsigned char), 54, fOut); 

            //Extracting image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            //Printing the width and the height of the image
            printf("width: %d\n", width);
            printf("height: %d\n", height);

            //Calculating the image size
            int size = height * width; 

            //Declaring buffe to store image data
            unsigned char buffe[size][3]; 
            
            // Reading the data of the image character by character from input file(fIn)
            for (i = 0; i < size; i++)
            {
                r = 0;
                g = 0;
                b = 0;
                //for blue
                buffe[i][2] = getc(fIn); 
                //for green
                buffe[i][1] = getc(fIn);
                //for red
                buffe[i][0] = getc(fIn); 

                //Conversion formula of rgb to sepia
                r = (buffe[i][0] * 0.393) + (buffe[i][1] * 0.769) + (buffe[i][2] * 0.189);
                g = (buffe[i][0] * 0.349) + (buffe[i][1] * 0.686) + (buffe[i][2] * 0.168);
                b = (buffe[i][0] * 0.272) + (buffe[i][1] * 0.534) + (buffe[i][2] * 0.131);

                if (r > MAX_VALUE)
                { // if value exceeds
                    r = MAX_VALUE;
                }
                if (g > MAX_VALUE)
                {
                    g = MAX_VALUE;
                }
                if (b > MAX_VALUE)
                {
                    b = MAX_VALUE;
                }
                putc(b, fOut);
                putc(g, fOut);
                putc(r, fOut);
            }

            //Closing the files
            fclose(fOut);
            fclose(fIn);

            stop = clock();
            //Printing the time (clocks_per_sec)
            printf("\nCLOCKS_PER_SEC = %ld\n", stop - start);
            printf("%lf ms\n", ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC);
            break;
        }


        else if (choice == 7)
        { // Copy Image
            // Implement your code here
            clock_t start, stop;

            start = clock(); // Note the start time for profiling purposes.

            FILE *fo = fopen("images/lena_copy.bmp", "wb"); // Output File name

            int i;

            FILE *streamIn;
            streamIn = fopen("images/lena512.bmp", "r"); // Input file name

            if (streamIn == (FILE *)0) // check if the input file has not been opened succesfully.
            {
                printf("File opening error ocurred. Exiting program.\n");
                exit(0);
            }

            unsigned char header[54];       // to store the image header
            unsigned char colorTable[1024]; // to store the colorTable, if it exists.

            int count = 0;
            for (i = 0; i < 54; i++)
            {
                header[i] = getc(streamIn); // strip out BMP header
            }
            int width = *(int *)&header[18];    // read the width from the image header
            int height = *(int *)&header[22];   // read the height from the image header
            int bitDepth = *(int *)&header[28]; // read the bitDepth from the image header

            if (bitDepth <= 8)
                fread(colorTable, sizeof(unsigned char), 1024, streamIn);

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            fwrite(header, sizeof(unsigned char), 54, fo); // write the image header to output file

            unsigned char buf[height * width]; // to store the image data

            fread(buf, sizeof(unsigned char), (height * width), streamIn);

            if (bitDepth <= 8)
                fwrite(colorTable, sizeof(unsigned char), 1024, fo);

            fwrite(buf, sizeof(unsigned char), (height * width), fo);

            fclose(fo);
            fclose(streamIn);

            stop = clock();

            printf("Time: %lf ms\n", ((double)(stop - start) * 1000.0) / CLOCKS_PER_SEC);
            break;
        }

        else if (choice == 8)
        { // Darken Image
            // Implement your code here
            FILE *fIn = fopen("lena512.bmp", "r");     // Input File name
            FILE *fOut = fopen("lena_dark.bmp", "w+"); // Output File name

            int i;
            unsigned char byte[54], colorTable[1024];

            if (fIn == NULL) // check if the input file has not been opened succesfully.
            {
                printf("File does not exist.\n");
            }

            for (i = 0; i < 54; i++) // read the 54 byte header from fIn
            {
                byte[i] = getc(fIn);
            }

            fwrite(byte, sizeof(unsigned char), 54, fOut); // write the header back

            // extract image height, width and bitDepth from imageHeader
            int height = *(int *)&byte[18];
            int width = *(int *)&byte[22];
            int bitDepth = *(int *)&byte[28];

            printf("width: %d\n", width);
            printf("height: %d\n", height);

            int size = height * width; // calculate image size

            if (bitDepth <= 8) // if ColorTable present, extract it.
            {
                fread(colorTable, sizeof(unsigned char), 1024, fIn);
                fwrite(colorTable, sizeof(unsigned char), 1024, fOut);
            }

            unsigned char buffer[size]; // to store the image data

            fread(buffer, sizeof(unsigned char), size, fIn); // read image data

            for (i = 0; i < size; i++) // decreasing pixel values to get image bright
            {
                if (buffer[i] > THRESHOLD)
                    buffer[i] = buffer[i] - THRESHOLD;
            }

            fwrite(buffer, sizeof(unsigned char), size, fOut); // write back to the output image

            fclose(fIn);
            fclose(fOut);
            break;
        }

        else if (choice == 9)
        {
            rotate(); // Rotate Image
            break;
        }

        else if (choice == 10)
        { // Negative Image
            clock_t start, stop;
            start = clock();
            FILE *fp = fopen("bb.bmp", "rb"); // read the file//

            unsigned char *imageData;       // to store the image information
            unsigned char *newimageData;    // to store the new image information, i.e. the negative image
            unsigned char imageHeader[54];  // to get the image header
            unsigned char colorTable[1024]; // to get the colortable

            int i, j; // loop counter variables

            fread(imageHeader, sizeof(unsigned char), 54, fp); // read the 54-byte from fp to imageHeader

            // extract image height and width from imageHeader
            int width = *(int *)&imageHeader[18];
            int height = *(int *)&imageHeader[22];
            int bitDepth = *(int *)&imageHeader[28];

            int imgDataSize = width * height; // calculate image size

            imageData = (unsigned char *)malloc(imgDataSize * sizeof(unsigned char)); // allocate the block of memory as big as the image size
            newimageData = (unsigned char *)malloc(imgDataSize * sizeof(unsigned char));

            if (bitDepth <= 8)                                      // COLOR TABLE Present
                fread(colorTable, sizeof(unsigned char), 1024, fp); // read the 1024-byte from fp to colorTable

            fread(imageData, sizeof(unsigned char), imgDataSize, fp);

            // Calculate the mean of the image
            for (i = 0; i < height; i++)
            {
                for (j = 0; j < width; j++)
                {
                    newimageData[i * width + j] = 255 - imageData[i * width + j];
                }
            }

            FILE *fo = fopen("images/lena_negative.bmp", "wb");

            fwrite(imageHeader, sizeof(unsigned char), 54, fo); // write the header back.

            if (bitDepth <= 8)                                       // COLOR TABLE Present
                fwrite(colorTable, sizeof(unsigned char), 1024, fo); // write the color table back

            fwrite(newimageData, sizeof(unsigned char), imgDataSize, fo); // write the values of the negative image.

            fclose(fo);
            fclose(fp);
            stop = clock();
            double d = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
            printf("%lf\n", d);
            // Implement your code here
            break;
        }

        else
        {
            printf("Invalid choice.\n");
            break;
        }
    } while (choice != 10);

    return 0;
}
