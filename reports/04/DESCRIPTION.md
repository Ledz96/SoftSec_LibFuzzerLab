**Name**

Double free

**Description**

In the function read_png_chunk, new chunk_data are allocated. At the beginning of the function, chunk->chunk_data is correctly initialized to NULL before the allocation. 
In case chunk_data is successfully allocated, however, it is still possible that it is freed in the same function, in case it is not valid: in this case, the variable will not be assigned to NULL.
Subsequently, a second attempt to free the variable will be made, causing a crash.

**Affected Lines**

In the updated file:

pngparser.c: (710, as well as other instances of free(chunk->chunk_data) for different types of chunks). 
Missing assignation at line 302

**Expected vs Observed**

We expect the program to free the value only once, and avoid possible attempts to double frees by assigning the variable to NULL and checking before freeing.
While the checks are actually performed, however, the assignment to NULL is not, leading to possible attempts to double free and, subsequently, undefiend behavior.

**Steps to Reproduce**

./fuzzer_load_png ../reports/04/crash-afe6aec768c605a27e2d9e03e924f8925f4c14aa

**Proof of concept**

crash-afe6aec768c605a27e2d9e03e924f8925f4c14aa

**Suggested Fix Description**

In order to fix the bug, it is enough to assign the chunk->chunk_data pointer to NULL after it has been freed in the read_png_chunk function. Following this, the subsequent free will not happen, as the program already checks that the value is not NULL before freeing.
