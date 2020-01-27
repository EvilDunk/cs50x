#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through each pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float average = 0;
            // Average RGB values
            average = round(((float)image[i][j].rgbtRed + (float)image[i][j].rgbtGreen + (float)image[i][j].rgbtBlue) / 3);
            // Set to grayscale
            image[i][j].rgbtRed = average;
            image[i][j].rgbtGreen = average;
            image[i][j].rgbtBlue = average;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE rowtemp[height][width];
    // Loop through rows
    for (int i = 0; i < height; i++)
    {
        // For each row
        for (int j = 0; j < width; j++)
        {
            // Read whole row to temporary array
            rowtemp[i][j] = image[i][j];

        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int k = 0; k < width; k++)
        {
            // Write reverse row to image array
            image[i][k] = rowtemp[i][width - 1 - k];

        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tempimage[height][width];
    // Loop through target pixels
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            // Loop through blur-box
            float redtotal = 0;
            float greentotal = 0;
            float bluetotal = 0;
            float blurcount = 0;

            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    // Determine if blur pixel is valid
                    if (i - 1 + k >= 0 && j - 1 + l >= 0 && i - 1 + k < height && j - 1 + l < width)
                    {
                        // Add RGB totals, increment RGB counts
                        redtotal += image[i - 1 + k][j - 1 + l].rgbtRed;
                        greentotal += image[i - 1 + k][j - 1 + l].rgbtGreen;
                        bluetotal += image[i - 1 + k][j - 1 + l].rgbtBlue;
                        blurcount++;
                    }
                }

            }
            // Calculate average and write to target pixel
            tempimage[i][j].rgbtRed = round(redtotal / blurcount);
            tempimage[i][j].rgbtGreen = round(greentotal / blurcount);
            tempimage[i][j].rgbtBlue = round(bluetotal / blurcount);

        }

    }
    // Loop through target pixels and write from tempimage
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = tempimage[i][j].rgbtRed;
            image[i][j].rgbtGreen = tempimage[i][j].rgbtGreen;
            image[i][j].rgbtBlue = tempimage[i][j].rgbtBlue;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    // Setup arrays and variables
    int gx[3][3] =
    {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    int gy[3][3] =
    {
        {-1, -2, -1},
        {0, 0, 0},
        {1, 2, 1}
    };
    RGBTRIPLE temp[height][width];

    // Loop through target pixel
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            float redtotalgx = 0;
            float greentotalgx = 0;
            float bluetotalgx = 0;
            float redtotalgy = 0;
            float greentotalgy = 0;
            float bluetotalgy = 0;
            // Loop through adjacent pixels
            for (int k = 0; k < 3; k++)
            {
                for (int l = 0; l < 3; l++)
                {
                    // Determine if adjacent pixel is valid
                    if (i - 1 + k >= 0 && j - 1 + l >= 0 && i - 1 + k < height && j - 1 + l < width)
                    {
                        // Take each color and multiply by kernel Gx
                        float redgx = image[i - 1 + k][j - 1 + l].rgbtRed * gx[k][l];
                        float greengx = image[i - 1 + k][j - 1 + l].rgbtGreen * gx[k][l];
                        float bluegx = image[i - 1 + k][j - 1 + l].rgbtBlue * gx[k][l];

                        // Take each color and mulltply by kernel Gy
                        float redgy = image[i - 1 + k][j - 1 + l].rgbtRed * gy[k][l];
                        float greengy = image[i - 1 + k][j - 1 + l].rgbtGreen * gy[k][l];
                        float bluegy = image[i - 1 + k][j - 1 + l].rgbtBlue * gy[k][l];



                        redtotalgx = redtotalgx + redgx;
                        greentotalgx = greentotalgx + greengx;
                        bluetotalgx = bluetotalgx + bluegx;
                        redtotalgy = redtotalgy + redgy;
                        greentotalgy = greentotalgy + greengy;
                        bluetotalgy = bluetotalgy + bluegy;
                    }

                }

            }
            // Square, square root, and round Gx Gy
            float redpixel = round(sqrt((redtotalgx * redtotalgx) + (redtotalgy * redtotalgy)));
            float greenpixel = round(sqrt((greentotalgx * greentotalgx) + (greentotalgy * greentotalgy)));
            float bluepixel = round(sqrt((bluetotalgx * bluetotalgx) + (bluetotalgy * bluetotalgy)));

            // Cap values at 255
            if (redpixel >= 255)
            {
                redpixel = 255;
            }
            if (greenpixel >= 255)
            {
                greenpixel = 255;
            }
            if (bluepixel >= 255)
            {
                bluepixel = 255;
            }

            // Write color values to image array
            temp[i][j].rgbtRed = redpixel;
            temp[i][j].rgbtGreen = greenpixel;
            temp[i][j].rgbtBlue = bluepixel;
        }

    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = temp[i][j].rgbtRed;
            image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
            image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
        }
    }
}
