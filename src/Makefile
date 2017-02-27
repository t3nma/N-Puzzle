N-Puzzle: main.o NPuzzle.o SearchAlgorithm.o Configuration.o Board.o
	g++ -o N-Puzzle main.o NPuzzle.o SearchAlgorithm.o Configuration.o Board.o -Wall

main.o: main.cpp Board.cpp Configuration.cpp SearchAlgorithm.cpp NPuzzle.cpp headers/Board.h headers/Configuration.h headers/SearchAlgorithm.h headers/NPuzzle.h
	g++ -c main.cpp -Wall

NPuzzle.o: NPuzzle.cpp Board.cpp Configuration.cpp SearchAlgorithm.cpp headers/Board.h headers/Configuration.h headers/SearchAlgorithm.h
	g++ -c NPuzzle.cpp -Wall

SearchAlgorithm.o: SearchAlgorithm.cpp Configuration.cpp headers/PQComparator.h
	g++ -c SearchAlgorithm.cpp -Wall

Configuration.o: Configuration.cpp Board.cpp headers/Configuration.h headers/Board.h
	g++ -c Configuration.cpp -Wall

Board.o: Board.cpp headers/Board.h
	g++ -c Board.cpp -Wall

clean:
	rm -f N-Puzzle *~ *.o *\#
