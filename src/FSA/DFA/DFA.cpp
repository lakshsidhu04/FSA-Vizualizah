#include "DFA.h"
#include <fstream>

DFA::DFA(int stateCount, int startState, std::unordered_set<int> acceptStates) 
    : startState(startState), acceptStates(acceptStates) {
    for (int i = 0; i < stateCount; i++) {
        states.insert(i);
    }
}

void DFA::addTransition(int initialState, char symbol, int finalState) {
    if (states.find(initialState) == states.end() || states.find(finalState) == states.end()) {
        throw std::invalid_argument("Invalid state in transition");
    }
    
    alphabet.insert(symbol);
    
    transitionTable[initialState][symbol] = finalState;
}

void DFA::exportToDot(const std::string &filename)
{
    std::ofstream file(filename);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file for writing");
    }
    
    file << "digraph DFA {\n  rankdir=LR;\n  node [shape=circle];\n";
    
    
    for (int state : states)
    {
        if(acceptStates.find(state) != acceptStates.end())
        {
            file << "  " << state << " [shape=doublecircle];" << std::endl;
        }
        else
        {
            file << "  " << state << ";" << std::endl;
        }
    }
    
    file << "  init [shape=point];" << std::endl;
    file << "  init -> " << startState << ";" << std::endl;
    
    for (const auto &[start, edges] : transitionTable)
    {
        for (const auto &[symbol, end] : edges)
        {
            file << "  " << start << " -> " << end << " [label=\"" << symbol << "\"];\n";
        }
    }
    
    file << "}\n";
    
    if (!file)
    {
        throw std::runtime_error("Error writing DOT file");
    }
}

void DFA::instanceDFA(int currentState, int highlightedEdgeStart, int highlightedEdgeEnd, const std::string &fileName)
{
    std::ofstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file for writing");
    }
    
    file << "digraph DFA {" << std::endl;
    file << " rankdir=LR;" << std::endl;
    file << " node [shape=circle];" << std::endl;
    file << " size=\"8,5\";" << std::endl;  
    file << " overlap=false;" << std::endl; 
    file << " splines=true;" << std::endl;
    
    for (int s : states)
    {
        if (s == currentState)
        {
            // accept state is double circle
            if(acceptStates.find(s) != acceptStates.end())
            {
                file << " " << s << " [shape=doublecircle, style=filled, fillcolor=green];" << std::endl;
            }
            else
            {
                file << " " << s << " [style=filled, fillcolor=blue, fontcolor=white];" << std::endl;
            }
        }
        else if (acceptStates.find(s) != acceptStates.end())
        {
            file << " " << s << " [shape=doublecircle];" << std::endl;
        }
        else
        {
            file << " " << s << ";" << std::endl;
        }
    }
    
    file << " init [shape=point];" << std::endl;
    file << " init -> " << startState << ";" << std::endl;
    
    for (const auto &[start, edges] : transitionTable)
    {
        for (const auto &[symbol, end] : edges)
        {
            if (start == highlightedEdgeStart && end == highlightedEdgeEnd)
            {
                file << " " << start << " -> " << end << " [label=\"" << symbol << "\", color=red, penwidth=2.0];\n";
            }
            else
            {
                file << " " << start << " -> " << end << " [label=\"" << symbol << "\"];\n";
            }
        }
    }

    file << "}\n";
    file.close();
}

void DFA::createGIF(const std::string &input)
{
    int currentState = startState;
    
    instanceDFA(currentState, -1, -1, "DOTFiles/instance_0.dot");

    int count = 1;
    for (char symbol : input)
    {
        if (transitionTable[currentState].find(symbol) == transitionTable[currentState].end())
        {
            std::cout << "No transition for symbol '" << symbol << "' from state " << currentState << std::endl;
            return;
        }

        int nextState = transitionTable[currentState][symbol];
        
        instanceDFA(nextState, currentState, nextState, "DOTFiles/instance_" + std::to_string(count++) + ".dot");
        
        currentState = nextState;
    }

    
    instanceDFA(currentState, -1, -1, "DOTFiles/instance_" + std::to_string(count) + ".dot");
}