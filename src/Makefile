n-puzzle: Node.o List.o MakeDescendants.o main.o
	gcc -o n-puzzle main.o Node.o List.o MakeDescendants.o -Wall

main.o: main.cpp
	g++ -c main.cpp -Wall

NPuzzle.o: NPuzzle.cpp
	   g++ -c NPuzzle.cpp -Wall

MakeDescendants.o: MakeDescendants.c Node.c List.c
	gcc -c MakeDescendants.c -Wall

List.o: List.c Node.c
	gcc -c List.c -Wall

Node.o: Node.c
	gcc -c Node.c -Wall

clean:
	rm -f *~ *.o
