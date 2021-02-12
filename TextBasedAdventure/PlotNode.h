#pragma once
#include <string>
class PlotNode
{
public:
    PlotNode* next_nodes[4]; // possible exits

    PlotNode(PlotNode* exit1 = nullptr, PlotNode* exit2 = nullptr, PlotNode* exit3 = nullptr, PlotNode* exit4 = nullptr); // constructor

    std::string description; //the text associated with this plotnode

    std::string print(); // print out description, pausing at newlines ('\n')
    PlotNode* exit(int choice); // return the next plotnode based on input
};

