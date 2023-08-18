#include "helpers.h"
#include <math.h>
#include <stdlib.h>

void get_pixel(int i, int j, RGBTRIPLE *pixel, int *pixels, int height, int width, RGBTRIPLE image[height][width]);
void gf(int i, int j, int *blue, int *green, int *red, int height, int width, RGBTRIPLE image[height][width], int gf_kernel[3][3],
        int x_index_mapping[3][3], int y_index_mapping[3][3]);
void addColors(int i, int j, int times, int *blue, int *green, int *red, int height, int width, RGBTRIPLE image[height][width]);

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gscolor = round((image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3.0);
            if (gscolor > 255)
            {
                gscolor = 255;
            }
            image[i][j].rgbtBlue = (BYTE) gscolor;
            image[i][j].rgbtGreen = (BYTE) gscolor;
            image[i][j].rgbtRed = (BYTE) gscolor;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width / 2; j++)
        {
            RGBTRIPLE pixelColor;
            int ref = width - j - 1;
            pixelColor.rgbtBlue = image[i][j].rgbtBlue;
            pixelColor.rgbtGreen = image[i][j].rgbtGreen;
            pixelColor.rgbtRed = image[i][j].rgbtRed;
            image[i][j].rgbtBlue = image[i][ref].rgbtBlue;
            image[i][j].rgbtGreen = image[i][ref].rgbtGreen;
            image[i][j].rgbtRed = image[i][ref].rgbtRed;
            image[i][ref].rgbtBlue = pixelColor.rgbtBlue;
            image[i][ref].rgbtGreen = pixelColor.rgbtGreen;
            image[i][ref].rgbtRed = pixelColor.rgbtRed;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    if (image == NULL)
    {
        return;
    }

    RGBTRIPLE image_cpy[height][width];

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_cpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_cpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_cpy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE intrestPixel[9];
            int pixels = 0;
            get_pixel(i - 1, j - 1, &intrestPixel[0], &pixels, height, width, image_cpy);
            get_pixel(i - 1, j, &intrestPixel[1], &pixels, height, width, image_cpy);
            get_pixel(i - 1, j + 1, &intrestPixel[2], &pixels, height, width, image_cpy);
            get_pixel(i, j - 1, &intrestPixel[3], &pixels, height, width, image_cpy);
            get_pixel(i, j, &intrestPixel[4], &pixels, height, width, image_cpy);
            get_pixel(i, j + 1, &intrestPixel[5], &pixels, height, width, image_cpy);
            get_pixel(i + 1, j - 1, &intrestPixel[6], &pixels, height, width, image_cpy);
            get_pixel(i + 1, j, &intrestPixel[7], &pixels, height, width, image_cpy);
            get_pixel(i + 1, j + 1, &intrestPixel[8], &pixels, height, width, image_cpy);
            float blue = 0, green = 0, red = 0;
            for (int k = 0; k < 9; k++)
            {
                blue += intrestPixel[k].rgbtBlue;
                green += intrestPixel[k].rgbtGreen;
                red += intrestPixel[k].rgbtRed;
            }
            image[i][j].rgbtBlue = (BYTE) round(blue / pixels);
            image[i][j].rgbtGreen = (BYTE) round(green / pixels);
            image[i][j].rgbtRed = (BYTE) round(red / pixels);
        }
    }
    return;
}

void get_pixel(int i, int j, RGBTRIPLE *pixel, int *pixels, int height, int width, RGBTRIPLE image[height][width])
{
    if (i >= 0 && j >= 0 && i < height && j < width)
    {
        pixel->rgbtBlue = image[i][j].rgbtBlue;
        pixel->rgbtGreen = image[i][j].rgbtGreen;
        pixel->rgbtRed = image[i][j].rgbtRed;
        *pixels = *pixels + 1;
    }
    else
    {
        pixel->rgbtBlue = 0;
        pixel->rgbtGreen = 0;
        pixel->rgbtRed = 0;
    }
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    if (image == NULL)
    {
        return;
    }

    RGBTRIPLE image_cpy[height][width];

    int gx_kernel[3][3] = {{-1, 0, 1}, {-2, 0, 2}, {-1, 0, 1}};
    int gy_kernel[3][3] = {{-1, -2, -1}, {0, 0, 0}, {1, 2, 1}};
    int x_index_mapping[3][3] = {{-1, 0, 1}, {-1, 0, 1}, {-1, 0, 1}};
    int y_index_mapping[3][3] = {{-1, -1, -1}, {0, 0, 0}, {1, 1, 1}};
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            image_cpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            image_cpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
            image_cpy[i][j].rgbtRed = image[i][j].rgbtRed;
        }
    }
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int gxblue = 0, gxgreen = 0, gxred = 0;
            gf(i, j, &gxblue, &gxgreen, &gxred, height, width, image_cpy, gx_kernel, x_index_mapping, y_index_mapping);
            int gyblue = 0, gygreen = 0, gyred = 0;
            gf(i, j, &gyblue, &gygreen, &gyred, height, width, image_cpy, gy_kernel, x_index_mapping, y_index_mapping);
            int blue = round(sqrtf((float) pow(gxblue, 2) + (float) pow(gyblue, 2)));
            int green = round(sqrtf((float) pow(gxgreen, 2) + (float) pow(gygreen, 2)));
            int red = round(sqrtf((float) pow(gxred, 2) + (float) pow(gyred, 2)));
            blue = blue > 255 ? 255 : blue;
            green = green > 255 ? 255 : green;
            red = red > 255 ? 255 : red;
            image[i][j].rgbtBlue = (BYTE) blue;
            image[i][j].rgbtGreen = (BYTE) green;
            image[i][j].rgbtRed = (BYTE) red;
        }
    }
    return;
}

void gf(int i, int j, int *blue, int *green, int *red, int height, int width, RGBTRIPLE image[height][width], int gf_kernel[3][3],
        int x_index_mapping[3][3], int y_index_mapping[3][3])
{
    for (int x = 0; x < 3; x++)
    {
        for (int y = 0; y < 3; y++)
        {
            addColors(i - x_index_mapping[x][y], j - y_index_mapping[x][y], gf_kernel[x][y], blue, green, red, height, width,
                      image);
        }
    }
    return;
}

void addColors(int i, int j, int times, int *blue, int *green, int *red, int height, int width, RGBTRIPLE image[height][width])
{
    if (i >= 0 && j >= 0 && i < height && j < width)
    {
        *blue = *blue + (image[i][j].rgbtBlue * times);
        *green = *green + (image[i][j].rgbtGreen * times);
        *red = *red + (image[i][j].rgbtRed * times);
    }
    return;
}
