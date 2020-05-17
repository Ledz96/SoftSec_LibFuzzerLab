#include "pngparser.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
#define IMG_SIZE 256
#define PALETTE_SIZE 16

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  if (Size < ((IMG_SIZE + PALETTE_SIZE) * sizeof(struct pixel))) {
      return 0;
  }
  struct image *test_img = malloc(sizeof(struct image));
  char filename[16];

  test_img->size_x = sqrt(IMG_SIZE);
  test_img->size_y = sqrt(IMG_SIZE);
  test_img->px = malloc(test_img->size_x * test_img->size_y * sizeof(struct pixel));
  if (test_img->px == NULL) {
      printf("Error in allocating the image");
      return 1;
  }
  struct pixel* palette = malloc(PALETTE_SIZE*sizeof(struct pixel));
  memcpy(test_img->px, Data, IMG_SIZE * sizeof(struct pixel));
  memcpy(palette, Data+(IMG_SIZE * sizeof(struct pixel)), PALETTE_SIZE * sizeof(struct pixel));

  sprintf(filename, "%d", getpid());
  strcat(filename, ".png");

  store_png(filename, test_img, palette, PALETTE_SIZE);

  free(test_img->px);
  free(test_img);
  free(palette);

  // Always return 0
  return 0;
}