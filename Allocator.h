/*
CSE 109: Fall 2018
Elliot Scribner
ejs320
This program is a non-optimzed memory allocator to fulfil memory requests made by users
Program #4
*/

#ifndef ALLOCATOR_H
#define ALLOCATOR_H

#include <stdlib.h>
#include <stdio.h>

struct Allocator_t
{
	size_t listCapacity;
	void *memory;
	size_t capacity;
	size_t memoryUsed; // total bytes used
	struct Allocation_t **list; //??? could also be a double ptr
	size_t listSize;
};

void makeAllocator(struct Allocator_t *this, size_t capacity);

void freeAllocator(struct Allocator_t *this);

void *allocate(struct Allocator_t *this, size_t amt);

void deallocate(struct Allocator_t *this, void *ptr);

void *getBase(struct Allocator_t *this);

size_t getUsed(struct Allocator_t *this);

size_t getCapacity(struct Allocator_t *this);

struct Allocation_t *getAllocation(struct Allocator_t *this, size_t index);

size_t numAllocations(struct Allocator_t *this);

void *riskyAlloc(struct Allocator_t *this, size_t size);

size_t align(size_t input, size_t alignment);

#endif