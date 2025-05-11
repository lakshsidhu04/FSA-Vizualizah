#include "NFA.h"
#include <unordered_map>
#include <unordered_set>
#include <fstream>

NFA::NFA(int stateCount, int startState, std::unordered_set<int> acceptStates)
    : startState(startState), acceptStates(acceptStates)
{
    for (int i = 0; i < stateCount; ++i) {
        states.insert(i);
    }
}

void NFA::addTransition(int initialState, char symbol, int finalState)
{
    alphabet.insert(symbol);
    transitionTable[initialState][symbol].insert(finalState);
}

void NFA::instanceNFA(std::unordered_set<int> currStates, std::unordered_set<int> highlightEdgeStart, std::unordered_set<int> highlightEdgeEnd, const std::string &fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file for writing");
    }
    
    file << "digraph NFA {" << std::endl;
    file << " rankdir=LR;" << std::endl;
    file << " node [shape=circle];" << std::endl;
    file << " size=\"8,5\";" << std::endl;
    file << " overlap=false;" << std::endl;
    file << " splines=true;" << std::endl;
    
    for(int s:states){
        if(currStates.find(s) != currStates.end()){
            if(acceptStates.find(s) != acceptStates.end()){
                file << " " << s << " [shape=doublecircle, style=filled, fillcolor=green];" << std::endl;
            }else{
                file << " " << s << " [style=filled, fillcolor=blue, fontcolor=white];" << std::endl;
            }
        }else{
            if(acceptStates.find(s) != acceptStates.end()){
                file << " " << s << " [shape=doublecircle];" << std::endl;
            }else{
                file << " " << s << ";" << std::endl;
            }
        }
    }
    
    
    file << "  init [shape=point];" << std::endl;
    file << "  init -> " << startState << ";" << std::endl;
    
    for (const auto &[start, edges] : transitionTable)
    {
        for (const auto &[symbol, end] : edges)
        {
            for (int e : end)
            {
                if (highlightEdgeStart.find(start) != highlightEdgeStart.end() && highlightEdgeEnd.find(e) != highlightEdgeEnd.end())
                {
                    file << "  " << start << " -> " << e << " [label=\"" << symbol << "\", color=red];\n";
                }
                else
                {
                    file << "  " << start << " -> " << e << " [label=\"" << symbol << "\"];\n";
                }
            }
        }
    }
    file << "}" << std::endl;
    file.close();
}

void NFA::createGIF(const std::string &input)
{
    std::unordered_set<int> currStates = {startState};
    
    instanceNFA(currStates, {}, {}, "DOTFiles/instance_0.dot");

    int count = 1;
    for (char symbol : input)
    {
        std::unordered_set<int> nextStates;
        std::unordered_set<int> highlightEdgeStart;
        std::unordered_set<int> highlightEdgeEnd;

        for (int state : currStates)
        {
            if (transitionTable.find(state) != transitionTable.end() && transitionTable[state].find(symbol) != transitionTable[state].end())
            {
                for (int nextState : transitionTable[state][symbol])
                {
                    nextStates.insert(nextState);
                    highlightEdgeStart.insert(state);
                    highlightEdgeEnd.insert(nextState);
                }
            }
        }
        
        instanceNFA(nextStates, highlightEdgeStart, highlightEdgeEnd, "DOTFiles/instance_" + std::to_string(count) + ".dot");
        currStates = nextStates;
        count++;
    }
}