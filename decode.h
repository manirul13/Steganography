#ifndef DECODE_H
#define DECODE_H

#include "types.h"  // contains Status, uint, etc.

#define  MAX_DECODE_FILE_SUFFIX 10
#define MAGIC_STRING "#*"

// Structure for decoding info
typedef struct _DecodeInfo
{
    /* member to handle stego.bmp*/
    char *stego_image_fname;
    FILE *fptr_stego_image;

    /* handle the output txt file */
    FILE *fptr_output;
    char *output_file_name;

    /* array to hold extension secret file (.txt) */
    char extn_secret_file[MAX_DECODE_FILE_SUFFIX];
    int size_secret_file_extn;

    /* size of the secret file data */
    uint secret_file_size;

    /* pointer to store the decode secret data (dynamically alllocated)*/
    char *secret_data;

} DecodeInfo;

// Function declarations foe Decoding

/* Check read and validate decode argues from argv */
Status read_and_validate_decode_argues(char *argv[], DecodeInfo *decInfo);

/* Get file pointers for i/p and o/p files */
Status open_decode_files(DecodeInfo *decInfo);

/* Store magic string */
Status decode_magic_string(const char *magic_string, DecodeInfo *decInfo);

/* Get secret file extension size */
Status decode_secret_file_extn_size(DecodeInfo *decInfo, int *size);

/* Get secret file extension */
Status decode_secret_file_extn(char *extn, DecodeInfo *decInfo, int size);

/* Get secret file extension size */
Status decode_secret_file_size(int *size, DecodeInfo *decInfo);

/* Get secret file data */
Status decode_secret_file_data(DecodeInfo *decInfo, int size);

/* Perform the decoding */
Status do_decoding(DecodeInfo *decInfo);

#endif
