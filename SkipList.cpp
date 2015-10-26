//
//  SkipList.cpp
//  CS350 Fall 2013
//

#include "SkipList.h"
#include "Flags.h"

#if CONSTRUCTOR || ALL
template <class T>
SkipList<T>::SkipList()
{
	int height = SkipList<T>::maxHeight;
	this->head = new Node<T>(height);
	// FIXME the following line won't compile
	// this->head = new Node<T>(SkipList<T>::maxHeight);
	this->head->height = 1;
}

template <class T>
SkipList<T>::~SkipList()
{
	Node<T> *node = this->head;
	while (node != NULL) {
		Node<T> *last = node;
		node = node->next[0];
		delete last;
	}
}
#endif

#if FIND || ALL
template <class T>
bool SkipList<T>::find(const T & x) const
{
	Node<T> *node = this->head;
	int h = node->height-1;

	while (node->next[h] != NULL && h > 0) {
		if (node->next[h]->data == x) {
			return true;
		} else if (node->next[h]->data > x) {
			h--;
		} else if (node->next[h]->data < x) {
			node = node->next[h];
		}
	}

	return false;
}
#endif

#if INSERT || ALL
// TODO: insert() method
#endif

#if REMOVE || ALL
// TODO: remove() method
#endif

#if ISEMPTY || ALL
// TODO: isEmpty() method
#endif

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
#endif

#if RANDOM || ALL
// TODO: randomLevel() method
#endif

// random number generator
template <class T>
double SkipList<T>::getRandomNumber()
{
    static int i = 0;
    static double a[10] = {0.32945,0.85923,0.12982,0.16250,0.56537,0.64072,0.27597,0.83957,0.75531,0.22502};
    
    return a[(i++)%10];
}

// printList() method
template <class T>
void SkipList<T>::printList()
{
	Node<T> *n = head;
	
	if (isEmpty())
	{
        std::cout << "Empty List" << std::endl;
	} else {
		while(n->next[0] != NULL)
		{
            n = n->next[0];
            // Print node data
            std::cout << "Node " << n->data << " height " << n->height << ": ";
            
            // Print levels
            for (int i=(n->height - 1); i >= 0; i--) {
                std::cout << "Level " << i << " -> ";
                if (n->next[i] != NULL) {
                    std::cout << n->next[i]->data;
                } else {
                    std::cout << "NULL";
                }
                std::cout << ",";
            }
            std::cout << std::endl;
		}
        std::cout << std::endl;
	}
}

template class SkipList<int>;
