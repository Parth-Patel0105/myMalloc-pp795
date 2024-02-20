Michael McMahon mam1198
Parth Patel pp795

Run instructions:

To run memgrind.c:
make memgrind
./memgrind

To run testcode.c:
make testcode
./testcode

Running testcode executes the tests outlined below:

Correctness test plan:

Test 1:
Requirement tested: malloc() only reserves unallocated memory 
Allocates the entire memory and then attempts to call malloc with a pointer again.
Expected result: NULL is assigned to the pointer:
Not enough space, NULL pointer returned.
(nil)

Test 2:
Requirement tested: malloc() correctly allocates space when there is enough.
Allocates an int pointer and assigns the value 5 to the allocated object and then prints the dereferenced pointer.
Expected result: prints 5:
5

Test 3:
Reuirement tested: free() deallocates memory
Allocates the entire array with a pointer d and then attempts to allocate more space, failing like in Test 2. Then frees the pointer d and attempts to allocate space again with a new pointer and writes a value to the object.
Expected result: The space isn't able to be allocated at first, but then it is after d is freed:
Not enough space, NULL pointer returned.
3.300000

Test 4:
Requirement tested: malloc() and free() arrange so that adjacent free blocks are coalesced.
Allocates 7 pointers l, m, n, o, p, q, r and s each of size 576 such that the entire 4096 byte array is filled (as the headers of each allocated chunk are 8 bytes each). Then frees pointers m and o and attempts to allocate 1744 bytes of space, which should fail. It then frees the pointer n, which pointed to the chunk in between m and o. myfree is expected to coalesce all three of the now adjacent free chunks into one. When malloc is called for 1744 bytes again, it should now have enough space and succeed. It will assign the integer 777 to the space allocated and print the dereferenced pointer.
Expected output: Error message "not enough space, NULL pointer returned" followed by 777:
Not enough space, NULL pointer returned.
777

Test 5: 
Requirement tested: free() cannot be called with an address not obtained from malloc().
Creates a local variable and calls free on it.
Expected result: An error is printed explaining that free() cannot be called with an address not obtained from malloc():
Error in testcode.c on line 105: Called free() with an address not obtained from malloc().

Test 6:
Requirement tested: free() cannot be called with an address not at the start of a chunk.
Allocates a pointer p1 with malloc and then calls free on an address in memory not allocated with malloc by performing pointer arithmetic on p1.
Expected result: An error is printed explaining that free() cannot be called with an address not at the start of a chunk:
Error in testcode.c on line 110: Called free() with an address not at the start of a chunk.

Test 7:
Requirement tested: free() cannot be called a second time on the same pointer.
Allocates a pointer p2, creates a pointer q2 of the same address, calls free on p2 and then on q2.
Expected result: An error is printed explaining that free() cannot be called a second time on the same pointer:
Error in testcode.c on line 118: Called free() a second time on the same pointer.

mymalloc() and myfree() design notes:

The headers at the beginning of each chunk are 8 bytes each. An int is written to the first 4 bytes to represent whether the chunk is allocated or not, 1 representing allocated and 0 representing unallocated. An int is written to the second 4 bytes which represents the size in bytes of the chunk's payload. This value is also used to traverse the memory.

When a chunk is allocated, if there is at least 8 bytes of space between it and the next chunk another chunk is created and it is set as unallocated. This means that we allow for chunks with payloads of size zero to be created. We allow this because memory cannot be allocated in a space of only 8 bytes, as the header size is 8 bytes.

We use a helper function called checkFree when freeing a pointer to ensure that it points to the payload of an object allocated by mymalloc(). We do this by using pointer arithmetic with the size values in the headers of each chunk in the memory and comparing those addresses to the one passed into myfree(). We also use checkFree to identify the three errors associated with myfree() by checking the allocated status of chunks and checking if the address passed into myfree() is in the memory array. In the case of any of the three errors an identifying integer is returned which myfree() uses to print the error message.

memgrind.c: assesses a custom memory allocator by running varied tests, including simple byte allocations and complex patterns, to simulate real usage.

Test Descriptions:

  Test 1: This test measures the allocator's performance by repeatedly allocating and then immediately freeing a single byte, putting a 
  spotlight on the overhead and efficiency of the allocator's basic operations.

  Test 2: It assesses the allocator's ability to handle multiple small allocations by allocating 120 1-byte objects, storing them in an 
  array, and then collectively freeing them, testing the allocator's batch processing capabilities.

  Test 3: This test introduces randomness by alternating between allocating a 1-byte chunk and freeing a previously allocated chunk, 
  simulating a more unpredictable and dynamic memory usage pattern to evaluate the allocator's robustness and adaptability.

  StressTest 1: Designed to push the allocator to its limits, this test performs rapid, alternating allocations and deallocations of a 
  single byte, testing the allocator's endurance and response to high-frequency memory operation requests.

  StressTest 2: It challenges the allocator with allocations of random sizes between 1 and 64 bytes to test its efficiency and strategy in 
  handling memory fragmentation and varied allocation sizes, providing insights into the allocator's performance under complex scenarios.

These tests are designed to cover a broad spectrum of common and edge-case scenarios to ensure robustness and efficiency in memory allocation and deallocation.
