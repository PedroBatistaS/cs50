#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int rgb_m = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = rgb_m;
            image[i][j].rgbtGreen = rgb_m;
            image[i][j].rgbtBlue = rgb_m;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int blue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 *
                             image[i][j].rgbtBlue);  // The formula for sepian
            int green = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 *
                              image[i][j].rgbtBlue); // The formula for sepian
            int red = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 *
                            image[i][j].rgbtBlue);   // The formula for sepian

            // using the formula and check that is less than the max
            if (red > 255)
            {
                image[i][j].rgbtRed = 255;
            }
            else
            {
                image[i][j].rgbtRed = red;
            }

            if (green > 255)
            {
                image[i][j].rgbtGreen = 255;
            }
            else
            {
                image[i][j].rgbtGreen = green;
            }

            if (blue > 255)
            {
                image[i][j].rgbtBlue = 255;
            }
            else
            {
                image[i][j].rgbtBlue = blue;
            }

        }
    }
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        if (width % 2 == 0)
        {
            for (int j = 0; j < width / 2; j++) // even
            {
                // Auxiliar
                RGBTRIPLE t[height][width];
                t[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = t[i][j];
            }
        }
        else if (width % 2 != 0)
        {
            for (int j = 0; j < (width - 1) / 2; j++) // odd
            {
                // Auxiliar
                RGBTRIPLE t[height][width];
                t[i][j] = image[i][j];
                image[i][j] = image[i][width - (j + 1)];
                image[i][width - (j + 1)] = t[i][j];
            }
        }
    }
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    // Auxiliar
    RGBTRIPLE t[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            //Variables
            float red = 0;
            float green = 0;
            float blue = 0;
            float count = 0;

            // go across the image
            for (int k = -1; k < 2; k++)
            {
                for (int z = -1; z < 2; z++)
                {
                    if (i + k < 0 || i + k > height - 1)
                    {
                        continue;
                    }
                    if (j + z < 0 || j + z > width - 1)
                    {
                        continue;
                    }

                    red += image[i + k][j + z].rgbtRed;
                    blue += image[i + k][j + z].rgbtBlue;
                    green += image[i + k][j + z].rgbtGreen;
                    count++;
                }
            }

            t[i][j].rgbtRed = round(red / count);
            t[i][j].rgbtBlue = round(blue / count);
            t[i][j].rgbtGreen = round(green / count);
        }
    }

    // pass the values from auxiliar to the image
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image[i][j].rgbtRed = t[i][j].rgbtRed;
            image[i][j].rgbtBlue = t[i][j].rgbtBlue;
            image[i][j].rgbtGreen = t[i][j].rgbtGreen;
        }
    }
}
