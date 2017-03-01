N-Puzzle: obj/main.o obj/NPuzzle.o obj/SearchAlgorithm.o obj/Configuration.o obj/Board.o

	g++ -o N-Puzzle obj/main.o obj/NPuzzle.o obj/SearchAlgorithm.o obj/Configuration.o obj/Board.o -Wall

DEBUG: obj/main.o obj/NPuzzle.o obj/SearchAlgorithmDEBUG.o obj/Configuration.o obj/Board.o

	g++ -o N-Puzzle obj/main.o obj/NPuzzle.o obj/SearchAlgorithmDEBUG.o obj/Configuration.o obj/Board.o -Wall -DDEBUG


obj/main.o: src/main.cpp src/Board.cpp src/Configuration.cpp src/SearchAlgorithm.cpp src/NPuzzle.cpp src/headers/Board.h src/headers/Configuration.h src/headers/SearchAlgorithm.h src/headers/NPuzzle.h
	g++ -o obj/main.o -c src/main.cpp -Wall

obj/NPuzzle.o: src/NPuzzle.cpp src/Board.cpp src/Configuration.cpp src/SearchAlgorithm.cpp src/headers/Board.h src/headers/Configuration.h src/headers/SearchAlgorithm.h
	g++ -o obj/NPuzzle.o -c src/NPuzzle.cpp -Wall

obj/SearchAlgorithm.o: src/SearchAlgorithm.cpp src/Configuration.cpp src/headers/HeapComparator.h
	g++ -o obj/SearchAlgorithm.o -c src/SearchAlgorithm.cpp -Wall

obj/SearchAlgorithmDEBUG.o: src/SearchAlgorithm.cpp src/Configuration.cpp src/headers/HeapComparator.h
	g++ -DDEBUG -o obj/SearchAlgorithmDEBUG.o -c src/SearchAlgorithm.cpp -Wall


obj/Configuration.o: src/Configuration.cpp src/Board.cpp src/headers/Configuration.h src/headers/Board.h
	g++ -o obj/Configuration.o -c src/Configuration.cpp -Wall

obj/Board.o: src/Board.cpp src/headers/Board.h

	g++ -o obj/Board.o -c src/Board.cpp -Wall

clean:
	rm -f N-Puzzle src/*~ obj/*.o src/*\#
