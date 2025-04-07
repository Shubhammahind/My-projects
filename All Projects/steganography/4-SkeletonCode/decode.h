#ifndef DECODE_H
#define DECODE_H

#include "types.h"

typedef struct _DecodeInfo
{
    /* Source Image info */
    char *encoded_image_fname;
    FILE *fptr_encoded_image;

    /* Secret File Info */
    char *output_fname;
    FILE *fptr_output;
    char secret_file_extension[10];
    uint size_secret_file;
    uint size_extension_file;

} DecodeInfo;

/* Decoding Function Prototype*/

/* Read and validate Decode args from argv */
Status read_and_validate_decode_args(char *argv[], DecodeInfo *decInfo);

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

/*Open files function*/
Status openfiles(DecodeInfo *decinfo);

/*Decoding magic string*/
Status decode_magic_string(char *data, DecodeInfo *decinfo);

/*Decoding image to data*/
Status decode_image_to_data(int size, FILE *fptr_encoded_image, char *decoded_data);

/*Decoding lsb to data*/
char decode_lsb_to_byte(char *str);

/*Decoding Secret File extension size*/
Status decode_secret_file_extension_size(int *size_extension_file, FILE *fptr_encoded_image);

/*Decoding lsb to size*/
uint decode_size_to_lsb(char *arr);

/*Decoding secret file extension*/
Status decode_secret_file_extension(char *secret_file_extension, int size, FILE *fptr_encoded_image);

#endif