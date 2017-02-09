#ifndef LIST_H
#define LIST_H
#include <iostream>
#include "Node.h"

using namespace std;

class List                  //functionally class customized for working with digits, *needs throw statements
{
    int size;
    Node* first;
    Node* last;
	
public:
    List();
    List(const List& l);
    ~List();

    void pop_back();
    void pop_front();
    void push_back(float x, float y);
    void push_front(float x, float y);
	void push_back(Node* target);
	void push_front(Node* target);
    void pop(Node* node);
    Node* peak(int pos) const;      //probably should change this to a int return type
    void set_info(int pos, float x, float y);

    int Size()  const;
    void Show();
    void Show(ostream& out) const;

private:
    void copy(const List& l);
};

#endif // LIST_H
