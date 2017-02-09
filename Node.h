#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

class Node              //functionally independent class for storing digits(unsigned short)
{

	float x, y;
    Node* next;
    Node* prev;
	Node* target;
public:
    Node();
    Node(float x, float y);
    Node(float x, float y, Node* prev, Node* next);
    Node(const Node& node);     //copy constructor
   // ~Node();
    void set_coords(float x, float y);
	void set_target(Node *trgt);
	Node* get_target();
    float get_coord_x();
	float get_coord_y();
    void set_next(Node* next);
    Node* get_next() const;
    void set_prev(Node* prev);
    Node* get_prev() const;
};

#endif // NODE_H
