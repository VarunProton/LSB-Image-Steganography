#include<stdio.h>
#ifndef ENCODE_H
#define ENCODE_H
#include <unistd.h>
#include "types.h" // Contains user-defined types

/* Constants for buffer sizes */
#define MAX_SECRET_BUF_SIZE 1
#define MAX_IMAGE_BUF_SIZE (MAX_SECRET_BUF_SIZE * 8)
#define MAX_FILE_SUFFIX 4
#define MAX_HEADER 54

/* Structure to store information required for encoding a secret file into a source image */
typedef struct _EncodeInfo 
{
    /* Source Image Info */
    char *src_image_fname;      // Source file name (e.g., beautful.bmp)
    FILE *fptr_src_image;       // File pointer for the source image
    uint image_remaining_capacity;         // Capacity of the source image
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

} EncodeInfo;

/* Function Prototypes */

/* Check operation type */
OperationType check_operation_type(char *argv);

/* Read and validate encoding arguments from command line */
Status read_and_validate_encode_args(char *argv[], EncodeInfo *encInfo);

/* Perform the encoding process */
Status do_encoding(EncodeInfo *encInfo);

/* Open input and output file pointers */
Status open_files(EncodeInfo *encInfo);

/* Check if the source image has enough capacity for the secret data */
Status check_capacity(EncodeInfo *encInfo);

/* Get the size of the BMP image */
uint get_image_size_for_bmp(FILE *fptr_image);

/* Get the size of the specified file */
long get_file_size(FILE *fptr, EncodeInfo *encInfo);

/* Get the size of the secret file */
long get_file_size_secret(FILE *fptr, EncodeInfo *encInfo);

/* Copy BMP image header from source to destination */
Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image);

/* Store a magic string in the image */
Status encode_magic_string(const char *magic_string, EncodeInfo *encInfo);

/* Get the size of the file extension */
uint get_ext_size(EncodeInfo *encInfo);

/* Encode the size of the secret file extension */
Status encode_secret_file_extn_size(uint size, EncodeInfo *encInfo);

/* Encode the secret file extension into the image */
Status encode_secret_file_extn(const char *file_extn, char size, EncodeInfo *encInfo);

/* Encode the size of the secret file into the image */
Status encode_secret_file_size(uint file_size, EncodeInfo *encInfo);

/* Encode the secret file data into the image */
Status encode_secret_file_data(EncodeInfo *encInfo);

/* Encode a single byte into the LSB of the image data */
Status encode_byte_to_lsb(char data, char *image_buffer);
 
/* Copy remaining image bytes from source to stego image after encoding */
Status copy_remaining_img_data(uint size, FILE *fptr_src, FILE *fptr_dest);

/* Encode an integer byte into the LSB of the image data */
Status encode_byte_to_lsb_int(uint data, char *image_buffer);

#endif // ENCODE_H