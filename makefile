all: exec
exec: main.o src/FSA/DFA/DFA.o src/FSA/NFA/NFA.o
	g++ main.o src/FSA/DFA/DFA.o src/FSA/NFA/NFA.o -o exec -std=c++11

main.o: main.cpp src/FSA/DFA/DFA.o src/FSA/NFA/NFA.o
	g++ -c main.cpp -o main.o -std=c++11

src/FSA/DFA/DFA.o: src/FSA/DFA/DFA.cpp src/FSA/DFA/DFA.h
	g++ -c src/FSA/DFA/DFA.cpp -o src/FSA/DFA/DFA.o -std=c++11

src/FSA/NFA/NFA.o: src/FSA/NFA/NFA.cpp src/FSA/NFA/NFA.h
	g++ -c src/FSA/NFA/NFA.cpp -o src/FSA/NFA/NFA.o -std=c++11

clean:
	rm -rf *.o exec
	rm -rf src/FSA/DFA/*.o
	rm -rf src/FSA/NFA/*.o