#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "types.h"
#include "decode.h"


int main(int argc, char **argv)
{
    if(check_operation_type(argv) == e_encode)
    {
        printf("\n## Started Encoding ##\n\n*******************************************************************\n");
        EncodeInfo encinfo;

        if(read_and_validate_encode_args(argv, &encinfo) == e_success)
        {
            printf("Success : Read and validate function\n");

            if(do_encoding(&encinfo) == 0)
            {
                printf("\n*******************************************************************\n## Encoding finished Successfully ## \n\n");
            }
            else
            {
                printf("Encoding Failed\n\n");
            }
        }
        else
        {
            printf("Failure : Read and validate function\n");
            printf("Encoding Failed\n\n");
            return 1;
        }
    }
    else if(check_operation_type(argv) == e_decode)
    {
        printf("\n## Started Decoding ##\n\n*******************************************************************\n");
        DecodeInfo decinfo;

        if(read_and_validate_decode_args(argv, &decinfo) == e_success)
        {
            printf("Success : Read and validate function\n");

            if(do_decoding(&decinfo) == 0)
            {
                printf("\n*******************************************************************\n## Decoding finished Successfully## \n\n");
            }
            else
            {
                printf("Decoding Failed\n\n");
            }   
        }

        else
        {
            printf("Failure : Read and validate function\n");
            printf("Decoding Failed\n\n");
            return 1;
        }
    }
    else
    {
        printf("*******************************************************************\n");
        printf("\t\t  Invalid operation\n");
        printf("*******************************************************************\n");
        printf("\t\t  Use below comments\n");
        printf("*******************************************************************\n");
        printf("For Encoding : ./a.out -e beautiful.bmp secret.txt stego.bmp\n");
        printf("For Decoding : ./a.out -d stego.bmp output.txt\n");
        printf("*******************************************************************\n");
    }

    return 0;
}

OperationType check_operation_type(char **argv)
{
    if(strcmp(argv[1], "-e") == 0 )
    {
        return e_encode;
    }
    else if(strcmp(argv[1], "-d") == 0 )
    {
        return e_decode;
    }
    else if(argv[1] == NULL)
    {
        return e_unsupported;
    }
    else
    {
        return e_unsupported;
    }
}
