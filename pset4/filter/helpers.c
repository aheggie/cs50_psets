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
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++) {
        // printf("line %i", h+1);
        for (int w = 0; w < width/2; w++) {
            int opposite_w = width-w;

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

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    return;
}
