/*
CSE 109: Fall 2018
Elliot Scribner
ejs320
This program is a non-optimzed memory allocator to fulfil memory requests made by users
Program #4
*/

#include "Allocation.h"
#include <stdio.h>

void makeAllocation(struct Allocation_t *this, size_t start, size_t size)
{
	this->start = start;
	this->size = size;
}

void freeAllocation(struct Allocation_t *this)
{
	this->start = 0;
	this->size = 0;
}

size_t getStart(struct Allocation_t *this)
{
	return this->start;
}

size_t getEnd(struct Allocation_t *this)
{
	size_t end = this->start + this->size;
	return end;
}

size_t getSize(struct Allocation_t *this)
{
	return this->size;
}

int doesOverlap(struct Allocation_t *this, size_t start, size_t size)
{
	int doesOverlap = 0;
	int min = 0;
	int max = 0;
	int thisStart = getStart(this);
	int thisSize = getSize(this);
	int endpt1 = thisStart + thisSize;
	int endpt2 = start + size;

	if (thisStart < start)
	{
		min = thisStart;
	}
	else if (start < thisStart)
	{
		min = start;
	}
	else if (start == thisStart)
	{
		doesOverlap = 1;
		return doesOverlap;
	}

	if (endpt1 < endpt2)
	{
		max = endpt2;
	}
	else if (endpt2 < endpt1)
	{
		max = endpt1;
	}
	else if (endpt1 == endpt2)
	{
		doesOverlap = 1;
		return doesOverlap;
	}

	int fullSize = size + thisSize;
	int range = max - min;
	if (range < fullSize)
	{
		doesOverlap = 1;
		return doesOverlap;
	}

	return doesOverlap;
}
