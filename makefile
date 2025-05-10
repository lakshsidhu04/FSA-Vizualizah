all: exec
exec: main.o src/FSA/DFA.o
	g++ main.o src/FSA/DFA.o -o exec -std=c++11

main.o: main.cpp src/FSA/DFA.o
	g++ -c main.cpp -o main.o -std=c++11

src/FSA/DFA.o: src/FSA/DFA.cpp src/FSA/DFA.h
	g++ -c src/FSA/DFA.cpp -o src/FSA/DFA.o -std=c++11

clean:
	rm -rf *.o exec
	rm -rf src/FSA/*.o