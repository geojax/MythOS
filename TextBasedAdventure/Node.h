#pragma once
#include <string>
class Node
{
protected:
	Node* next_nodes[4];
public:
	Node(Node* exit1 = nullptr, Node* exit2 = nullptr, Node* exit3 = nullptr, Node* exit4 = nullptr);
};
