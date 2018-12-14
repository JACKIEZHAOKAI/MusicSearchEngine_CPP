/*
 * List.h
 *
 *  Created on: Dec 6, 2016
 *      Author: xuzhaokai
 */

#ifndef LIST_H_
#define LIST_H_
#include <assert.h>
#include <iostream>
#include <cstddef>
using namespace std;

template <class listitem>
class List
{
private:
    struct Node
    {
        listitem data;
        Node* next;
        Node* previous;
        Node(listitem newdata): data(newdata), next(NULL), previous(NULL) {}
    };
    typedef struct Node* NodePtr;
    NodePtr start;
    NodePtr end;
    NodePtr cursor;
    int length;

public:
    /**Constructors and Destructors */
    List();
    ~List();
    List(const List &list);


    /**Manipulation Procedures*/
    void begin_cursor();

    void add_cursor(listitem data);

    void remove_end();

    void remove_start();

    void add_end(listitem data);

    void add_start(listitem data);

    void remove_cursor();

    void move_cursor();

    /**Accessors*/
    listitem  get_start();

    listitem  get_end();

    listitem  get_cursor();

    bool is_empty();

    bool off_end();

    int get_length();

    int linear_search(int value);

    /**Additional List Operations*/
    void print();

    void printReverse();

    bool operator==(const List&list);

};

//default constructor
template <class listitem>
List<listitem>::List() {
    start = NULL;
    end = NULL;
    cursor = NULL;
    length = 0;
}

//destructor
template <class listitem>
List<listitem>::~List()
{
    cursor = start;
    NodePtr temp;
    while(cursor != NULL)
    {
        temp = cursor->next;
        delete cursor;
        cursor = temp;
    }
}


template <class listitem>
List<listitem>::List(const List &list): length(list.length)
{
    if(list.start == NULL) //If the original list is empty, make an empty list for this list
    {
        start = end = cursor = NULL;
    }
    else
    {
        start = new Node(list.start->data); //using second Node constructor
        NodePtr temp = list.start; //set a temporary node pointer to point at the start of the original list
        cursor = start; //set iterator to point to start of the new list

        while(temp->next != NULL)
        {

            temp = temp->next; //advance up to the next node in the original list
            cursor->next = new Node(temp->data); //using node constructor to create a new node with copy of data
            cursor = cursor->next; //advance to this new node

        }

        end = cursor; //Why do I need this line of code?
        cursor = NULL;

    }
}





/**Manipulation Procedures*/

template <class listitem>	//template the function
void List<listitem>::add_start(listitem data) //List is templated and takes in a generic param
{
    if (length==0) //Why is this necessary?	To test if the list is empty
    {
        start = new Node(data);
        end = start;
    }
    else
    {
        NodePtr N = new Node(data);//create the new node by calling the node constructor
        N->next = start;//set the new node's next field to point to the start
        start->previous = N; //Need to update the previous pointer of start to point back at the new node
        start = N;//make the start be the new node
    }
    length++;
}

template <class listitem>
void List<listitem>::add_end(listitem data)
{
    if (length==0)
    {
        end  = new Node(data);
        start = end;
    }
    else
    {
        NodePtr N = new Node(data);
        end->next = N;
        N->previous=end;
        end = N;
    }
    length++;
}

template <class listitem>
void List<listitem>::remove_start()
{
    assert(length != 0);

    if (length==1)
    {
        delete start;
        start = end = cursor = NULL;
        length = 0;
    }
    else
    {
        start= start->next;
        delete start->previous;
        start->previous= NULL;

        length--;
    }
}

template <class listitem>
void List<listitem>::remove_end()
{
    assert(length != 0);

    if (length==1)
    {
        delete end;
        start = end = cursor = NULL;
        length = 0;
    }
    else
    {
        end= end->previous;
        delete end->next;
        end->next= NULL;

        length--;
    }
}

template <class listitem>
void List<listitem>::begin_cursor()
{
    cursor=start;
}


template <class listitem>
void List<listitem>::add_cursor(listitem data)
{
    assert(cursor == NULL);

	//MADE a change, add data into the front of the cursor!!!

	NodePtr node=new Node(data);

	node->next=cursor;
	node->previous=cursor->previous;

	cursor->previous->next=node;
	cursor->previous=node;

	length++;

}


template <class listitem>
void List<listitem>::remove_cursor()
{

		assert(length!=0);
		assert(cursor!=NULL);
		//pre: cursor is NULL
		if(cursor==start)
			remove_start();
		else if (cursor == end)
			remove_end();
		else
		{
			NodePtr temp = cursor;
			temp ->previous->next = temp ->next;
			temp->next->previous = temp ->previous;
			delete temp;
			//cursor = cursor ->next;
			length--;
			cursor = NULL;
		}

}

template <class listitem>
void List<listitem>::move_cursor()
{
    assert(length!=0);
    assert(cursor!= NULL);
    cursor=cursor->next;
}



//Assess functions
template <class listitem>
listitem List<listitem>::get_start()
{
    assert(start != NULL);
    return start -> data;
}

template <class listitem>
listitem List<listitem>::get_end()
{
    assert(start != NULL);
    return end -> data;
}

template <class listitem>
bool List<listitem>::is_empty()
{
    if (length==0)
        return true;
    else
        return false;
}

template <class listitem>
int List<listitem>::get_length()
{
    return length;
}

template <class listitem>
listitem List<listitem>::get_cursor()
{
    assert(cursor != NULL);
    return cursor -> data;
}


//off_end: returns whether the iterator is off the end of the list
template <class listitem>
bool List<listitem>::off_end()
{
    if(cursor==NULL)
        return true;
    else
        return false;
}

template <class listitem>
int List<listitem>::linear_search(int value)
{
    //precondition: the list is not empty
    assert(length!=0);

    begin_cursor();

    for(int index=1;index<=length;index++)
    {
        if (value != get_cursor())
            move_cursor();
        else
            return index;
    }

    return -1;
}



//Additional operations
template <class listitem>
void  List<listitem>::print()
{
    NodePtr temp = start; //create a temporary iterator
    while (temp != NULL) {
        cout<< temp->data <<"  ";
        temp = temp->next;
    }
    cout << endl;
}

template <class listitem>
void  List<listitem>::printReverse()
{
    NodePtr temp = end; //create a temporary iterator
    while (temp != NULL) {
        cout<< temp->data <<"  ";
        temp = temp->previous;
    }
}


template <class listitem>
bool List<listitem>::operator==(const List<listitem>&list)
{
    if(length != list.length)
    {
        return false;
    }
    else
    {
        NodePtr p1 = start;
        NodePtr p2 = list.start;

        while(p1 != NULL)
        {
            if(p1->data != p2->data)
            {
                return false;
            }
            p1 = p1 ->next;
            p2 = p2 ->next;
        }
    }
    return true;
}




#endif /* LIST_H_ */
