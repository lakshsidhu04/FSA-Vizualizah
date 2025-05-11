#include <iostream>
#include "./src/FSA/DFA/DFA.h"
#include "./src/FSA/NFA/NFA.h"

using namespace std;

int main(){
    NFA nfa(5, 0, {1, 2});
    nfa.addTransition(0, 'a', 1);
    nfa.addTransition(0, 'a', 2);
    nfa.addTransition(1, 'b', 3);
    nfa.addTransition(2, 'b', 4);

    nfa.addTransition(3, 'c', 1);
    nfa.addTransition(4, 'c', 2);

    nfa.createGIF("abc");


}