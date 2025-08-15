
#include <stdio.h>
#include <string.h>
#include "encode.h"
#include "decode.h"
#include "types.h"

int main(int argc, char *argv[])
{
    if (check_operation_type(argv) == e_encode)
    {
        EncodeInfo encInfo;
        printf("INFO: Selected Encoding\n");
        printf("Done\n");
        // here continue the encoding
        if (read_and_validate_encode_args(argv, &encInfo) == e_success)
        {
            printf("INFO: Read and validate encode arguments is successful\n");
            printf("Done\n");

            if (do_encoding(&encInfo) == e_success)
            {
                printf("INFO: Encoding is completed\n");
                printf("Done\n");
            }
            else
            {
                printf("Failed to do the encoding\n");
            }
        }
        else
        {
            printf("Failed !!! to read and validate the encode arguments\n");
        }
    }
    else if (check_operation_type(argv) == d_decode)
    {
        DecodeInfo decInfo;
        printf("INFO: Selected Decoding\n");
        printf("Done\n");
        if (read_and_validate_decode_argues(argv, &decInfo) == d_success)
        {
            printf("INFO: Read and validate encode arguments is successful\n");
            printf("Done\n");
            if (do_decoding(&decInfo) == d_success)
            {
                printf("INFO: Decoding is completed\n");
                printf("Done\n");
            }
            else
            {
                printf("Failed to do the decoding\n");
            }
        }
        else
        {
            printf("Failed!! to read and validate the decode arguments\n");
        }
    }
    else
    {
        printf("Invalid Option\n");
        printf("=============================Usage==========================");
        printf("Encoding: ./a.out -e beautiful.bpm secret.txt stego.bmp\n");
        printf("Decoding: ./a.out -d stego.bmp decode.txt\n");
    }

    return 0;
}
OperationType check_operation_type(char *argv[])
{
    //./a.out -e beautiful.bmp secret.txt stego.bmp  /enum
    if (strcmp(argv[1], "-e") == 0)
    {
        return e_encode;
    }
    else if (strcmp(argv[1], "-d") == 0)
    {
        return d_decode;
    }
    else
    {
        return e_unsupported;
    }
}
