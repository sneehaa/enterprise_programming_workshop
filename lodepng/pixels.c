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
    for (int i = 0; i < 10; i++) {
        int idx = i * 4;
        printf("Pixel %d -> R:%d G:%d, B:%d A:%d\n",
            i, image[idx], image[idx+1], image[idx+2], image[idx+3]);
    }
    printf("Width: %u, Height: %u\n", width, height);
    lodepng_encode32_file("pixout.png", image, width, height);
    printf("Saved  image as pixout.png\n");
    free(image);
    return 0;
}