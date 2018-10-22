/*
CSE 109: Fall 2018
Elliot Scribner
ejs320
This program is a non-optimzed memory allocator to fulfil memory requests made by users
Program #4
*/

#include "Allocator.h"
#include "Allocation.h"

void makeAllocator(struct Allocator_t *this, size_t capacity)
{
	capacity = align(capacity, 16);
	this->memory = malloc(capacity);
	this->capacity = capacity;
	this->list = NULL;
	this->memoryUsed = 0;
	this->listSize = 0;
	this->listCapacity = 0;
}

void freeAllocator(struct Allocator_t *this)
{
	free(this->memory);
	this->memory = NULL;
	for (int i = 0; i < this->listSize; i++)
	{
		free(this->list[i]);
		this->list[i] = NULL;
	}
	this->listCapacity = 0;
	free(this->list);
	this->list = NULL;
	this->memoryUsed = 0;
	this->listSize = 0;
}

void *allocate(struct Allocator_t *this, size_t amt)
{
	amt = align(amt, 16);
	for (size_t i = 0; i < this->capacity; i += 16)
	{
		if (i + amt > this->capacity)
		{
			break;
		}
		int overlaps = 0;
		for (size_t j = 0; j < this->listSize; j++)
		{
			if (doesOverlap(this->list[j], i, amt))
			{
				overlaps = 1;
				break;
			}
		}

		if (overlaps)
		{
			continue;
		}

		if (this->listCapacity == this->listSize)
		{
			this->listCapacity = (this->listCapacity * 2) + 1;
			struct Allocation_t **temp = (struct Allocation_t **) malloc(
					this->listCapacity * sizeof(struct Allocation_t *));
			for (int k = 0; k < this->listSize; k++)
			{
				temp[k] = this->list[k];
			}
			free(this->list);
			this->list = temp;
		}
		this->list[this->listSize] = (struct Allocation_t *) malloc(sizeof(struct Allocation_t));
		makeAllocation(this->list[this->listSize], i, amt);
		this->memoryUsed += amt;
		this->listSize++;
		return this->memory + i;
	}
	return NULL;
}

void deallocate(struct Allocator_t *this, void *ptr)
{
	if (ptr == NULL)
	{
		return;
	}
	for (int i = 0; i < this->listSize; i++)
	{
		if ((this->memory + getStart(this->list[i])) == ptr)
		{
			this->memoryUsed = this->memoryUsed - getSize(this->list[i]); //err
			free(this->list[i]);
			this->listSize--;
			this->list[i] = NULL;
			this->list[i] = this->list[this->listSize];
			this->list[this->listSize] = NULL;
			return;
		}
	}
	fprintf(stderr, "Corruption in free \n");
	exit(1);
}

void *getBase(struct Allocator_t *this)
{
	return this->memory;
}

size_t getUsed(struct Allocator_t *this)
{
	return this->memoryUsed;
}

size_t getCapacity(struct Allocator_t *this)
{
	return this->capacity;
}

struct Allocation_t *getAllocation(struct Allocator_t *this, size_t index)
{
	if (index < 0 || index >= this->listSize)
	{
		return NULL;
	}
	return this->list[index];
}

size_t numAllocations(struct Allocator_t *this)
{
	return this->listSize;
}

void *riskyAlloc(struct Allocator_t *this, size_t size)
{
	void *retVal = allocate(this, size);
	if (retVal != NULL)
	{
		return retVal;
	}
	else
	{
		void *oldMemory = this->memory;
		this->memory = realloc(this->memory, this->capacity + size);
		if (oldMemory != this->memory)
		{
			fprintf(stderr, "Bad realloc \n");
			return NULL;
		}
	}
	return allocate(this, size);
}

size_t align(size_t input, size_t alignment)
{
	if (input % alignment != 0)
	{
		input = input + (16 - (input % alignment));
	}
	return input;
}