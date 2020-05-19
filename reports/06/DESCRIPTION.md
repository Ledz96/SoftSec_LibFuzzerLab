**Name**

fclose on null pointer

**Description**

The function load_png tries to open a file with the function fopen: if the action is successful, the program functions normally, while if it is not, it jumps to an error.
The error section, however, starts by closing the file using fclose(), without checking whether or not it was correctly opened first. 
Since the FILE* variable has NULL value in case the file is not opened correctly, null value is passed to the fclose: according to the function's documentation, this leads to undefined behavior, and often causes segmentation faults.

**Affected Lines**

On the fixed file:
pngparser.c: 747-749

**Expected vs Observed**

We expect the program to correctly deal with errors: in case a file could not be open, the program should just ignore it; in case it was, it should close it before freeing other variables to deal with the error. 
In practice, the program always attempts to call 'fclose()' on the file pointer, even when it has NULL value.

**Steps to Reproduce**

./fuzzer_load_png_name -jobs=2 -runs=32 -workers=2 ../seeds

**Suggested Fix Description**

In order to fix the bug, it's enough to put the fclose(file) function call inside an if condition, that checks whether the pointer is not null before proceding.
