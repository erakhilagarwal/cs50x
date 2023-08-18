#include "helpers.h"
#include <math.h>
#include <stdio.h>

void get_pixel(int i, int j, RGBTRIPLE *pixel, int *pixels, int height, int width, RGBTRIPLE image[height][width]);

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

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            RGBTRIPLE pixelColor;
            pixelColor.rgbtBlue = image[i][j].rgbtBlue;
            pixelColor.rgbtGreen = image[i][j].rgbtGreen;
            pixelColor.rgbtRed = image[i][j].rgbtRed;
            // sepiaRed = .393 * originalRed + .769 * originalGreen + .189 * originalBlue
            // sepiaGreen = .349 * originalRed + .686 * originalGreen + .168 * originalBlue
            // sepiaBlue = .272 * originalRed + .534 * originalGreen + .131 * originalBlue
            int sepiaBlue = round(0.272 * pixelColor.rgbtRed + 0.534 * pixelColor.rgbtGreen + 0.131 * pixelColor.rgbtBlue);
            int sepiaGreen = round(0.349 * pixelColor.rgbtRed + 0.686 * pixelColor.rgbtGreen + 0.168 * pixelColor.rgbtBlue);
            int sepiaRed = round(0.393 * pixelColor.rgbtRed + 0.769 * pixelColor.rgbtGreen + 0.189 * pixelColor.rgbtBlue);
            image[i][j].rgbtBlue = (BYTE) (sepiaBlue > 255 ? 255 : sepiaBlue);
            image[i][j].rgbtGreen = (BYTE) (sepiaGreen > 255 ? 255 : sepiaGreen);
            image[i][j].rgbtRed = (BYTE) (sepiaRed > 255 ? 255 : sepiaRed);
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
    RGBTRIPLE image_cpy[height][width];
    if (image == NULL)
    {
        return;
    }

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
