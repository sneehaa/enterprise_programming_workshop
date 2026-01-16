#include <stdio.h>
#include <stdlib.h>
#include "lodepng.h"

int main(){
    printf("Program started\n");
    unsigned char* image = NULL;
    unsigned width, height;
    unsigned error = lodepng_decode32_file(&image, &width, &height, "input.png");

    if(error) {
        printf("Error %u: %s\n", error, lodepng_error_text(error));
        return 1;
    }
    printf("Image loaded: %u x %u\n", width, height);

    for(unsigned y = 0; y < height; y++){
        for(unsigned x = 0; x < width; x++) {
            unsigned idx = 4 * (y * width + x);

            for (int c = 0; c < 3; c++){
                int value = image[idx + c] + 40;
                image[idx + c] = (value > 255) ? 255 : value;
            }

        }
    }

    error = lodepng_encode32_file("bright.png", image, width, height);
    if (error) {
        printf("Encoding error %u: %s\n", error, lodepng_error_text(error));
   } else {
    printf("Brightness-adjusted image saved as bright.png\n");
   }

    free(image);
    return 0;
}
