#include <stdio.h>
#include "decode.h"
#include "types.h"
#include <string.h>
#include "common.h"

Status openfiles(DecodeInfo *decinfo)
{
    decinfo->fptr_encoded_image = fopen(decinfo->encoded_image_fname,"r");

    if(decinfo -> fptr_encoded_image == NULL)
    {
        perror("fopen ");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decinfo-> encoded_image_fname);

    	return e_failure;
    }

    decinfo->fptr_output = fopen(decinfo->output_fname, "w");
    // Do Error handling
    if(decinfo ->fptr_output == NULL)
    {
    	perror("fopen ");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", decinfo->output_fname);

    	return e_failure;
    }

    return e_success;
}

Status read_and_validate_decode_args(char *argv[], DecodeInfo *decinfo)
{
    if(strcmp(strstr(argv[2], "."), ".bmp") == 0)
    {
        decinfo -> encoded_image_fname = argv[2];
    }
    else
    {
        return e_failure;
    }

    if(argv[3] != NULL)
    {
        if(strcmp(strstr(argv[3], ".") , ".txt") == 0)
        {
            decinfo->output_fname = argv[3];
        }
        else
        {
            return e_failure;
        }
    }
    else
    {
        decinfo -> output_fname = "output.txt";
    }
    return e_success;
}

Status decode_magic_string(char *data, DecodeInfo *decinfo)
{
    fseek(decinfo -> fptr_encoded_image, 54, SEEK_SET);
    char password[strlen(data) + 1];

    decode_image_to_data(strlen(data), decinfo -> fptr_encoded_image, password);

    if(strcmp(password, data) == 0)
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
    
}

Status decode_image_to_data(int size, FILE *fptr_encoded_image, char *decoded_data)
{
    char str[8];
    
    for( int i = 0; i < size; i++)
    {
        fread(str, sizeof(char), 8, fptr_encoded_image);
        decoded_data[i] = decode_lsb_to_byte(str);
    }
    decoded_data[size] = '\0';
    return e_success;
}

char decode_lsb_to_byte(char *str)
{
    char decoded_byte = 0x00;

    for(int i = 0; i <= 7; i++)
    {
        decoded_byte = decoded_byte | (str[i] & 0x01) << (7-i);
    }
    return decoded_byte;
    
}

Status decode_secret_file_extension_size(int *size, FILE *fptr_encoded_image)
{
    char arr[32];
    fread(arr, 1, 32, fptr_encoded_image);
    *size = decode_size_to_lsb(arr);
    return e_success;
}

uint decode_size_to_lsb(char *arr)
{
    int decoded_byte = 0;

    for(int i = 0; i <= 31; i++)
    {
        decoded_byte = decoded_byte | (arr[i] & 0x01) << (31-i);
    }
    return decoded_byte;
}

Status decode_secret_file_extension(char *secret_file_extension, int size, FILE *fptr_encoded_image)
{
    decode_image_to_data(size, fptr_encoded_image, secret_file_extension);
   
}

Status decode_secret_file_size(int *size, FILE *fptr_encoded_image)
{
    char arr[32];
    fread(arr, 1, 32, fptr_encoded_image);
    *size = decode_size_to_lsb(arr);
    return e_success;   
}

Status decode_secret_file(char *secret_file_data, int size, FILE *fptr_encoded_image)
{
    decode_image_to_data(size, fptr_encoded_image, secret_file_data);
    return e_success;
}

Status do_decoding(DecodeInfo *decinfo)
{
    if(openfiles(decinfo) == e_success)
    {
        printf("Success : Opened files function\n");

        if(decode_magic_string(MAGIC_STRING, decinfo) == e_success)
        {
            printf("Success : Decoded magic string\n");

            if(decode_secret_file_extension_size(&decinfo -> size_extension_file, decinfo -> fptr_encoded_image) == e_success)
            {
                printf("Success : Decoded extension file size\n");

                if(decode_secret_file_extension(decinfo -> secret_file_extension, decinfo -> size_extension_file, decinfo -> fptr_encoded_image) == e_success)
                {
                    printf("Success : Decoded secret file extension\n");

                    if(decode_secret_file_size(&decinfo -> size_secret_file, decinfo -> fptr_encoded_image) == e_success)
                    {
                        printf("Success : Decoded secret file size\n");

                        char secret_file_data[decinfo -> size_secret_file];
                        if(decode_secret_file(secret_file_data, decinfo -> size_secret_file, decinfo -> fptr_encoded_image) == e_success)
                        {
                            printf("Success : decoded secret file data\n");
                            fwrite(secret_file_data, 1, decinfo -> size_secret_file, decinfo -> fptr_output);
                            return e_success;
                        }
                        else
                        {
                            printf("Failure : Decoding secret file data\n");
                            return 1;
                        }
                    }
                    else
                    {
                        printf("Failure : Decoding secret file size\n");
                        return 1;
                    }
                }
                else
                {
                    printf("Failure : decoding secret file extension\n");
                    return 1;
                }
            }
            else
            {
                printf("Failure : Decoding extension file size\n");
                return 1;
            }
        }
        else
        {
            printf("Failure : Decoding magic string\n");
            return 1;
        }
    }
    else
    {
        printf("Failure : Opening files function\n");
        return 1;
    }
}