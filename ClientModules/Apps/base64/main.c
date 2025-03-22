
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "base64.h"

int main()
{
    system("clear");

    ///////encode
    const unsigned char *input = ".jpg";

    printf("Oi: %s\n", input);

    unsigned char *base64encode_out = encode_message((unsigned char *)input);
    if (base64encode_out == NULL)
    {
        fprintf(stderr, "Encode fail\n");
        return 1;
    }

    printf("Oi: %s\n", base64encode_out);

    //////////decode
    unsigned char *base64decode_out = decode_message((const unsigned char *)base64encode_out);
    if (base64decode_out == NULL)
    {
        fprintf(stderr, "Decode fail\n");
        return 1;
    }

    printf("Oi: %s\n", base64decode_out);

    /////////encode images


    // THESE STUFF WILL BE TAKEN FROM THE CLIENT SERVER
    const char *filename_tobecoded = "eunjung.jpg";   // path to the image file to be encoded
    const char *filename_tobedecoded = "eunjung.txt"; // path to the text file to be decoded
    const char *fileext_tobedecoded = "ext.txt"; // path to the text file to be decoded

    // Read the image file into a byte array
    encode_media(filename_tobecoded);

    decode_media(filename_tobedecoded,fileext_tobedecoded);

    free(base64decode_out);

    free(base64encode_out);

    clear_decoding_table();


    return 0;
}