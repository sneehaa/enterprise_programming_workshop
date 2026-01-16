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

    for(unsigned y = 0; y < height; y++){
        for(unsigned x = 0; x < width; x++) {
            unsigned idx = 4 * (y * width + x);
           
            image[idx] = 255 - image[idx];
            image[idx+1] = 255 - image[idx+1];
            image[idx+2] = 255 - image[idx+2];

        }
    }

    lodepng_encode32_file("invert.png", image, width, height);
    printf("Saved grayscale image as invert.png\n");

    free(image);
    return 0;
}
