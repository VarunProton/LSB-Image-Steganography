#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

/* Function Definitions */

uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Move file pointer to 18th byte position where width is stored
    fseek(fptr_image, 18, SEEK_SET);
    // Read width and height of the BMP image
    fread(&width, sizeof(int), 1, fptr_image);
    fread(&height, sizeof(int), 1, fptr_image);

    // Return the capacity in terms of bytes (width * height * 3)
    return width * height * 3;
}

long get_file_size(FILE *fptr, EncodeInfo *encInfo)
{
    if (fptr == NULL) 
    {
        printf("File pointer is NULL!\n");
        return 0;
    }
    // Move pointer to the end of the file to get its size
    fseek(fptr, 0, SEEK_END);
    uint size = ftell(fptr); // Get file size in bytes
    // Reset file pointer to the beginning of the file
    fseek(fptr, 0, SEEK_SET);
    
    // Calculate total encoding size requirements
    return (size * 8) + (2 * sizeof(int) + 54 + 1 + (strlen(MAGIC_STRING)) * 8 + get_ext_size(encInfo) * 8);
}

long get_file_size_secret(FILE *fptr, EncodeInfo *encInfo)
{
    if (fptr == NULL) 
    {
        printf("File pointer is NULL!\n");
        return 0;
    }
    // Move pointer to the end to get file size
    fseek(fptr, 0, SEEK_END);
    uint size = ftell(fptr); // Get file size in bytes
    // Reset pointer to beginning
    fseek(fptr, 0, SEEK_SET);
    return size;
} 

uint get_ext_size(EncodeInfo *encInfo)
{
    char *ptr = strrchr(encInfo->src_image_fname, '.'); // Find last occurrence of '.'
    return strlen(ptr); // Return length of extension
}

Status open_files(EncodeInfo *encInfo)
{
    // Open source image file in read mode
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);
    	return e_failure;
    }

    // Open secret file in read mode
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);
    	return e_failure;
    }

    // Open stego image file in write mode
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);
    	return e_failure;
    }

    // Return success if all files were opened successfully
    return e_success;
}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo)
{
    const char *valid_extensions[] = {".bmp", ".txt", ".bmp"};
    
    // Validate extensions for input files
    for (int i = 0; i < 2; i++) 
    {
        if (strstr(argv[i + 2], valid_extensions[i]) == NULL)
        {
            printf("Error: command line argument %d is Invalid\n", i + 2);
            return e_failure;
        }
    }
    // Check for output file argument, set default if absent
    if (argv[4] == NULL)
    {
        printf("\033[0;33mINFO:  \033[0;34mArgument of output file not passed, setting default file name.\033[0m\n");
        sleep(1);
        encInfo->stego_image_fname = "output.bmp";
    }
    // Validate output file extension
    else if (strstr(argv[4], valid_extensions[2]) == NULL)
    {
        printf("Error: command line argument is Invalid\n");
        return e_failure;
    }
    else
        encInfo->stego_image_fname = argv[4];

    encInfo->src_image_fname = argv[2]; // Set source image filename
    encInfo->secret_fname = argv[3]; // Set secret file filename
    return e_success;
}

Status check_capacity(EncodeInfo *encInfo)
{
    uint image_capacity = get_image_size_for_bmp(encInfo->fptr_src_image);
    long size_secret_file = get_file_size(encInfo->fptr_secret, encInfo);

    if (image_capacity >= size_secret_file)
    {
        printf("\033[0;33mINFO:\033[0m \033[0;34m Image capacity: %u bytes\033[0m\n", image_capacity);
        printf("\033[0;33mINFO:\033[0m \033[0;34m Secret file size: %ld bytes\033[0m\n", size_secret_file);
        sleep(1);
        encInfo->image_remaining_capacity = (image_capacity - size_secret_file); // Calculate remaining capacity
        return e_success;
    }

    printf("Error: Image capacity is insufficient\n");
    return e_failure;  
}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
    for (int i = 7; i >= 0; i--)
    {
        // Set LSB of each buffer byte with bits from the data byte
        image_buffer[7 - i] = (image_buffer[7 - i] & (~1)) | ((data >> i) & 1);
    }
    return e_success;
}

Status encode_byte_to_lsb_int(uint data, char *image_buffer)
{
    for (int i = 31; i >= 0; i--)
    {
        // Set LSB of each buffer byte with bits from the integer data
        image_buffer[31 - i] = (image_buffer[31 - i] & (~1)) | ((data >> i) & 1);
    }
    return e_success;
}

Status copy_remaining_img_data(uint size, FILE *fptr_src, FILE *fptr_dest)
{
    char header[size];
    
    // Read and copy header data from source to destination
    fread(header, size, 1, fptr_src);
    fwrite(header, size, 1, fptr_dest);
    return e_success;
}
