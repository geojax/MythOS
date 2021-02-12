#include "PlotNode.h"
#include <iostream>

PlotNode::PlotNode(PlotNode* exit1, PlotNode* exit2, PlotNode* exit3, PlotNode* exit4)
{
    next_nodes[0] = exit1;
    next_nodes[1] = exit2;
    next_nodes[2] = exit3;
    next_nodes[3] = exit4;
}

std::string PlotNode::print()
{
    int i = 0;
    while (description[i] != '\n' && i < description.length()) {
        std::cout << description[i];
        ++i;
    }
    return std::string();
}

PlotNode* PlotNode::exit(int choice)
{
    if (choice < 1 || choice > 4 || next_nodes[choice] == nullptr) {
        std::cout << "ERROR: That choice is not possible. Try again\n";
        return this;
    }

    return next_nodes[choice - 1];
}
