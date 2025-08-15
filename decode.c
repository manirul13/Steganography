#include <stdio.h>
#include <string.h>
#include "types.h"
#include "decode.h" 
#include "common.h"

Status read_and_validate_decode_argues(char *argv[], DecodeInfo *decInfo)
{
    // Check if the stego image has a .bmp extension
    if (strstr(argv[2], ".bmp") == NULL)
    {
        printf("ERROR: Unsupported file format. Only .bmp files are allowed.\n");
        return e_failure;
    }
    // store the stego omage file name
    decInfo->stego_image_fname = argv[2];

    // Check if output file name is given
    if (argv[3] != NULL)
    {
        decInfo->output_file_name = argv[3];
    }
    else
    {
        //if given , use dafault file name
        decInfo->output_file_name = "decoded.txt"; // Default output name
    }

    return d_success;
}

Status open_decode_files(DecodeInfo *decInfo)
{
    // Open the stego image file in read mode
    decInfo->fptr_stego_image = fopen(decInfo->stego_image_fname, "r");
    if (decInfo->fptr_stego_image == NULL)
    {
        printf("ERROR: Unable to open stego image file %s\n", decInfo->stego_image_fname);
        return d_failure;
    }

    // Open the output file in write mode
    decInfo->fptr_output = fopen(decInfo->output_file_name, "w");
    if (decInfo->fptr_output == NULL)
    {
        printf("Unable to open output file %s\n", decInfo->output_file_name);
        return d_failure;
    }

    return d_success;
}

Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo)
{
    //Buffer to hold decoded string
    char buffer[strlen(magic_string)];

    // Skip BMP file header (54 bytes)
    fseek(decInfo->fptr_stego_image, 54, SEEK_SET); 

    //Loop through each character of the Magic string
    for (int i = 0; i < strlen(magic_string); i++)
    {
        buffer[i] = 0;

        //Decode each character bit by bit (8 bits)
        for (int j = 0; j < 8; j++)
        {
            char byte;
            fread(&byte, 1, 1, decInfo->fptr_stego_image);  //read a byte
            buffer[i] |= (byte & 1) << (7 - j);             //Extract LSB and Shift
        }
    }

    //Compare decode string with expected magic string
    if (strncmp(buffer, magic_string, strlen(magic_string)) == 0)
    {
        printf("Magic string verified: %s\n", buffer);
        return d_success;
    }
    else
    {
        printf("Magic string mismatch. Expected %s but got %s\n", magic_string, buffer);
        return d_failure;
    }
}

Status decode_secret_file_extn_size(DecodeInfo *decInfo, int *size)
{
    *size = 0;

    //Decode 32 bits to get the extension size
    for (int i = 0; i < 32; i++)
    {
        char byte;
        fread(&byte, 1, 1, decInfo->fptr_stego_image);
        *size |= (byte & 1) << (31 - i);
    }
    return d_success;
}

Status decode_secret_file_extn(char *extn, DecodeInfo *decInfo, int size)
{
    //Loop through each character of the extension
    for (int i = 0; i < size; i++)
    {
        extn[i] = 0;

        //Each character has 8 bits
        for (int j = 0; j < 8; j++)
        {
            char byte;
            fread(&byte, 1, 1, decInfo->fptr_stego_image);
            extn[i] |= (byte & 1) << (7 - j);
        }
    }

    //Null terminate the extension string
    extn[size] = '\0';
    printf("Decoded file extension: %s\n", extn);
    return d_success;
}

Status decode_secret_file_size(int *size, DecodeInfo *decInfo)
{
    *size = 0;
    //rad 32 bits to get file size
    for (int i = 0; i < 32; i++)
    {
        char byte;
        fread(&byte, 1, 1, decInfo->fptr_stego_image);
        *size |= (byte & 1) << (31 - i);
    }
    printf("Decoded secret file size: %d bytes\n", *size);
    return d_success;
}

Status decode_secret_file_data(DecodeInfo *decInfo, int size)
{
    //decode 'size' number of bytes
    for (int i = 0; i < size; i++)
    {
        char ch = 0;

        //Decode 8 bits per character
        for (int j = 0; j < 8; j++)
        {
            char byte;
            fread(&byte, 1, 1, decInfo->fptr_stego_image);
            ch |= (byte & 1) << (7 - j);
        }

        //Write decoded character to output file
        fputc(ch, decInfo->fptr_output);
    }
    return d_success;
}

Status do_decoding(DecodeInfo *decInfo)
{
    if (open_decode_files(decInfo) == d_success)
    {
        printf("INFO: Opened stego and output files successfully.\n");
        printf("Done\n");
        if (decode_magic_string(MAGIC_STRING, decInfo) == d_success)
        {
            printf("INFO: Decode magic string successfully\n");
            printf("Done\n");
            int extn_size;
            if (decode_secret_file_extn_size(decInfo, &extn_size) == d_success)
            {
                printf("INFO: Decode secret file extension size successfully\n");
                printf("Done\n");
                char extn[MAX_DECODE_FILE_SUFFIX];
                if (decode_secret_file_extn(extn, decInfo, extn_size) == d_success)
                {
                    printf("INFO: Decode secret file extension succesfully\n");
                    printf("Done\n");
                    int file_size;
                    if (decode_secret_file_size(&file_size, decInfo) == d_success)
                    {
                        printf("INFO: Decode secret file size successfully\n");
                        printf("Done\n");
                        if (decode_secret_file_data(decInfo, file_size) == d_success)
                        {
                            printf("INFO: Decoded secret file data successfully.\n");
                            printf("Done\n");
                        }
                        else
                        {
                            printf("Failed!! to decode secret file data.\n");
                            return d_failure;
                        }
                    }
                    else
                    {
                        printf("Failed!! to decode secret file size.\n");
                        return d_failure;
                    }
                }
                else
                {
                    printf("Failed!! to decode secret file extension.\n");
                    return d_failure;
                }
            }
            else
            {
                printf("Failed!! to decode file extension size.\n");
                return d_failure;
            }
        }
        else
        {
            printf("Magic string mismatch or not found.\n");
            return d_failure;
        }
    }
    else
    {
        printf("ERROR: Failed to open files.\n");
        return d_failure;
    }

    return d_success;
}
