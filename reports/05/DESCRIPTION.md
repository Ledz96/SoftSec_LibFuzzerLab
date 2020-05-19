**Name**

Memory Leak

**Description**

In the function load_png, a for loop allocates new chunks, that are then identified and treated based on their type. In the previous bugfix, we made sure that all kinds of recognized chunks were correctly freed.
In case the chunk does not fit any of the known types, however, it is just ignored and overwritten with another allocation, causing a memory leak.

**Affected Lines**

In the updated file:

pngparser.c: 592 (allocation), 682 (lack of action). 

**Expected vs Observed**

We expect the program to consider the situation where the chunk does not fit any of the known types, either by aborting or freeing it, before skipping to the next one.
The program, however, just ignores the possibility, leading to memory leaks (and a corrupted stored image) in case this happens.

**Steps to Reproduce**

./fuzzer_load_png ../reports/05/leak-489e797dcd765cf4d701db08c3e8cf7b9496c561.png

**Proof of concept**

leak-489e797dcd765cf4d701db08c3e8cf7b9496c561.png

**Suggested Fix Description**

Two different approaches may be taken in order to fix the bug: in case the analysed chunk does not correspond to any of the predetermined ones, it is possible to, either:
1) Free the chunk before proceding with the next iteration of the loop, being consistent with the current strategy of ignoring it (but without causing any memory leak) 
2) Jump to the error section, as the image is corrupted. This solution was deemed cleaner, and therefore adopted in fixing the problem. The chunk will then still be asigned to the current_chunk variable, and therefore freed in the error section.
