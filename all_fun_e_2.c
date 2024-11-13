#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    char header[54];
    fseek(fptr_src_image, 0, SEEK_SET);  // Go to the start of the source image
    if (fread(header, 54, 1, fptr_src_image) != 1)  // Read the BMP header (54 bytes)
    {
        printf("Error: The data from source image is not copied\n");
        return e_failure;
    }
    if (fwrite(header, 54, 1, fptr_dest_image) != 1)  // Write the BMP header to destination
    {
        printf("Error: The data from source image is not pasted\n");
        return e_failure;
    }
    return e_success;
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo)
{
    char n = strlen(MAGIC_STRING);  // Get the length of the magic string
    char data[8];
    for (char i = 0; i < n; i++)  // Loop over each character in the magic string
    {
        if (fread(data, 8, 1, encInfo->fptr_src_image) != 1)  // Read 8 bytes from the source image
        {
            printf("Error: The data from source image is not copied\n");
            return e_failure;
        }
        if (encode_byte_to_lsb(magic_string[i], data) == e_failure)  // Encode character into LSBs
        {
            printf("Error: When the process of byte to lsb is done\n");
            return e_failure;
        }

        if (fwrite(data, 8, 1, encInfo->fptr_stego_image) != 1)  // Write encoded data to stego image
        {
            printf("Error: The data from source image is not pasted\n");
            return e_failure;
        }
    }
    return e_success;
}

Status encode_secret_file_extn_size(uint size, EncodeInfo *encInfo)
{
    char data[32];
    if (fread(data, 32, 1, encInfo->fptr_src_image) != 1)  // Read 32 bytes from source image
    {
        printf("Error: The data from source image is not copied\n");
        return e_failure;
    }

    // Encode the file extension size in LSBs
    if (encode_byte_to_lsb_int(size, data) == e_failure)
    {
        printf("Error: When the process of byte to lsb is done\n");
        return e_failure;
    }
    if (fwrite(data, 32, 1, encInfo->fptr_stego_image) != 1)  // Write encoded data to stego image
    {
        printf("Error: The data from source image is not pasted\n");
        return e_failure;
    }
    return e_success;
}

Status encode_secret_file_extn(const char *file_extn, char size, EncodeInfo *encInfo)
{
    char data[8];
    while (*file_extn != '\0')  // Loop over each character in the file extension
    {
        if (fread(data, 8, 1, encInfo->fptr_src_image) != 1)  // Read 8 bytes from source image
        {
            printf("Error: The data from source image is not copied\n");
            return e_failure;
        }

        if (encode_byte_to_lsb(*file_extn, data) == e_failure)  // Encode character into LSBs
        {
            printf("Error: When the process of byte to lsb is done\n");
            return e_failure;
        }

        if (fwrite(data, 8, 1, encInfo->fptr_stego_image) != 1)  // Write encoded data to stego image
        {
            printf("Error: The data from source image is not pasted\n");
            return e_failure;
        }
        file_extn++;  // Move to the next character in the file extension
    }
    return e_success;
}

Status encode_secret_file_size(uint file_size, EncodeInfo *encInfo)
{
    char data[32];
    if (fread(data, 32, 1, encInfo->fptr_src_image) != 1)  // Read 32 bytes from source image
    {
        printf("Error: The data from source image is not copied\n");
        return e_failure;
    }

    // Encode file size into LSBs of data
    if (encode_byte_to_lsb_int((int)file_size, data) == e_failure)
    {
        printf("Error: When the process of byte to lsb is done\n");
        return e_failure;
    }

    if (fwrite(data, 32, 1, encInfo->fptr_stego_image) != 1)  // Write encoded data to stego image
    {
        printf("Error: The data from source image is not pasted\n");
        return e_failure;
    }
    return e_success;
}

Status encode_secret_file_data(EncodeInfo *encInfo)
{
    char file_size = get_file_size_secret(encInfo->fptr_secret, encInfo);  // Get the size of secret file
    char data[8];
    char secret_d;
    fseek(encInfo->fptr_secret, 0, SEEK_SET);  // Reset secret file pointer to beginning
    for (int i = 0; i < file_size; i++)  // Loop through each byte of secret file
    {
        if (fread(data, 8, 1, encInfo->fptr_src_image) != 1)  // Read 8 bytes from source image
        {
            printf("Error: The data from source image is not copied\n");
            return e_failure;
        }

        if (fread(&secret_d, 1, 1, encInfo->fptr_secret) != 1)  // Read 1 byte of secret data
        {
            printf("Error: The data from source image is not copied\n");
            return e_failure;
        }

        // Encode the secret data byte into LSBs of data
        if (encode_byte_to_lsb(secret_d, data) == e_failure)
        {
            printf("Error: When the process of byte to lsb is done\n");
            return e_failure;
        }

        if (fwrite(data, 8, 1, encInfo->fptr_stego_image) != 1)  // Write encoded data to stego image
        {
            printf("Error: The data from source image is not pasted\n");
            return e_failure;
        }
    }
    return e_success;
}
