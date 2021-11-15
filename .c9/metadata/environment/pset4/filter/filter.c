{"filter":false,"title":"filter.c","tooltip":"/pset4/filter/filter.c","undoManager":{"mark":-1,"position":-1,"stack":[[{"start":{"row":0,"column":0},"end":{"row":153,"column":0},"action":"remove","lines":["#include <getopt.h>","#include <stdio.h>","#include <stdlib.h>","","#include \"helpers.h\"","","int main(int argc, char *argv[])","{","","    // Define allowable filters","    char *filters = \"begr\";","","    // Get filter flag and check validity","    char filter = getopt(argc, argv, filters);","    if (filter == '?')","    {","        fprintf(stderr, \"Invalid filter.\\n\");","        return 1;","    }","","    // Ensure only one filter","    if (getopt(argc, argv, filters) != -1)","    {","        fprintf(stderr, \"Only one filter allowed.\\n\");","        return 2;","    }","","    // Ensure proper usage","    if (argc != optind + 2)","    {","        fprintf(stderr, \"Usage: filter [flag] infile outfile\\n\");","        return 3;","    }","","    // Remember filenames","    char *infile = argv[optind];","    char *outfile = argv[optind + 1];","","    // Open input file","    FILE *inptr = fopen(infile, \"r\");","    if (inptr == NULL)","    {","        fprintf(stderr, \"Could not open %s.\\n\", infile);","        return 4;","    }","","    // Open output file","    FILE *outptr = fopen(outfile, \"w\");","    if (outptr == NULL)","    {","        fclose(inptr);","        fprintf(stderr, \"Could not create %s.\\n\", outfile);","        return 5;","    }","","    // Read infile's BITMAPFILEHEADER","    BITMAPFILEHEADER bf;","    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);","","    // Read infile's BITMAPINFOHEADER","    BITMAPINFOHEADER bi;","    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);","","    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0","    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||","        bi.biBitCount != 24 || bi.biCompression != 0)","    {","        fclose(outptr);","        fclose(inptr);","        fprintf(stderr, \"Unsupported file format.\\n\");","        return 6;","    }","","    int height = abs(bi.biHeight);","    int width = bi.biWidth;","","    // Allocate memory for image","    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));","    if (image == NULL)","    {","        fprintf(stderr, \"Not enough memory to store image.\\n\");","        fclose(outptr);","        fclose(inptr);","        return 7;","    }","","    // Determine padding for scanlines","    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;","","    // Iterate over infile's scanlines","    for (int i = 0; i < height; i++)","    {","        // Read row into pixel array","        fread(image[i], sizeof(RGBTRIPLE), width, inptr);","","        // Skip over padding","        fseek(inptr, padding, SEEK_CUR);","    }","","    // Filter image","    switch (filter)","    {","        // Blur","        case 'b':","            blur(height, width, image);","            break;","","        // Edges","        case 'e':","            edges(height, width, image);","            break;","","        // Grayscale","        case 'g':","            grayscale(height, width, image);","            break;","","        // Reflect","        case 'r':","            reflect(height, width, image);","            break;","    }","","    // Write outfile's BITMAPFILEHEADER","    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);","","    // Write outfile's BITMAPINFOHEADER","    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);","","    // Write new pixels to outfile","    for (int i = 0; i < height; i++)","    {","        // Write row to outfile","        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);","","        // Write padding at end of row","        for (int k = 0; k < padding; k++)","        {","            fputc(0x00, outptr);","        }","    }","","    // Free memory for image","    free(image);","","    // Close infile","    fclose(inptr);","","    // Close outfile","    fclose(outptr);","","    return 0;","}",""],"id":1},{"start":{"row":0,"column":0},"end":{"row":258,"column":1},"action":"insert","lines":["#include \"helpers.h\"","#include \"math.h\"","#include <stdio.h>","","// Convert copy to grayscale","void grayscale(int height, int width, RGBTRIPLE image[height][width])","{","    RGBTRIPLE copy[height][width];","    for (int i=0;i<height;i++)","    {","        for (int j=0;j<width;j++)","        {","            copy[i][j]=image[i][j];","            int sum = copy[i][j].rgbtRed+copy[i][j].rgbtGreen+copy[i][j].rgbtBlue;","            int avg = sum/3;","            if (avg>255)","            {","                avg=255;","            }","            image[i][j].rgbtRed=avg;","            image[i][j].rgbtGreen=avg;","            image[i][j].rgbtBlue =avg;","        }","    }","    return;","}","","// Reflect copy horizontally","void reflect(int height, int width, RGBTRIPLE image[height][width])","{","    int mid=floor((width-1)/2);","    RGBTRIPLE right[height][width-mid];","    for (int i=0;i<height;i++)","    {","        for (int j=0;j<=width-1-mid-1;j++)","        {","            right[i][j]=image[i][width-1-j];","            image[i][width-1-j]=image[i][j];","            image[i][j]=right[i][j];","        }","    }","    return;","}","","// Blur copy","void blur(int height, int width, RGBTRIPLE image[height][width])","{","    RGBTRIPLE copy[height][width];","    for (int i=0; i<height;i++)","    {","        for (int j=0;j<width;j++)","        {","            copy[i][j]=image[i][j];","        }","    }","    for (int i=0; i<height;i++)","    {","        for (int j=0;j<width;j++)","        {","            int sum_rgbtRed=0;","            int sum_rgbtGreen=0;","            int sum_rgbtBlue=0;","            int count =0;","            if ((i-1)>=0)","            {","                sum_rgbtRed+=copy[i-1][j].rgbtRed;","                sum_rgbtGreen+=copy[i-1][j].rgbtGreen;","                sum_rgbtBlue+=copy[i-1][j].rgbtBlue;","                count++;","                if(j-1>=0)","                {","                    sum_rgbtRed+=copy[i-1][j-1].rgbtRed;","                    sum_rgbtGreen+=copy[i-1][j-1].rgbtGreen;","                    sum_rgbtBlue+=copy[i-1][j-1].rgbtBlue;","                    count++;","                }","                if(j+1<width)","                {","                    sum_rgbtRed+=copy[i-1][j+1].rgbtRed;","                    sum_rgbtGreen+=copy[i-1][j+1].rgbtGreen;","                    sum_rgbtBlue+=copy[i-1][j+1].rgbtBlue;","                    count++;","                }","            }","            sum_rgbtRed+=copy[i][j].rgbtRed;","            sum_rgbtGreen+=copy[i][j].rgbtGreen;","            sum_rgbtBlue+=copy[i][j].rgbtBlue;","            count++;","            if(j-1>=0)","            {","                sum_rgbtRed+=copy[i][j-1].rgbtRed;","                sum_rgbtGreen+=copy[i][j-1].rgbtGreen;","                sum_rgbtBlue+=copy[i][j-1].rgbtBlue;","                count++;","            }","            if(j+1<width)","            {","                sum_rgbtRed+=copy[i][j+1].rgbtRed;","                sum_rgbtGreen+=copy[i][j+1].rgbtGreen;","                sum_rgbtBlue+=copy[i][j+1].rgbtBlue;","                count++;","            }","            if (i+1<height)","            {","                sum_rgbtRed+=copy[i+1][j].rgbtRed;","                sum_rgbtGreen+=copy[i+1][j].rgbtGreen;","                sum_rgbtBlue+=copy[i+1][j].rgbtBlue;","                count++;","                if(j-1>=0)","                {","                    sum_rgbtRed+=copy[i+1][j-1].rgbtRed;","                    sum_rgbtGreen+=copy[i+1][j-1].rgbtGreen;","                    sum_rgbtBlue+=copy[i+1][j-1].rgbtBlue;","                    count++;","                }","                if(j+1<width)","                {","                    sum_rgbtRed+=copy[i+1][j+1].rgbtRed;","                    sum_rgbtGreen+=copy[i+1][j+1].rgbtGreen;","                    sum_rgbtBlue+=copy[i+1][j+1].rgbtBlue;","                    count++;","                }","            }","            int avg_rgbtRed = round(sum_rgbtRed/count);","            int avg_rgbtGreen = round(sum_rgbtGreen/count);","            int avg_rgbtBlue = round(sum_rgbtBlue/count);","            if (avg_rgbtRed>255)","            {","                avg_rgbtRed=255;","            }","            if (avg_rgbtGreen>255)","            {","                avg_rgbtGreen=255;","            }","            if (avg_rgbtBlue>255)","            {","                avg_rgbtBlue=255;","            }","            image[i][j].rgbtRed=avg_rgbtRed;","            image[i][j].rgbtGreen=avg_rgbtGreen;","            image[i][j].rgbtBlue=avg_rgbtBlue;","        }","    }","    return;","}","","// Detect edges","void edges(int height, int width, RGBTRIPLE image[height][width])","{","    int gxr=0;","    int gxg=0;","    int gxb=0;","    int gyr=0;","    int gyg=0;","    int gyb =0;","    RGBTRIPLE copy[height][width];","    for (int i=0; i<height;i++)","    {","        for (int j=0;j<width;j++)","        {","            copy[i][j]=image[i][j];","        }","    }","    for (int i=0;i<height;i++)","    {","        for(int j=0;j<width;j++)","        {","            printf(\"%i,%i,%i__\", copy[i][j].rgbtRed,copy[i][j].rgbtGreen,copy[i][j].rgbtBlue);","        }","        printf(\"\\n\");","    }  ","    for (int i=0; i<height;i++)","    {","        for (int j=0;j<width;j++)","        {","            if (j-1>=0)","            {","                gxr+=copy[i][j-1].rgbtRed*-2;","                gxg+=copy[i][j-1].rgbtGreen*-2;","                gxb+=copy[i][j-1].rgbtBlue*-2;","                printf(\"gxr: %i gyr: %i\\n\",gxr,gyr);","            }","            if (j+1<width)","            {","                gxr+=copy[i][j+1].rgbtRed*2;","                gxg+=copy[i][j+1].rgbtGreen*2;","                gxb+=copy[i][j+1].rgbtBlue*2;","                printf(\"gxr: %i gyr: %i\\n\",gxr,gyr);","                if (i-1>=0)","                {","                    gxr+=copy[i-1][j+1].rgbtRed*1;","                    gxg+=copy[i-1][j+1].rgbtGreen*1;","                    gxb+=copy[i-1][j+1].rgbtBlue*1;","                    gyr+=copy[i-1][j+1].rgbtRed*-1;","                    gyg+=copy[i-1][j+1].rgbtGreen*-1;","                    gyb+=copy[i-1][j+1].rgbtBlue*-1;","                    printf(\"gxr: %i gyr: %i\\n\",gxr,gyr);","                }","                if (i+1<height)","                {","                    gxr+=copy[i+1][j+1].rgbtRed*1;","                    gxg+=copy[i+1][j+1].rgbtGreen*1;","                    gxb+=copy[i+1][j+1].rgbtBlue*1;","                    gyr+=copy[i+1][j+1].rgbtRed*1;","                    gyg+=copy[i+1][j+1].rgbtGreen*1;","                    gyb+=copy[i+1][j+1].rgbtBlue*1;","                    printf(\"gxr: %i gyr: %i\\n\",gxr,gyr);","                }","            }","            if (i-1>=0)","            {","                gyr+=copy[i-1][j].rgbtRed*-2;","                gyg+=copy[i-1][j].rgbtGreen*-2;","                gyb+=copy[i-1][j].rgbtBlue*-2;","                printf(\"gxr: %i gyr: %i\\n\",gxr,gyr);","                if (j-1>=0)","                {","                    gxr+=copy[i-1][j-1].rgbtRed*-1;","                    gxg+=copy[i-1][j-1].rgbtGreen*-1;","                    gxb+=copy[i-1][j-1].rgbtBlue*-1;","                    gyr+=copy[i-1][j-1].rgbtRed*-1;","                    gyg+=copy[i-1][j-1].rgbtGreen*-1;","                    gyb+=copy[i-1][j-1].rgbtBlue*-1;","                    printf(\"gxr: %i gyr: %i\\n\",gxr,gyr);","                }","            }","            if (i+1<height)","            {","                gyr+=copy[i+1][j].rgbtRed*2;","                gyg+=copy[i+1][j].rgbtGreen*2;","                gyb+=copy[i+1][j].rgbtBlue*2;","                printf(\"gxr: %i gyr: %i\\n\",gxr,gyr);","                if (j-1>=0)","                {  ","                    gxr+=copy[i+1][j-1].rgbtRed*-1;","                    gxg+=copy[i+1][j-1].rgbtGreen*-1;","                    gxb+=copy[i+1][j-1].rgbtBlue*-1;","                    gyr+=copy[i+1][j-1].rgbtRed*1;","                    gyg+=copy[i+1][j-1].rgbtGreen*1;","                    gyb+=copy[i+1][j-1].rgbtBlue*1;","                    printf(\"gxr: %i gyr: %i\\n\",gxr,gyr);","                }","            }","            int red=round(sqrt(pow(gxr,2)+pow(gyr,2)));","            int green=round(sqrt(pow(gxg,2)+pow(gyg,2)));","            int blue=round(sqrt(pow(gxb,2)+pow(gyb,2)));","            printf(\"red: %i\\n\",red);","            if (red>255){red=255;}","            if (green>255){red=255;}","            if (blue>255){red=255;}","            image[i][j].rgbtRed=red;","            image[i][j].rgbtGreen =green;","            image[i][j].rgbtBlue =blue;","            printf(\"red: %i image[%i][%i]\\n\",red,i,j);","        }","    }","    ","    return;","}"]}]]},"ace":{"folds":[],"scrolltop":1141,"scrollleft":0,"selection":{"start":{"row":0,"column":0},"end":{"row":153,"column":0},"isBackwards":false},"options":{"guessTabSize":true,"useWrapMode":false,"wrapToView":true},"firstLineState":{"row":223,"mode":"ace/mode/c_cpp"}},"timestamp":1636981658761,"hash":"8e395e2bf1b8652e48a2b5aedcf6c0ff342e5ca0"}