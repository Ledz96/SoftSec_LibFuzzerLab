#include "pngparser.h"
#include <stdio.h>
#include <unistd.h>
#include <string.h>

// LibFuzzer stub
//
int LLVMFuzzerTestOneInput(const uint8_t *Data, size_t Size) {
  struct image *test_img;
  char* filename = malloc((Size+1) * sizeof(char));
  int i;

  for (i = 0; i < Size; i++) {
      filename[i] = Data[i];
  }
  filename[i] = '\0';
  
  if (load_png("../seeds/rgba.png", &test_img)) {
    return 1;
  }

  store_png(filename, test_img, NULL, 0);

  free(test_img->px);
  free(test_img);
  free(filename);

  // Always return 0
  return 0;
}
 
