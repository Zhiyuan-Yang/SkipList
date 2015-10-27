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
	std::cout << "DEBUG: Allocate new skip list\n";
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
		std::cout << "DEBUG: Deallocating node " << last->data << std::endl;
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

	while (node->next[h] != NULL && h >= 0) {
		if (node->next[h]->data == x) {
			std::cout << "DEBUG: " << x << " found\n";
			return true;
		} else if (node->next[h]->data > x) {
			h--;
		} else if (node->next[h]->data < x) {
			node = node->next[h];
		}
	}

	std::cout << "DEBUG: " << x << " not found\n";
	return false;
}
#endif

#if INSERT || ALL
template <class T>
void SkipList<T>::insert(const T & x)
{
	int level = randomLevel();
	Node<T> *newnode = new Node<T>(x, level), *node = head;

	while (--level >= 0) {
		while (node->next[level] != NULL && node->next[level]->data < x)
			node = node->next[level];
		if (node->next[level] != NULL && node->next[level]->data == x) {
			std::cout << "DEBUG: Insert failed - node already exists\n";
			return;
		}
		newnode->next[level] = node->next[level];
		node->next[level] = newnode;
	}
	std::cout << "DEBUG: Inserted value " << x << " at level " << newnode->height << std::endl;
}
#endif

#if REMOVE || ALL
template <class T>
void SkipList<T>::remove(const T & x)
{
	Node<T> *delnode = NULL, *node = this->head;
	// FIXME the following won't work, no idea why
	// for (int level = SkipList<T>::maxHeight-1; level >= 0; level--) {
	for (int level = this->head->height-1; level >= 0; level--) {
		while (node->next[level] != NULL && node->next[level]->data < x)
			node = node->next[level];
		if (node->next[level] != NULL && node->next[level]->data == x) {
			delnode = node->next[level];
			node->next[level] = delnode->next[level];
		}
	}

	if (delnode == NULL) {
		std::cout << "DEBUG: Delete failed - value " << x << " not found\n";
	} else {
		delete delnode;
		std::cout << "DEBUG: Delete success - value " << x << " removed\n";
	}
}
#endif

#if ISEMPTY || ALL
// TODO: isEmpty() method
#endif

#if MAKEEMPTY || ALL
// TODO: makeEmpty() method
#endif

#if RANDOM || ALL
template <class T>
int SkipList<T>::randomLevel()
{
	int level = 0;
	double pushup;
	do {
		level++;
		pushup = getRandomNumber();
	} while (level < SkipList<T>::maxHeight && pushup < 0.5);
	
	return level;
}
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
