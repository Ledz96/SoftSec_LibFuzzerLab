#include "pngparser.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define IMG_SIZE 1024

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < IMG_SIZE) {
      return 0;
  }
  struct image *test_img = malloc(sizeof(struct image));
  char filename[16];

  int pixel_number = IMG_SIZE/sizeof(struct pixel);

  test_img->size_x = sqrt(pixel_number);
  test_img->size_y = sqrt(pixel_number);
  test_img->px = malloc(test_img->size_x * test_img->size_y * sizeof(struct pixel));
  if (test_img->px == NULL) {
      printf("Error in allocating the image");
      return 1;
  }
  memcpy(test_img->px, Data, IMG_SIZE);

  sprintf(filename, "%d", getpid());
  strcat(filename, ".png");

  store_png(filename, test_img, NULL, 0);

  free(test_img->px);
  free(test_img);

  // Always return 0
  return 0;
}