#include "pngparser.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct image *test_img;
  char filename[16];

  sprintf(filename, "%d", getpid());
  strcat(filename, ".png");

  FILE *input = fopen(filename,"w");
  fwrite(Data, Size, 1, input);
  fclose(input);
  
  // What would happen if we run multiple fuzzing processes at the same time?
  // Take a look at the name of the file.
  if (!load_png(filename, &test_img)) {
    free(test_img->px);
    free(test_img);
  }

  // Always return 0
  return 0;
}
