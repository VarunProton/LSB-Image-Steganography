#include <stdio.h>
#include <string.h>
#include "decode.h"  // Updated to decode.h
#include "types.h"
#include "common.h"

Status decode_magic_string(DecodeInfo *decInfo)
{
    char data[16];
    fseek(decInfo->fptr_stego_image, 54, SEEK_SET);  // Move to BMP data section
    if (fread(data, 16, 1, decInfo->fptr_stego_image) != 1)  // Read 16 bytes for magic string
    {
        printf("Error: The data from coded image is not copied\n");
        return e_failure;
    }

    // Decode magic string from LSBs
    if (decode_byte_from_lsb(strlen(MAGIC_STRING), decInfo, data) != e_success)
    {
        printf("Error: When the process of byte to lsb is done\n");
        return e_failure;
    }
    return e_success;
}

Status decode_secret_file_extn_size(DecodeInfo *decInfo)
{
    char data[32];
    if (fread(data, 32, 1, decInfo->fptr_stego_image) != 1)  // Read 32 bits for extension size
    {
        printf("Error: The data from coded image is not copied\n");
        return e_failure;
    }

    // Decode extension size from LSBs
    if (decode_byte_from_lsb_int(decInfo, data) != e_success)
    {
        printf("Error: When the process of byte to lsb is done\n");
        return e_failure;
    }
    return e_success;
}

Status decode_secret_file_extn(DecodeInfo *decInfo)
{
    char data[decInfo->decoded_data.size * 8];
    if (fread(data, decInfo->decoded_data.size * 8, 1, decInfo->fptr_stego_image) != 1)  // Read bytes for file extension
    {
        printf("Error: The data from coded image is not copied\n");
        return e_failure;
    }

    // Decode file extension from LSBs
    if (decode_byte_from_lsb(decInfo->decoded_data.size, decInfo, data) != e_success)
    {
        printf("Error: When the process of byte to lsb is done\n");
        return e_failure;
    }
    return e_success;
}

Status decode_secret_file_size(DecodeInfo *decInfo)
{
    char data[32];
    if (fread(data, 32, 1, decInfo->fptr_stego_image) != 1)  // Read 32 bits for file size
    {
        printf("Error: The data from coded image is not copied\n");
        return e_failure;
    }

    // Decode file size from LSBs
    if (decode_byte_from_lsb_int(decInfo, data) != e_success)
    {
        printf("Error: When the process of byte to lsb is done\n");
        return e_failure;
    }
    return e_success;
}

Status decode_secret_file_data(DecodeInfo *decInfo)
{
    char data[decInfo->decoded_data.size * 8];
    if (fread(data, decInfo->decoded_data.size * 8, 1, decInfo->fptr_stego_image) != 1)  // Read bytes for file data
    {
        printf("Error: The data from coded image is not copied\n");
        return e_failure;
    }

    // Decode file data from LSBs
    if (decode_byte_from_lsb(decInfo->decoded_data.size, decInfo, data) != e_success)
    {
        printf("Error: When the process of byte to lsb is done\n");
        return e_failure;
    }

    // Write decoded data to the secret file
    if (fprintf(decInfo->fptr_secret, "%s", decInfo->decoded_data.secret) < 0) 
    {
        printf("Error: Unable to write the string to file\n");
        return e_failure;
    }

    return e_success;
}
