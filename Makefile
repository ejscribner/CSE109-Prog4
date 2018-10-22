prog4: Allocation.o Allocator.o prog4.o
	gcc -g -Wall -Werror -o prog4 Allocation.o Allocator.o prog4.o

Allocation.o: Allocation.c
	gcc -g -Wall -Werror -c Allocation.c

Allocator.o: Allocator.c
	gcc -g -Wall -Werror -c Allocator.c

clean:
	rm *.o prog4