#include <stdio.h>
#include "encode.h"
#include "types.h"
#include <string.h>
#include "common.h"

/* Function Definitions */

/* Get image size
 * Input: Image file ptr
 * Output: width * height * bytes per pixel (3 in our case)
 * Description: In BMP Image, width is stored in offset 18,
 * and height after that. size is 4 bytes
 */
uint get_image_size_for_bmp(FILE *fptr_image)
{
    uint width, height;
    // Seek to 18th byte
    fseek(fptr_image, 18, SEEK_SET);

    // Read the width (an int)
    fread(&width, sizeof(int), 1, fptr_image);
    printf("width   = %u\n", width);

    // Read the height (an int)
    fread(&height, sizeof(int), 1, fptr_image);
    printf("height  = %u\n", height);

    // Return image capacity
    return width * height * 3;
}

/* 
 * Get File pointers for i/p and o/p files
 * Inputs: Src Image file, Secret file and
 * Stego Image file
 * Output: FILE pointer for above files
 * Return Value: e_success or e_failure, on file errors
 */
Status open_files(EncodeInfo *encInfo)
{
    // Src Image file
    encInfo->fptr_src_image = fopen(encInfo->src_image_fname, "r");
    // Do Error handling
    if (encInfo->fptr_src_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->src_image_fname);

    	return e_failure;
    }

    // Secret file
    encInfo->fptr_secret = fopen(encInfo->secret_fname, "r");
    // Do Error handling
    if (encInfo->fptr_secret == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->secret_fname);

    	return e_failure;
    }

    // Stego Image file
    encInfo->fptr_stego_image = fopen(encInfo->stego_image_fname, "w");
    // Do Error handling
    if (encInfo->fptr_stego_image == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", encInfo->stego_image_fname);

    	return e_failure;
    }

    // No failure return e_success
    return e_success;
}

Status read_and_validate_encode_args(char *argv[], EncodeInfo *encinfo)
{
    if(strcmp(strstr(argv[2], "."), ".bmp") == 0)
    {
        encinfo-> src_image_fname = argv[2];
    }
    else
    {
        return e_failure;
       
    }

    if(strcmp(strstr(argv[3], "."), ".txt") == 0)
    {
        encinfo-> secret_fname = argv[3];
    }
    else
    {
        return e_failure;
       
    }

    if(argv[4] != NULL)
    {
        if(strcmp(strstr(argv[4], "."), ".bmp") == 0)
        {
            encinfo->stego_image_fname = argv[4];
        }
        else
        {
            return e_failure;
        }
    }
    else
    {
        encinfo -> stego_image_fname = "stego.bmp";
    }
    return e_success;
}

uint get_file_size(FILE *fptr)
{
    fseek(fptr, 0, SEEK_SET);
    fseek(fptr, 0, SEEK_END);
    return ftell(fptr);
}

Status check_capacity(EncodeInfo *encinfo)
{
    encinfo -> image_capacity = get_image_size_for_bmp(encinfo -> fptr_src_image);
    encinfo -> size_secret_file = get_file_size(encinfo -> fptr_secret);
    fseek(encinfo -> fptr_secret, 0, SEEK_SET);
    if(encinfo -> image_capacity >= (54+ 16 +32 +32 +32 + (8 * encinfo -> size_secret_file)))
    {
        return e_success;
    }
    else
    {
        return e_failure;
    }
}

Status copy_bmp_header(FILE *fptr_src_image, FILE *fptr_dest_image)
{
    char str[54];
    fseek(fptr_src_image, 0 , SEEK_SET );
    fread(str, sizeof(char), 54, fptr_src_image);
    fwrite(str, sizeof(char), 54, fptr_dest_image);
    return e_success;
}

Status encode_magic_string(const char *magic_string, EncodeInfo *encinfo)
{
    encode_data_to_image(magic_string, strlen(magic_string), encinfo -> fptr_src_image, encinfo -> fptr_stego_image);
    return e_success;
}

Status encode_data_to_image(const char *data, int size, FILE *fptr_src_image, FILE * fptr_dest_image)
{
    char str[8];
    for( int i = 0; i < size; i++) // 2 times fetch 8 bytes of the data form the src_image.bmp
    {
        fread(str, sizeof(char), 8, fptr_src_image);
        encode_byte_to_lsb(data[i], str);
        fwrite(str, sizeof(char), 8, fptr_dest_image);
    }
    return e_success;
}

Status encode_byte_to_lsb(char data, char *image_buffer)
{
    unsigned char mask = 1 << 7;

    for( int i = 0; i <= 7; i++)
    {
        image_buffer[i] = (image_buffer[i] & 0XFE) | ((data & mask) >> 7 - i);
        mask = mask >> 1;
    }
}

