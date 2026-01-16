#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

int main(){
    unsigned char* image = NULL;
    unsigned width, height;

    if(lodepng_decode32_file(&image, &width, &height, "input.png")) {
        printf("Error decoding image\n");
        return 1;
    }

    printf("Width: %u, Height: %u\n", width, height);
    free(image);
    return 0;
}