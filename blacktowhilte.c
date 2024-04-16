#include <stdio.h>
#define THRESHOLD 128
#define WHITE 255
#define BLACK 0

int main()
{
    int choice,i,j,k;

    do
    {
        printf("Select the filter for Image.");
        printf("1.Black to White.");
        printf("2.RGB to gray");
        scanf("%d", &choice);
    

    switch (choice)
    {
//******************************BLACK TO WHITE*****************************************
    case 1:
        FILE *fIn = fopen("lena512.bmp", "r"); // Input File name
        FILE *fOut = fopen("b_w.bmp", "w+");   // Output File name

        int i;
        unsigned char byte[54];         // to get the image header
        unsigned char colorTable[1024]; // to get the colortable

        if (fIn == NULL) // check if the input file has not been opened succesfully.
        {
            printf("File does not exist.\n");
        }

        for (i = 0; i < 54; i++) // read the 54 byte header from fIn
        {
            byte[i] = getc(fIn);
        }

        fwrite(byte, sizeof(unsigned char), 54, fOut);

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

        for (i = 0; i < size; i++) // store 0(black) and 255(white) values to buffer
        {
            buffer[i] = (buffer[i] > THRESHOLD) ? WHITE : BLACK;
        }

        fwrite(buffer, sizeof(unsigned char), size, fOut); // write back to the output image

        fclose(fIn); 
        fclose(fOut);
        break;
//************************************ RGB TO GRAY ************************************************		
    case 2:
	    FILE *fIN=("lena_color.bmp","r");    //Input File name
	    FilE *fOUT=("lena_gray.bmp","w");    //Output File name

	    int i,j,y;
	    unsigned char byte[54];

	    if(fIN == NULL)
	    {                                                                      // check if the input file has not been opened succesfully.
		printf("File does not exist.\n");
	    }

	    for (i = 0; i<54; i++)                                                  //read the 54 byte header from fIn
	    {                                                
		    byte[i] = getc(fIn);
	    }

	    fwrite(byte, sizeof(unsigned char), 54, fOut);                          //write the header back
		    
	    // extract image height, width and bitDepth from imageHeader

	    int height = *(int*)&byte[18];
	    int width = *(int*)&byte[22];
	    int bitDepth = *(int*)&byte[28]; 

	    printf("width: %d\n", width);
	    printf("height: %d\n", height );

	    int size = height * width;        //calculate image size

	    unsigned char buffer[size][3];         //to store the image data

	    for(i = 0; i<size; i++)									        //RGB to gray
	    {
		y = 0;
		buffer[i][2] = getc(fIn);									//blue
		buffer[i][1] = getc(fIn);									//green
		buffer[i][0] = getc(fIn);									//red
			
		y = (buffer[i][0]*0.3) + (buffer[i][1]*0.59) + (buffer[i][2]*0.11);			//conversion formula of rgb to gray

		putc(y, fOut);
		putc(y, fOut);
		putc(y, fOut);
	    }
	    

	    fclose(fOut);
	    fclose(fIn);

	    stop = clock();
	    printf("\nCLOCKS_PER_SEC = %ld\n", stop-start); 
	    printf("%lf ms\n",((double)(stop-start) * 1000.0)/CLOCKS_PER_SEC );
	    return 0;


	    
	    
		
		
    }
}
while (choice != 6);
    
return 0;
}
