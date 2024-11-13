#include <stdio.h>
#include <string.h>
#include "decode.h"  // Updated to decode.h
#include "types.h"
#include "common.h"

Status open_files_d(DecodeInfo *decInfo)
{ 
    // Open secret file in write mode
    decInfo->fptr_secret = fopen(decInfo->secret_fname, "w");
    if (decInfo->fptr_secret == NULL)  // Error handling for file
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->secret_fname);
        return e_failure;
    }

    // Open stego image file in read mode
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");
    if (decInfo->fptr_stego_image == NULL)  // Error handling for file
    {
        perror("fopen");
        fprintf(stderr, "ERROR: Unable to open file %s\n", decInfo->stego_image_fname);
        return e_failure;
    }

    return e_success;  // Return success if both files opened
}

Status read_and_validate_encode_args_d(char *argv[], DecodeInfo *decInfo)
{
    const char *valid_extensions[] = {".bmp", ".txt"};
    
    // Validate stego image file extension
    if (strstr(argv[2], valid_extensions[0]) == NULL)
    {
        printf("Error: command line argument %d is Invalid\n", 3);
        return e_failure;
    }
    else    
        decInfo->stego_image_fname = argv[2];

    // Set default secret file name if none provided
    if(argv[3] == NULL)
    {
        printf("\033[0;33mINFO:  \033[0;36mArgument of output file not passed, setting default file name.\033[0m\n");
        sleep(1);
        decInfo->secret_fname = "output.txt";
    }
    // Validate secret file extension if provided
    else if (strstr(argv[3], valid_extensions[1]) == NULL)
    {
        printf("Error: command line argument %d is Invalid\n", 4);
        return e_failure;
    }
    else
        decInfo->secret_fname = argv[3];
    
    return e_success;
}

Status decode_byte_from_lsb(char size, DecodeInfo *decInfo, char *image_buffer)
{
    char data = 0;
    for(int j = 0; j < size; j++)  // Decode each byte
    {
        for(int i = 0; i < 8; i++)  // Process 8 LSBs for each byte
        {
            data = (data << 1) | (image_buffer[i] & 1);  // Extract bit and build data byte
        }
        image_buffer += 8;  // Move to next byte in buffer
        decInfo->decoded_data.secret[j] = data;  // Store decoded byte
    }
    return e_success;
}

Status decode_byte_from_lsb_int(DecodeInfo *decInfo, char *image_buffer)
{
    int data = 0;
    for(int i = 0; i < 32; i++)  // Decode 32 LSBs for integer
    {
        data = (data << 1) | (image_buffer[i] & 1);  // Extract bit and build integer
    }
    decInfo->decoded_data.size = data;  // Store decoded integer
    return e_success;
}
