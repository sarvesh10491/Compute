main: main.o ring_buffer_lib.o b_tree_lib.o
	gcc -o main main.o ring_buffer_lib.o b_tree_lib.o

main.o: main.c
	gcc -c main.c

ring_buffer_lib.o: ring_buffer_lib.c
	gcc -c ring_buffer_lib.c
	
b_tree_lib.o: b_tree_lib.c
	gcc -c b_tree_lib.c
	
clean:
	rm -f main *.o