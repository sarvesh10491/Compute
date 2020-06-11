double_linked_list_app: double_linked_list_lib.o main.c
	gcc -Wall -Wextra double_linked_list_lib.o main.c -o double_linked_list_app

llist.o: double_linked_list_lib.h double_linked_list_lib.c
	gcc -Wall -Wextra -fPIC double_linked_list_lib.h -c double_linked_list_lib.c

clean:
	rm -rf *.o *.gch double_linked_list_app