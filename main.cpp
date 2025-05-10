#include <iostream>
#include "./src/FSA/DFA.h"

using namespace std;

int main(){
    DFA dfa(3, 0, {1});
    dfa.addTransition(0, 'a', 1);
    dfa.addTransition(0, 'b', 2);
    dfa.addTransition(1, 'a', 0);
    dfa.addTransition(1, 'b', 2);
    dfa.addTransition(2, 'a', 1);
    dfa.addTransition(2, 'b', 2);
    dfa.createGIF("aab");
    return 0;
}