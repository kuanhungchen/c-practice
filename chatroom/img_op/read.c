#include <stdint.h>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

int main() {
    int width, height, depth;

    uint8_t* rgb_image = stbi_load("image.png", &width, &height, &depth, 3);
    //printf("width: %i\nheight: %i\nbpp: %i", width, height, bpp);
    
    printf("%i\n", rgb_image[10]);
    stbi_image_free(rgb_image);

    return 0;
}
