/*
Name : H VARUN
Date : 12/11/24
Description : LSB Image Steganography */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "encode.h"
#include "types.h"
#include "decode.h"

int main(int argc, char *argv[])
{
    // Check if enough command-line arguments are provided
    if (argc < 3) 
    {
        printf("\033[0;31mINFO: Please pass valid arguments.\n");
        usleep(500000);
        printf("INFO: Encoding minimun 4 arguments.\n");
        usleep(500000);
        printf("Usage:-./a.out -e source_image_file secret_data_file [Destination_image_file]\n");
        usleep(500000);
        printf("INFO: Decoding Minimum 3 arguments.\n");
        usleep(500000);
        printf("Usage:-./a.out -d encoded_image [output_file_name]\033[0m\n");
        return 1; // Exit with an error code
    }

    // Determine operation type (encoding or decoding)
    OperationType op = check_operation_type(argv[1]);
    
    // Check if operation is encoding
    if (op == e_encode)
    {
        printf("\033[0;36mEncoding process started\033[0m\n");
        sleep(1);
        EncodeInfo encInfo;

        // Read and validate command-line arguments for encoding
        Status st = read_and_validate_encode_args(argv, &encInfo);
        if (st == e_failure)
        {
            printf("Error: Invalid command line arguments. Please try again.\n");
            return 1; // Exit with an error code
        }

        // Perform the encoding process
        st = do_encoding(&encInfo);
        if (st == e_failure)
        {
            printf("Error: Encoding failed. Please check the input files and try again.\n");
            return 1; // Exit with an error code
        }

        printf("\033[0;32m--------------------------------\033[0m\n");
        printf("\033[0;32mEncoding completed successfully.\033[0m\n");
        printf("\033[0;32m--------------------------------\033[0m\n");
    }
    // Check if operation is decoding
    else if (op == e_decode)
    {
        printf("\033[0;36mDecoding process started\033[0m\n");
        sleep(1);
        DecodeInfo decInfo;

        // Read and validate command-line arguments for decoding
        Status st = read_and_validate_encode_args_d(argv, &decInfo);
        if (st == e_failure)
        {
            printf("Error: Invalid command line arguments. Please try again.\n");
            return 1; // Exit with an error code
        }

        // Perform the decoding process
        st = do_decoding(&decInfo);
        if (st == e_failure)
        {
            printf("Error: Decoding failed. Please check the input files and try again.\n");
            return 1; // Exit with an error code
        }

        printf("\033[0;32m--------------------------------\033[0m\n");
        printf("\033[0;32mDecoding completed successfully.\033[0m\n");
        printf("\033[0;32m--------------------------------\033[0m\n");
    }
    // Unsupported operation type
    else
    {
        printf("Error: Unsupported operation. Use -e for encoding or -d for decoding.\n");
        return 1; // Exit with an error code
    }

    return 0; // Success
}

// Determine operation type based on command-line argument
OperationType check_operation_type(char *argv)
{
    if(strcmp(argv, "-e") == e_success) // Check if operation is encoding
        return e_encode;
    else if (strcmp(argv, "-d") == e_success) // Check if operation is decoding
        return e_decode;
    else
        return e_unsupported; // Unsupported operation
}
