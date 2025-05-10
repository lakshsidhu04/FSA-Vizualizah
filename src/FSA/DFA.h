#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class DFA{
    private:
        // 5-tuple representation of DFA
        std::unordered_set<int> states; 
        std::unordered_set<char> alphabet;
        std::unordered_map<int, std::unordered_map<char, int>> transitionTable; 
        int startState; 
        std::unordered_set<int> acceptStates; 
    
    public:
        DFA(int stateCount,int startState, std::unordered_set<int> acceptStates);
        void addTransition(int initialState, char symbol, int finalState);
        void exportToDot(const std::string& fileName); 
        void instanceDFA(int state,int start,int end, const std::string& fileName);
        void createGIF(const std::string& input);
};