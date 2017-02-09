#include "Node.h"

Node::Node()
{
	x = y = 0.0f;
    next=NULL;
    prev=NULL;
}
Node::Node(float x, float y)
{
	this->x = x;
	this->y = y;
    next=NULL;
    prev=NULL;
}
Node::Node(float x, float y, Node* prev, Node* next)
{
	this->x = x;
	this->y = y;
    this->next=next;
    this->prev=prev;
}
Node::Node(const Node& node)
{
	this->x = node.x;
	this->y = node.y;
	this->target = node.target;
    next=node.next;
    prev=node.prev;
}
/*Node::~Node()
{
    info=0;
    delete next;
}*/
void Node::set_coords(float x, float y)
{
	this->x = x;
	this->y = y;
}
void Node::set_target(Node *trgt)
{
	target = trgt;
}
Node* Node::get_target()
{
	return target;
}
float Node::get_coord_x()
{
    return x;
}
float Node::get_coord_y()
{
	return y;
}
void Node::set_next(Node* next)
{
    this->next=next;
}
Node* Node::get_next() const
{
    return this->next;
}
void Node::set_prev(Node* prev)
{
	this->prev=prev;
}
Node* Node::get_prev() const
{
    return prev;
}
