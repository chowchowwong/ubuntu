#include "helpers.h"
#include "math.h"
#include <stdio.h>

// Convert copy to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            copy[i][j]=image[i][j];
            int sum = copy[i][j].rgbtRed+copy[i][j].rgbtGreen+copy[i][j].rgbtBlue;
            int avg = round(sum/3.0);
            if (avg>255)
            {
                avg=255;
            }
            image[i][j].rgbtRed=avg;
            image[i][j].rgbtGreen=avg;
            image[i][j].rgbtBlue =avg;
        }
    }
    return;
}

// Reflect copy horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int mid=floor((width-1)/2);
    RGBTRIPLE right[height][width-mid];
    for (int i=0;i<height;i++)
    {
        for (int j=0;j<=width-1-mid-1;j++)
        {
            right[i][j]=image[i][width-1-j];
            image[i][width-1-j]=image[i][j];
            image[i][j]=right[i][j];
        }
    }
    return;
}

// Blur copy
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    for (int i=0; i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            copy[i][j]=image[i][j];
        }
    }
    for (int i=0; i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            int sum_rgbtRed=0;
            int sum_rgbtGreen=0;
            int sum_rgbtBlue=0;
            double count =0;
            if ((i-1)>=0)
            {
                sum_rgbtRed+=copy[i-1][j].rgbtRed;
                sum_rgbtGreen+=copy[i-1][j].rgbtGreen;
                sum_rgbtBlue+=copy[i-1][j].rgbtBlue;
                count++;
                if(j-1>=0)
                {
                    sum_rgbtRed+=copy[i-1][j-1].rgbtRed;
                    sum_rgbtGreen+=copy[i-1][j-1].rgbtGreen;
                    sum_rgbtBlue+=copy[i-1][j-1].rgbtBlue;
                    count++;
                }
                if(j+1<width)
                {
                    sum_rgbtRed+=copy[i-1][j+1].rgbtRed;
                    sum_rgbtGreen+=copy[i-1][j+1].rgbtGreen;
                    sum_rgbtBlue+=copy[i-1][j+1].rgbtBlue;
                    count++;
                }
            }
            sum_rgbtRed+=copy[i][j].rgbtRed;
            sum_rgbtGreen+=copy[i][j].rgbtGreen;
            sum_rgbtBlue+=copy[i][j].rgbtBlue;
            count++;
            if(j-1>=0)
            {
                sum_rgbtRed+=copy[i][j-1].rgbtRed;
                sum_rgbtGreen+=copy[i][j-1].rgbtGreen;
                sum_rgbtBlue+=copy[i][j-1].rgbtBlue;
                count++;
            }
            if(j+1<width)
            {
                sum_rgbtRed+=copy[i][j+1].rgbtRed;
                sum_rgbtGreen+=copy[i][j+1].rgbtGreen;
                sum_rgbtBlue+=copy[i][j+1].rgbtBlue;
                count++;
            }
            if (i+1<height)
            {
                sum_rgbtRed+=copy[i+1][j].rgbtRed;
                sum_rgbtGreen+=copy[i+1][j].rgbtGreen;
                sum_rgbtBlue+=copy[i+1][j].rgbtBlue;
                count++;
                if(j-1>=0)
                {
                    sum_rgbtRed+=copy[i+1][j-1].rgbtRed;
                    sum_rgbtGreen+=copy[i+1][j-1].rgbtGreen;
                    sum_rgbtBlue+=copy[i+1][j-1].rgbtBlue;
                    count++;
                }
                if(j+1<width)
                {
                    sum_rgbtRed+=copy[i+1][j+1].rgbtRed;
                    sum_rgbtGreen+=copy[i+1][j+1].rgbtGreen;
                    sum_rgbtBlue+=copy[i+1][j+1].rgbtBlue;
                    count++;
                }
            }
            int avg_rgbtRed = round(sum_rgbtRed/count);
            int avg_rgbtGreen = round(sum_rgbtGreen/count);
            int avg_rgbtBlue = round(sum_rgbtBlue/count);
            if (avg_rgbtRed>255)
            {
                avg_rgbtRed=255;
            }
            if (avg_rgbtGreen>255)
            {
                avg_rgbtGreen=255;
            }
            if (avg_rgbtBlue>255)
            {
                avg_rgbtBlue=255;
            }
            image[i][j].rgbtRed=avg_rgbtRed;
            image[i][j].rgbtGreen=avg_rgbtGreen;
            image[i][j].rgbtBlue=avg_rgbtBlue;
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int gxr=0;
    int gxg=0;
    int gxb=0;
    int gyr=0;
    int gyg=0;
    int gyb =0;
    RGBTRIPLE copy[height][width];
    for (int i=0; i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            copy[i][j]=image[i][j];
        }
    }
    for (int i=0;i<height;i++)
    {
        for(int j=0;j<width;j++)
        {
            //printf("%i,%i,%i__", copy[i][j].rgbtRed,copy[i][j].rgbtGreen,copy[i][j].rgbtBlue);
        }
        //printf("\n");
    }
    for (int i=0; i<height;i++)
    {
        for (int j=0;j<width;j++)
        {
            gxr=0;
            gxg=0;
            gxb=0;
            gyr=0;
            gyg=0;
            gyb =0;
            if (j-1>=0)
            {
                gxr+=copy[i][j-1].rgbtRed*-2;
                gxg+=copy[i][j-1].rgbtGreen*-2;
                gxb+=copy[i][j-1].rgbtBlue*-2;
                //printf("gxr: %i gyr: %i\n",gxr,gyr);
            }
            if (j+1<width)
            {
                gxr+=copy[i][j+1].rgbtRed*2;
                gxg+=copy[i][j+1].rgbtGreen*2;
                gxb+=copy[i][j+1].rgbtBlue*2;
                //printf("gxr: %i gyr: %i\n",gxr,gyr);
                if (i-1>=0)
                {
                    gxr+=copy[i-1][j+1].rgbtRed*1;
                    gxg+=copy[i-1][j+1].rgbtGreen*1;
                    gxb+=copy[i-1][j+1].rgbtBlue*1;
                    gyr+=copy[i-1][j+1].rgbtRed*-1;
                    gyg+=copy[i-1][j+1].rgbtGreen*-1;
                    gyb+=copy[i-1][j+1].rgbtBlue*-1;
                    //printf("gxr: %i gyr: %i\n",gxr,gyr);
                }
                if (i+1<height)
                {
                    gxr+=copy[i+1][j+1].rgbtRed*1;
                    gxg+=copy[i+1][j+1].rgbtGreen*1;
                    gxb+=copy[i+1][j+1].rgbtBlue*1;
                    gyr+=copy[i+1][j+1].rgbtRed*1;
                    gyg+=copy[i+1][j+1].rgbtGreen*1;
                    gyb+=copy[i+1][j+1].rgbtBlue*1;
                    //printf("gxr: %i gyr: %i\n",gxr,gyr);
                }
            }
            if (i-1>=0)
            {
                gyr+=copy[i-1][j].rgbtRed*-2;
                gyg+=copy[i-1][j].rgbtGreen*-2;
                gyb+=copy[i-1][j].rgbtBlue*-2;
                //printf("gxr: %i gyr: %i\n",gxr,gyr);
                if (j-1>=0)
                {
                    gxr+=copy[i-1][j-1].rgbtRed*-1;
                    gxg+=copy[i-1][j-1].rgbtGreen*-1;
                    gxb+=copy[i-1][j-1].rgbtBlue*-1;
                    gyr+=copy[i-1][j-1].rgbtRed*-1;
                    gyg+=copy[i-1][j-1].rgbtGreen*-1;
                    gyb+=copy[i-1][j-1].rgbtBlue*-1;
                    //printf("gxr: %i gyr: %i\n",gxr,gyr);
                }
            }
            if (i+1<height)
            {
                gyr+=copy[i+1][j].rgbtRed*2;
                gyg+=copy[i+1][j].rgbtGreen*2;
                gyb+=copy[i+1][j].rgbtBlue*2;
                //printf("gxr: %i gyr: %i\n",gxr,gyr);
                if (j-1>=0)
                {
                    gxr+=copy[i+1][j-1].rgbtRed*-1;
                    gxg+=copy[i+1][j-1].rgbtGreen*-1;
                    gxb+=copy[i+1][j-1].rgbtBlue*-1;
                    gyr+=copy[i+1][j-1].rgbtRed*1;
                    gyg+=copy[i+1][j-1].rgbtGreen*1;
                    gyb+=copy[i+1][j-1].rgbtBlue*1;
                    //printf("gxr: %i gyr: %i\n",gxr,gyr);
                }
            }
            int red=round(sqrt(pow(gxr,2)+pow(gyr,2)));
            int green=round(sqrt(pow(gxg,2)+pow(gyg,2)));
            int blue=round(sqrt(pow(gxb,2)+pow(gyb,2)));
            //printf("red: %i\n",red);
            if (red>255){red=255;}
            if (green>255){green=255;}
            if (blue>255){blue=255;}
            image[i][j].rgbtRed=red;
            image[i][j].rgbtGreen =green;
            image[i][j].rgbtBlue =blue;
            //printf("red: %i image[%i][%i]\n",red,i,j);
        }  
    }

    return;
}