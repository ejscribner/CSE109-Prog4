/*
CSE 109: Fall 2018
Elliot Scribner
ejs320
This program is a non-optimzed memory allocator to fulfil memory requests made by users
Program #4
*/

#ifndef ALLOCATION_H
#define ALLOCATION_H
#include <stdlib.h>

struct Allocation_t {
	size_t start;
	size_t size;
};

void makeAllocation(struct Allocation_t* this, size_t start, size_t size);

void freeAllocation(struct Allocation_t* this);

size_t getStart(struct Allocation_t* this);  //Check if this vs it matters

size_t getEnd(struct Allocation_t* this);

size_t getSize(struct Allocation_t* this);

int doesOverlap(struct Allocation_t* this);

#endif
