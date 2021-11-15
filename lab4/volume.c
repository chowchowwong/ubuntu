// Modifies the volume of an audio file

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

// Number of bytes in .wav header
const int HEADER_SIZE = 44;

int main(int argc, char *argv[])
{
    // Check command-line arguments
    if (argc != 4)
    {
        printf("Usage: ./volume input.wav output.wav factor\n");
        return 1;
    }

    // Open files and determine scaling factor
    FILE *input = fopen(argv[1], "r");
    if (input == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    FILE *output = fopen(argv[2], "w");
    if (output == NULL)
    {
        printf("Could not open file.\n");
        return 1;
    }

    float factor = atof(argv[3]);

    // TODO: Copy header from input file to output file
    uint8_t header[HEADER_SIZE];

    fread(&header, sizeof(uint8_t), 44, input);
    fwrite(&header,sizeof(uint8_t), 44, output);
    //printf("header: ");
    // for (int i =0; i<44;i++)
    // {
    //     printf("%i",header[i]);
    // }
    // printf("\n");

    // TODO: Read samples from input file and write updated data to output file

    int n =1;
    int body=1;
    //fseek(input, 45, SEEK_SET);
    do
    {
        n=n*10;
        int16_t buffer[n];
        //printf("body = %i\nn changed to %i\n",body,n);
        fseek(input,44,SEEK_SET);
        body = fread(&buffer, sizeof(int16_t), n, input);
        //printf("body = %i\nn changed to %i\n",body,n);
    } while(n==body);
    //printf("body = %i\nn changed to %i\n",body,n);
    int16_t buffer[body];

    fseek(input,44,SEEK_SET);
    fread(&buffer, sizeof(int16_t), n, input);
    //printf("body = %i\nn changed to %i\n",body,n);
    // printf("body: ");
    // for (int i =0; i<3;i++)
    // {
    //     printf("%i__",buffer[i]);
    // }
    // printf("\n");
    for (int i=0;i<body;i++)
    {
        buffer[i]=(int16_t)(buffer[i]*factor);
    }

    //printf("factor: %f\nfactored body: ",factor);
    // for (int i =0; i<3;i++)
    // {
    //     printf("%i__",buffer[i]);
    // }
    // printf("\n");
    fseek(output, 44, SEEK_SET);
    fwrite(&buffer,sizeof(int16_t), body, output);

    // Close files
    fclose(input);
    fclose(output);
}
