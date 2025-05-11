#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>

class NFA
{
private:
    // 5-tuple representation of NFA
    std::unordered_set<int> states;
    std::unordered_set<char> alphabet;
    std::unordered_map<int, std::unordered_map<char, std::unordered_set<int>>> transitionTable;
    int startState;
    std::unordered_set<int> acceptStates;

public:
    NFA(int stateCount, int startState, std::unordered_set<int> acceptStates);
    void addTransition(int initialState, char symbol, int finalState);
    void exportToDot(const std::string &fileName);
    void instanceNFA(std::unordered_set<int> currStates, std::unordered_set<int> highlightEdgeStart, std::unordered_set<int> highlightEdgeEnd, const std::string &fileName);
    void createGIF(const std::string &input);
};