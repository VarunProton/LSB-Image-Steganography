#include <stdio.h>
#include <string.h>
#include "decode.h"  // Updated to decode.h
#include "types.h"
#include "common.h"
 
Status do_decoding(DecodeInfo *decInfo)  // Updated function name
{
    // Open files and check for failure
    if (open_files_d(decInfo) == e_failure)
    {
        return e_failure; // Error already logged in open_files
    }
    printf("\033[0;33mINFO:\033[0m \033[0;35m Successfully opened all the files.\033[0m\n");
    sleep(1);

    // Decode the magic string
    if (decode_magic_string(decInfo) == e_failure)  // Updated function name
    {
        printf("Error: Magic string decoding.\n");
        return e_failure; // Error already logged in decode_magic_string
    }
    if(strcmp(decInfo->decoded_data.secret, MAGIC_STRING) != 0)
    {
        printf("ERROR: Magic string not found.\n");
        return e_failure;
    }
    printf("\033[0;33mINFO:\033[0m \033[0;35m Magic string found as \"%s\".\033[0m\n",decInfo->decoded_data.secret);
    sleep(1);

    // Decode secret file extension size
    if (decode_secret_file_extn_size(decInfo) == e_failure)  // Updated function name
    {
        return e_failure; // Error already logged in decode_secret_file_extn_size
    }
    printf("\033[0;33mINFO:\033[0m \033[0;35m Successfully decoded extension size as \"%d\".\033[0m\n", decInfo->decoded_data.size);
    sleep(1);

    // Decode secret file extension
    if (decode_secret_file_extn(decInfo) == e_failure)  // Updated function name
    {
        return e_failure; // Error already logged in decode_secret_file_extn
    }
    printf("\033[0;33mINFO:\033[0m \033[0;35m Successfully decoded extension as \"%s\".\033[0m\n", decInfo->decoded_data.secret);
    sleep(1);

    // Decode secret file size
    if (decode_secret_file_size(decInfo) == e_failure)  // Updated function name
    {
        return e_failure; // Error already logged in decode_secret_file_size
    }
    printf("\033[0;33mINFO:\033[0m \033[0;35m Successfully decoded the file size as \"%d\".\033[0m\n", decInfo->decoded_data.size);
    sleep(1);

    // Decode secret file data
    if (decode_secret_file_data(decInfo) == e_failure)  // Updated function name
    {
        return e_failure; // Error already logged in decode_secret_file_data
    }
    printf("\033[0;33mINFO:\033[0m \033[0;35m Successfully decoded secret data as \"%s\".\033[0m\n", decInfo->decoded_data.secret);
    sleep(1);

    return e_success;
}
