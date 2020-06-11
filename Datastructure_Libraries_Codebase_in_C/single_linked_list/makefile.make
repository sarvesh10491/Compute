single_linked_list_app: single_linked_list_lib.o main.c
	gcc -Wall -Wextra single_linked_list_lib.o main.c -o single_linked_list_app

llist.o: single_linked_list_lib.h single_linked_list_lib.c
	gcc -Wall -Wextra -fPIC single_linked_list_lib.h -c single_linked_list_lib.c

clean:
	rm -rf *.o *.gch single_linked_list_app