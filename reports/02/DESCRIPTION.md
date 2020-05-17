**Name**

Memory leak

**Description**

The variable iend_chunk is assigned to an allocated chunk in load_png(). 
Contrarily to other kinds of chunks, however, the variable is never freed before the function returns. This causes a memory leak.

**Affected Lines**

In the updated file:

pngparser.c: (650)

**Expected vs Observed**

We expect the program to allocate and then free the variable after it has been used, causing no memory leaks. 
In practice, however, the pointer is never freed after its allocation, leading to a memory leak.

**Steps to Reproduce**

./fuzzer_load_png ../reports/02/leak-2d5ff885f157e7321b0f50c06272f3da682963af

**Proof of concept**

leak-2d5ff885f157e7321b0f50c06272f3da682963af

**Suggested Fix Description**

In order to fix the bug, it is necessary to free the iend_chunk, as well as the chunk_data, in case they have been allocated. This must be done in the end of the function, both in the case of error or success, as in both situations the allocation may happen.
In order to make sure that the values can be freed without any error, it is necessary to add a check on them not being NULL before freeing. 