Status encode_secret_file_extn_size(int size, FILE *fptr_src_image, FILE * fptr_dest_image)
{
    char arr[32];
    fread(arr, 1, 32, fptr_src_image); //  reads 32 individual 1-byte blocks. , check line 201.
    encode_size_to_lsb(size, arr);
    fwrite(arr, 1, 32, fptr_dest_image);
    return e_success;
}

Status encode_size_to_lsb(int data, char *image_buffer) // here we encode the size/length of secret file extenstion that is .txt (size = 4) so  these 4 byte encode into the stego.bmp.
{                                                       // and this logic also encode size of secret file logic is smae -> foe example 128 is size -> now 128 is an int , for int required 32 byte data foe encode.  same logic
    uint mask = 1 << 31;

    for( int i = 0; i <= 31; i++)
    {
        image_buffer[i] = (image_buffer[i] & 0XFE) | ((data & mask) >> 31 - i);
        mask = mask >> 1;
    }
}

Status encode_secret_file_extn(const char *file_extn , EncodeInfo *encinfo) // here encode .txt extenstion
{
    encode_data_to_image(file_extn, strlen(file_extn), encinfo -> fptr_src_image, encinfo -> fptr_stego_image);
   
}

Status encode_secret_file_size(long file_size, EncodeInfo *encinfo)
{
    char arr[32];
    fread(arr, 32, 1, encinfo -> fptr_src_image);  // reads 1 block of 32 byte
    encode_size_to_lsb(file_size, arr);
    fwrite(arr, 32, 1, encinfo -> fptr_stego_image);
    return e_success;
}

Status encode_secret_file_data(EncodeInfo *encinfo)
{
    char ch;
    for(int i = 0; i < encinfo -> size_secret_file; i++)
    {
        fread(encinfo -> image_data, 8 , 1, encinfo -> fptr_src_image);
        fread(&ch, 1, 1, encinfo -> fptr_secret);
        encode_byte_to_lsb(ch, encinfo -> image_data);
        fwrite(encinfo -> image_data, 8, 1, encinfo -> fptr_stego_image);
    }
    return e_success;
}

Status copy_remaining_img_data(FILE *fptr_src_image, FILE *fptr_stego_image)
{
    char ch;
    while(fread(&ch, 1, 1, fptr_src_image) > 0)
    {
        fwrite(&ch, 1, 1, fptr_stego_image);
    }
    return e_success;
}

Status do_encoding(EncodeInfo *encinfo)
{
    if(open_files(encinfo) == e_success)
    {
        printf("Success : Opened files function\n");

        if (check_capacity(encinfo) == e_success)
        {
            printf("Success : Check Capacity\n");

            if(copy_bmp_header(encinfo -> fptr_src_image, encinfo -> fptr_stego_image) == e_success)
            {
                printf("Success : Copied .bmp header\n");

                if(encode_magic_string(MAGIC_STRING, encinfo) == e_success)
                {
                    printf("Success : Encoded magic string\n");
                    
                    strcpy(encinfo -> extn_secret_file , (strstr(encinfo -> secret_fname, ".")));
                    if(encode_secret_file_extn_size(strlen(encinfo -> extn_secret_file), encinfo -> fptr_src_image, encinfo -> fptr_stego_image) == e_success)
                    {
                        printf("Success : Encoded secret file size extension\n");

                        if(encode_secret_file_extn(encinfo -> extn_secret_file, encinfo) == e_success)
                        {
                            printf("Success : Encoded secret file extension\n");

                            if(encode_secret_file_size(encinfo -> size_secret_file, encinfo) == e_success)
                            {
                                printf("Success : Encoded secret file size\n");

                                if(encode_secret_file_data(encinfo) == e_success)
                                {
                                    printf("Success : Encoding secret file data\n");

                                    if(copy_remaining_img_data(encinfo -> fptr_src_image, encinfo -> fptr_stego_image) == e_success)
                                    {
                                        printf("Success : copied remaining data\n");
                                        return e_success;
                                    }

                                    else
                                    {
                                        printf("Failure : copying remaining data\n");
                                        return 1;
                                    }
                                }

                                else
                                {
                                    printf("Failure : Encoding secret file data\n");
                                    return 1;
                                }
                            }

                            else
                            {
                                printf("Failure : Encoding secret file size\n");
                                return 1;
                            }
                        }

                        else
                        {
                            printf("Failure : Encoding secret file extension\n");  
                            return 1;  
                        }
                    }

                    else
                    {
                        printf("Failure : Encoding secret file size extension\n");
                        return 1;    
                    }
                }
                else
                {
                    printf("Failure : Encoding magic string\n");
                    return 1;
                }
            }
            else
            {
                printf("Failure : Copying .bmp header\n");
                return 1;
            }

        }
        else
        {
            printf("Failure : Check Capacity\n");
            return 1;
        }
    }
    else
    {
        printf("Failure : Open files function\n");
        return 1;
    }
}

