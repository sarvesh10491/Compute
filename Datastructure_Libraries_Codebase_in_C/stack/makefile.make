stack_app: stack_lib.o main.c
	gcc -Wall -Wextra stack_lib.o main.c -o stack_app

llist.o: stack_lib.h stack_lib.c
	gcc -Wall -Wextra -fPIC stack_lib.h -c stack_lib.c

clean:
	rm -rf *.o *.gch stack_app