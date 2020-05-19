**Name**

Memory leak

**Description**

For the special chunks plte_chunk and ihdr_chunk, only the chunk itself is freed, while the chunk_data field, even when allocated, is never freed. 
This leads to a memory leak, as the pointers to the special chunks are freed, but some of the inner fields are not.

**Affected Lines**

In the updated file:

pngparser.c: (277)

**Expected vs Observed**

We expect the program to allocate chunk_data and then free it after the parent variable after has been used, causing no memory leaks. 
In practice, however, the inner pointer is never freed after its allocation, leading to a memory leak.

**Steps to Reproduce**

./fuzzer_load_png ../reports/03/leak-2d5ff885f157e7321b0f50c06272f3da682963af

**Proof of concept**

leak-2d5ff885f157e7321b0f50c06272f3da682963af

**Suggested Fix Description**

In order to fix the bug, it is necessary to free ihdr_chunk->chunk_data and plte_chunk->chunk_data, both in the case of error and the one of success.
In particular, it is necessary to add a condition that checks that the variable is not NULL right after it has been checked that the structure itself is not NULL. At this point, if it is not NULL, it is necessary to free it, just like it has been done for the current_chunk->chunk_data variable. 
After this, it is possible to procede and free the chunk itself.
