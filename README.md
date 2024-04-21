# Image Processing in C

## Overview

This project provides an image processing application implemented in C. The application utilizes `main.c` for the main program flow and `filter.c` for various image filtering functions. The project offers functionalities like black and white conversion, RGB to grayscale conversion, brightness adjustment, image blurring, color inversion, and image rotation.

## Files

- **main.c**: Contains the main program flow, user interface, and file handling.
- **filter.c**: Includes various image filtering functions such as black and white conversion, grayscale conversion, brightness adjustment, etc.

## Features

- **Black to White Conversion**: Converts the image to black and white based on a threshold.
- **RGB to Grayscale Conversion**: Converts the image to grayscale using the luminosity method.
- **Brightness Adjustment**: Increases or decreases the brightness of the image.
- **Image Blurring**: Applies a blur filter to the image.
- **Color Inversion**: Inverts the colors of the image.
- **Image Rotation**: Rotates the image by 90 degrees left, right, or 180 degrees.

## Requirements

- C compiler (gcc recommended)
- BMP image files for testing

## Compilation and Execution

1. **Compile the Code**
    ```bash
    gcc b23cm1026_b23ee1005_b23bb1032_b23ci1036main.c b23cm1026_b23ee1005_b23bb1032_b23ci1036filter.c -o image_processing
    ```

2. **Run the Program**
    ```bash
    ./image_processing
    ```

3. **Usage**
    - Follow the on-screen menu to select a filter.
    - Provide the input BMP file name when prompted.
    - The processed image will be saved with a default name or as specified in the code.

## Contributing

 NAMAN SONI(B23CM1026)
 ATANU KAYAL(B23EE1005)
 PRAKHAR CHAUHAN(B23BB1032)
 SOMYA JAINGIR(B23CI1036)


