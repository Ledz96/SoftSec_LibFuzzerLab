**Name**

Memory leak

**Description**

The variable output_buffer is reallocated in the decompress_png_data() function, and later assigned to *decompressed data (decompressed_data is a pointer to pointer passed to the function as a parameter). Because of this, the responsibility of freeing the pointer is passed to the calling function.
The calling function (store_png()) does not, however, free the pointer, causing a memory leak. 

**Affected Lines**

In the updated file:

pngparser.c: (388)

**Expected vs Observed**

We expect the program to allocate and then free the variable after it has been used, causing no memory leaks. 
In practice, however, the pointer is never freed after its allocation, leading to a memory leak.

**Steps to Reproduce**

./fuzzer_load_png leak-2d5ff885f157e7321b0f50c06272f3da682963af

**Proof of concept**

leak-2d5ff885f157e7321b0f50c06272f3da682963af

**Suggested Fix Description**

In order to fix the bug, it's enough to free the inflated_buff before the function store_png() returns. 
