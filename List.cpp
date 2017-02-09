#include "List.h"


List::List()
{
    size=0;
    first=last=NULL;
}


List::List(const List& l)
{
    copy(l);
}

List::~List()
{
    //for (int i=0;i<size;i++)
        ;//delete
}
void List::pop_front()
{
    if (first==NULL)
        return;
    if (first==last)
    {
		delete first;
        first=last=NULL;
        size=0;
        return;
    }
    Node* aux=first->get_next();
    aux->set_prev(last);
	last->set_next(aux);
    delete first;
    first=aux;
    size--;
}
void List::pop_back()
{
    if (first==NULL)
        return;
    if (first==last)
    {
		delete first;
        first=last=NULL;
        size=0;
        return;
    }
    Node* aux=last->get_prev();
    aux->set_next(first);
	first->set_prev(aux);
    delete last;
    last=aux;
    size--;
}
void List::pop(Node* node) {
	if (first == node)
		first = first->get_next();
	if (last == node)
		last = last->get_prev();
	node->get_prev()->set_next(node->get_next());
	node->get_next()->set_prev(node->get_prev());
	size--;
	delete node;
}
void List::push_front(float x, float y)
{
    if (first==NULL)        //if the list is empty
    {
        first=last=new Node(x, y);
		first->set_next(first);
		first->set_prev(first);
		last->set_next(first);
		last->set_prev(first);
        size=1;
        return;
    }
	
	Node* aux = new Node(x, y);
	aux->set_next(first);
	aux->set_prev(last);
	last->set_next(aux);
	first->set_prev(aux);
	first = aux;
	size ++;
	return;
}
void List::push_back(float x, float y)
{
	if (first == NULL)        //if the list is empty
	{
		first = last = new Node(x, y);
		last->set_next(last);
		last->set_prev(last);
		first->set_next(last);
		first->set_prev(last);
		size = 1;
		return;
	}
	Node* aux = new Node(x, y);
	aux->set_next(first);
	aux->set_prev(last);
	first->set_prev(aux);
	last->set_next(aux);
	last = aux;
	size++;
	return;
}


void List::push_front(Node* target)
{
	if (first == NULL)        //if the list is empty
	{
		first = last = new Node();
		first->set_target(target);
		first->set_next(first);
		first->set_prev(first);
		last->set_next(first);
		last->set_prev(first);
		size = 1;
		return;
	}

	Node* aux = new Node();
	aux->set_target(target);
	aux->set_next(first);
	aux->set_prev(last);
	last->set_next(aux);
	first->set_prev(aux);
	first = aux;
	size++;
	return;
}
void List::push_back(Node* target)
{
	if (first == NULL)        //if the list is empty
	{
		first = last = new Node();
		first->set_target(target);
		last->set_next(last);
		last->set_prev(last);
		first->set_next(last);
		first->set_prev(last);
		size = 1;
		return;
	}
	Node* aux = new Node();
	aux->set_target(target);
	aux->set_next(first);
	aux->set_prev(last);
	first->set_prev(aux);
	last->set_next(aux);
	last = aux;
	size++;
	return;
}
int List::Size()    const
{
    return size;
}
void List::Show()
{
    if (first==NULL)
    {
        cout<<"Lista goala";
        return;
    }
    Node*aux=first;
    while (aux!=last)
    {
        cout<<aux->get_coord_x()<<aux->get_coord_y();
        aux=aux->get_next();
    }
	cout << aux->get_coord_x() << aux->get_coord_y();
}

void List::Show(ostream& out) const
{
	if (first == NULL)
	{
		out << "Lista goala";
		return;
	}
	Node*aux = first;
	while (aux != last)
	{
		out << aux->get_coord_x() << aux->get_coord_y();
		aux = aux->get_next();
	}
	out << aux->get_coord_x() << aux->get_coord_y();
}


Node* List::peak(int pos) const       //this method offers the possibility to crack the program. TO DO: delete it. it also needs iterator for it uses too much precessing speed.
{
    if (pos<1)
        return NULL;
    if (pos>size)
        return NULL;
    if (first==NULL)
        return NULL;
    Node* aux=first;
    int i=1;
    while (i<pos&&aux!=NULL)
    {
        i++;
        aux=aux->get_next();
    }
    //if (aux!=NULL)
        return aux;
}
void List::set_info(int pos, float x, float y)
{
    if (pos<1)
        return;
    if (pos>size)
        return;
    if (first==NULL)
        return;
    Node* aux=first;
    int i=1;
    while (i<pos&&aux!=NULL)
    {
        i++;
        aux=aux->get_next();
    }
    if (aux!=NULL)
        aux->set_coords(x, y);
    return;
}
/*
List& List::operator=(const List &l)
{
    copy(l);
    return *this;
}

bool List::operator==(const List &l)
{
    if (size!=l.Size())
        return false;
    if (size==0)return true;
    int i=1;
    Node* aux1=first;
    Node* aux2=l.peak(1);
    while (i<=size&&aux1!=NULL)
    {
        if (aux1->get_info()!=aux2->get_info())
            return false;
        i++;
        aux1=aux1->get_next();
        aux2=aux2->get_next();
    }
    return true;
}
*/
void List::copy(const List& l)
{
    //cout<<" ia cu porc ";
    size=l.Size();
    for (int i=1;i<=size;i++)
    {
        if(i==1)
        {
            first=new Node(l.peak(i)->get_coord_x(), l.peak(i)->get_coord_y());
			last = first;
			first->set_next(last);
			first->set_prev(last);
        }
        else
        {
            Node* aux=new Node(l.peak(i)->get_coord_x(), l.peak(i)->get_coord_y(), last, first);
			first->set_prev(aux);
			last->set_next(aux);
            last=aux;
        }
    }
}

