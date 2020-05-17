**Name**

Memory leak

**Description**

The variable img->px is reallocated (in this case, in the convert_color_palette_to_image() function), and, as per the specification of the library, should be freed in the calling program.
The provided stub for the use of the fuzzer, however, does not free the img->px (nor img) after calling the function and before returning.

**Affected Lines**

In the updated file:

pngparser.c: (425)

**Expected vs Observed**

We expect the stub to correctly free both img->px and px after they have been allocated by load_png.
In practice, however, the pointer is never freed after its allocation, leading to a memory leak.

**Steps to Reproduce**

./fuzzer_load_png ../reports/00/leak-2d5ff885f157e7321b0f50c06272f3da682963af

**Proof of concept**

leak-2d5ff885f157e7321b0f50c06272f3da682963af

**Suggested Fix Description**

In order to fix the bug, it's enough to free the img->px and img pointers (in this order) after the load_png function returns correctly (as only if it does they have been allocated). 
