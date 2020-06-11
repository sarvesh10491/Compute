ring_buffer_app: ring_buffer_lib.o main.c
	gcc -Wall -Wextra ring_buffer_lib.o main.c -o ring_buffer_app

llist.o: ring_buffer_lib.h ring_buffer_lib.c
	gcc -Wall -Wextra -fPIC ring_buffer_lib.h -c ring_buffer_lib.c

clean:
	rm -rf *.o *.gch ring_buffer_app