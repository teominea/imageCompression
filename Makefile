build:
	gcc -o quadtree structs.h main.c functii.c
run:
	./quadtree
clean:
	rm quadtree
valgrind:
	valgrind --leak-check=yes --track-origins=yes ./quadtree