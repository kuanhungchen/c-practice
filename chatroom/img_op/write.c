#include <stdint.h>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#define CHANNEL_NUM 3

int main() {
    int width = 10; 
    int height = 10;

    uint8_t* rgb_image;
    rgb_image = malloc(width * height * CHANNEL_NUM * sizeof(int));
    memset(rgb_image, 255, width * height * CHANNEL_NUM * sizeof(int));
    /*
     * rbg_image.shape = width * height * 3;
     * [px1_r, px1_g, px1_b, px2_r, px2_g, ...]
     *
     *
     *
     *
     *
     *
     */

    int i, j;
    for (i=0; i<width; i++) {
        for (j=0; j<height; j++) {
            int idx = 3 * (i * height + j) + 2;
            printf("Index: %i\n", idx);
            rgb_image[idx] = 0;
        }
    }

    stbi_write_png("image.png", width, height, CHANNEL_NUM, rgb_image, width*CHANNEL_NUM);

    return 0;
}
