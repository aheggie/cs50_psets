#include <stdarg.h>
#include <math.h>
#include <stdio.h>
#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        // printf("line %i", h+1);
        for (int w = 0; w < width; w++) {
            RGBTRIPLE pixel = image[h][w];
            BYTE greyscale = round((pixel.rgbtGreen + pixel.rgbtRed + pixel.rgbtBlue) / 3.0);
            // printf("%x%x%x ", pixel.rgbtRed, pixel.rgbtGreen, pixel.rgbtBlue);
            image[h][w].rgbtRed = greyscale;
            image[h][w].rgbtGreen = greyscale;
            image[h][w].rgbtBlue = greyscale;

        }
        // printf("\n");
    }
    // printf("h: %i w: %i", height, width);
    return;
}


// Convert image to sepia
BYTE max_255(int integer) {
    return integer > 255 ? 255 : integer;
}

RGBTRIPLE sepia_pixel(RGBTRIPLE input_pixel) {
    RGBTRIPLE output_pixel;
    float originalRed = input_pixel.rgbtRed;
    float originalGreen = input_pixel.rgbtGreen;
    float originalBlue = input_pixel.rgbtBlue;
    output_pixel.rgbtRed = max_255(round(.393 * originalRed + .769 * originalGreen + .189 * originalBlue));
    output_pixel.rgbtGreen = max_255(round(.349 * originalRed + .686 * originalGreen + .168 * originalBlue));
    output_pixel.rgbtBlue = max_255(round(.272 * originalRed + .534 * originalGreen + .131 * originalBlue));

    return output_pixel;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        for (int w = 0; w < width; w++) {

            RGBTRIPLE sepia = sepia_pixel(image[h][w]);

            image[h][w].rgbtRed = sepia.rgbtRed;
            image[h][w].rgbtGreen = sepia.rgbtGreen;
            image[h][w].rgbtBlue = sepia.rgbtBlue;

        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        // printf("line %i", h+1);
        for (int w = 0; w < width/2; w++) {
            int opposite_w = width-1-w;

            RGBTRIPLE pixel = image[h][w];
            RGBTRIPLE opposite_pixel = image[h][opposite_w];

            image[h][w].rgbtRed = opposite_pixel.rgbtRed;
            image[h][w].rgbtGreen = opposite_pixel.rgbtGreen;
            image[h][w].rgbtBlue = opposite_pixel.rgbtBlue;

            image[h][opposite_w].rgbtRed = pixel.rgbtRed;
            image[h][opposite_w].rgbtGreen = pixel.rgbtGreen;
            image[h][opposite_w].rgbtBlue = pixel.rgbtBlue;

        }
        // printf("\n");
    }
    // printf("h: %i w: %i", height, width);
    return;
}

//learned variable arg functions from explanation here https://www.geeksforgeeks.org/variable-length-argument-c/
RGBTRIPLE average_colour(int arg_count,...) {
    //this etc is from stdarg.h
    va_list pixels;
    float redSum = 0.0;
    float greenSum = 0.0;
   float blueSum = 0.0;
   RGBTRIPLE current_pixel, output_pixel;

   /* initialize pixels for number of arguments */
   va_start(pixels, arg_count);

   /* access all the arguments assigned to pixels */
   for (int i = 0; i < arg_count; i++) {
      current_pixel = va_arg(pixels, RGBTRIPLE);
      redSum += current_pixel.rgbtRed;
      greenSum += current_pixel.rgbtGreen;
      blueSum += current_pixel.rgbtBlue;
   }

   /* clean memory reserved for pixels */
   va_end(pixels);

   output_pixel.rgbtRed = max_255(round(redSum/arg_count));
   output_pixel.rgbtGreen = max_255(round(greenSum/arg_count));
   output_pixel.rgbtBlue = max_255(round(blueSum/arg_count));


   return output_pixel;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        // printf("line %i", h+1);
        for (int w = 0; w < width; w++) {
            RGBTRIPLE blur_pixel = image[h][w];
            //top left corner
            if (h == 0 && w == 0)
            {
                blur_pixel = average_colour(4, image[h][w], image[h][w+1], image[h+1][w], image[h+1][w+1]);
            }
            //top right corner
            else if (h == 0 && w == width -1)
            {
                blur_pixel = average_colour(4, image[h][w-1], image[h][w], image[h+1][w-1], image[h+1][w]);
            }
            //bottom left corner
            else if (h == height - 1 && w ==0)
            {
                blur_pixel = average_colour(4, image[h-1][w], image[h-1][w+1], image[h][w], image[h][w+1]);
            }
            //bottom right corner
            else if (h == height - 1 && w == width -1)
            {
                blur_pixel = average_colour(4, image[h-1][w-1], image[h-1][w], image[h][w-1], image[h][w]);
            }
            //left wall
            else if (w == 0)
            {
                blur_pixel = average_colour(6, image[h-1][w], image[h-1][w+1], image[h][w], image[h][w+1], image[h+1][w], image[h+1][w+1]);
            }
            //right wall
            else if (w == width -1)
            {
                blur_pixel = average_colour(6, image[h-1][w-1], image[h-1][w], image[h][w-1], image[h][w], image[h+1][w-1], image[h+1][w]);
            }
            //top wall
            else if (h == 0)
            {
                blur_pixel = average_colour(6, image[h][w-1], image[h][w], image[h][w+1], image[h+1][w-1], image[h+1][w], image[h+1][w+1]);
            }
            //bottom wall
            else if (h == height - 1)
            {
                blur_pixel = average_colour(6, image[h-1][w-1], image[h-1][w], image[h-1][w+1], image[h][w-1], image[h][w], image[h][w+1]);
            }
            else
            {
                blur_pixel = average_colour(9, image[h-1][w-1], image[h-1][w], image[h-1][w+1], image[h][w-1], image[h][w], image[h][w+1], image[h+1][w-1], image[h+1][w], image[h+1][w+1]);
            }
            image[h][w] = blur_pixel;
        }
        // if ((h+1) % 10 == 0) {printf("\n");} else {printf(" ");}
    }
    // printf("h: %i w: %i", height, width);
    return;
}
