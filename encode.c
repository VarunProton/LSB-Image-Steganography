#include <stdio.h>
#include<string.h>
#include "encode.h"
#include "types.h"
#include "common.h"

Status do_encoding(EncodeInfo *encInfo)
{
    // Open files and check for failure
    if (open_files(encInfo) == e_failure)
    {
        return e_failure; // Error already logged in open_files
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Successfully opened all the files\033[0m\n");
    sleep(1);

    // Check capacity for secret file
    if (check_capacity(encInfo) == e_failure)
    {
        printf("Error: The .bmp file doesn't have enough space for the secret code. Use another image.\n");
        return e_failure;
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Enough capacity in the source image. Can proceed with the next step.\033[0m\n");
    sleep(1);

    // Copy BMP header
    if (copy_bmp_header(encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
    {
        return e_failure; // Error already logged in copy_bmp_header
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Header is successfully copied.\033[0m\n");
    sleep(1);

    // Encode the magic string
    if (encode_magic_string(MAGIC_STRING, encInfo) == e_failure)
    {
        return e_failure; // Error already logged in encode_magic_string
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Successfully copied magic string.\033[0m\n");
    sleep(1);

    // Encode secret file extension size
    if (encode_secret_file_extn_size(get_ext_size(encInfo), encInfo) == e_failure)
    {
        return e_failure; // Error already logged in encode_secret_file_extn_size
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Successfully copied extension size.\033[0m\n");
    sleep(1);

    // Encode secret file extension
    if (encode_secret_file_extn(strrchr(encInfo->secret_fname, '.'), get_ext_size(encInfo), encInfo) == e_failure)
    {
        return e_failure; // Error already logged in encode_secret_file_extn
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Successfully copied extension.\033[0m\n");
    sleep(1);

    // Encode secret file size
    if (encode_secret_file_size(get_file_size_secret(encInfo->fptr_secret, encInfo), encInfo) == e_failure)
    {
        return e_failure; // Error already logged in encode_secret_file_size
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Successfully placed the file size.\033[0m\n");
    sleep(1);

    // Encode secret file data
    if (encode_secret_file_data(encInfo) == e_failure)
    {
        return e_failure; // Error already logged in encode_secret_file_data
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Successfully placed secret data.\033[0m\n");
    sleep(1);

    // Copy remaining image data
    if (copy_remaining_img_data(encInfo->image_remaining_capacity, encInfo->fptr_src_image, encInfo->fptr_stego_image) == e_failure)
    {
        return e_failure; // Error already logged in copy_remaining_img_data
    }
    printf("\033[0;33mINFO:\033[0m \033[0;34m Successfully completed copying remaining data.\033[0m\n");
    sleep(1);

    return e_success;
}


