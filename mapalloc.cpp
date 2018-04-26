// mapalloc.cpp
// Corey S. Gray
// 25 April 2018
// Source for Assignment 4 - Exercise A: Simple Memory Manager
// See http://man7.org/linux/man-pages/man2/mmap.2.html for details on mmap and munmap

#include <sys/mman.h>
#include <unordered_map>

#include "mapalloc.h"

std::unordered_map<void*, size_t> allocations;

// mapAlloc
// Takes a size_t indicating the number of bytes to be allocated.
// Returns a pointer to the allocated block or nullptr if unsuccessful.
void* mapAlloc(size_t length) {
	void* address = mmap(
		nullptr,                    // addr: Kernel chooses the address at which to create the mapping
		length,                     // length: The length of the mapping
		PROT_READ | PROT_WRITE,     // prot: Grant read and write access
		MAP_SHARED | MAP_ANONYMOUS, // flags: Updates are visible to other processes and initialize its contents to zero
		-1,                         // fd: File descriptor, which is not used with MAP_ANONYMOUS
		0                           // offset: Starting point. Should be 0 with MAP_ANONYMOUS.
		);

	if (address == MAP_FAILED)
		return nullptr;
	
	allocations[address]=length;
	return address;
}

// mapFree
// Takes a pointer to a block previous allocated with mapAlloc.
// Deallocates the given block and returns nothing.
void mapFree(void * address) {
	size_t length = allocations[address];
	munmap(address, length);
	allocations.erase(address);
}