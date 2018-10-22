#include "Allocator.h"
#include "printAllocations.h"

int main(int argc, char **argv)
{
	struct Allocator_t *myAllocator = (struct Allocator_t *) malloc(sizeof(struct Allocator_t));
	makeAllocator(myAllocator, 256);
	allocate(myAllocator, 16);
	allocate(myAllocator, 16);
	allocate(myAllocator, 16);
	printAllocations(myAllocator, stdout);
	deallocate(myAllocator, myAllocator->memory);
	printAllocations(myAllocator, stdout);
	deallocate(myAllocator, myAllocator->memory);
	deallocate(myAllocator, myAllocator->memory);
	free(myAllocator);
	myAllocator = NULL;
	return 0;
}