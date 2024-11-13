#include <stdio.h>
#ifndef DECODE_H
#define DECODE_H
#include <unistd.h>
#include "types.h" // Contains user-defined types

/* Constants for buffer sizes */
#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4
#define MAX_HEADER 54

/* Structure to store information required for decoding a secret file from a source image */
typedef struct _DecodeInfo 
{
    /* Source Image Info */
    char *src_image_fname;      // Source file name (e.g., beautful.bmp)
    FILE *fptr_src_image;       // File pointer for the source image
    uint image_capacity;         // Capacity of the source image
    uint bits_per_pixel;         // Bits per pixel (usually 24 for BMP)
    char image_data[MAX_IMAGE_BUF_SIZE]; // Buffer to store image data

    /* Secret File Info */
    char *secret_fname;         // Secret file name (e.g., secret.txt)
    FILE *fptr_secret;          // File pointer for the secret file
    char extn_secret_file[MAX_FILE_SUFFIX]; // Extension of the secret file
    char secret_data[MAX_SECRET_BUF_SIZE]; // Buffer to store secret data
    long size_secret_file;      // Size of the secret file

    /* Stego Image Info */
    char *stego_image_fname;    // Output image file name
    FILE *fptr_stego_image;     // File pointer for the output image
    union data
    {
        char secret[50];
        int size;
    }decoded_data;

} DecodeInfo;

/* Function Prototypes */

/* Read and validate decoding arguments from command line */
Status read_and_validate_encode_args_d(char *argv[], DecodeInfo *decInfo);

/* Perform the decoding process */
Status do_decoding(DecodeInfo *decInfo);

/* Open input and output file pointers */
Status open_files_d(DecodeInfo *decInfo);

/* Store a magic string in the image */
Status decode_magic_string(DecodeInfo *decInfo);

/* Decode the size of the secret file extension */
Status decode_secret_file_extn_size(DecodeInfo *decInfo);

/* Decode the secret file extension from the image */
Status decode_secret_file_extn(DecodeInfo *decInfo);

/* Decode the size of the secret file from the image */
Status decode_secret_file_size(DecodeInfo *decInfo);

/* Decode the secret file data from the image */
Status decode_secret_file_data(DecodeInfo *decInfo);

/* Decode a single byte from the LSB of the image data */
Status decode_byte_from_lsb(char size, DecodeInfo *decInfo, char *image_buffer);

/* Decode an integer byte from the LSB of the image data */
Status decode_byte_from_lsb_int(DecodeInfo *decInfo, char *image_buffer);

#endif // DECODE_H