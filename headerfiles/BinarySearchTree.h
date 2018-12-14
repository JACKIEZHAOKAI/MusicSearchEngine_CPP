/*
 *
 * Binh Nguyen
 * Sid Yadav
 */

#ifndef BINARYSEARCHTREE_H_
#define BINARYSEARCHTREE_H_

#include <iostream>
#include <cstddef>
#include <string>
#include <assert.h>
#include <fstream>
#include "Song.h"

using namespace std;

class BinarySearchTree {
private:
	struct Node {
		Song data;
		Node* left;
		Node* right;

		Node(Song newdata) :
				data(newdata), left(NULL), right(NULL) {
		}
	};

	typedef struct Node* NodePtr;
	NodePtr root;

	/**Private helper functions*/

	void insertHelper(NodePtr root, Song value);
	//private helper function for insert
	//recursively inserts a value into the BST

	void in_order_print_to_file_helper(NodePtr root, ostream& fout);
	// similar to inOrderPrintHelper()

	void inOrderPrintHelper(NodePtr root);
	//private helper function for inOrderPrint
	//recursively prints tree values in order from smallest to largest

	void inOrderPrintHelperTitle(NodePtr root);
	//only prints titles

	void preOrderPrintHelper(NodePtr root);
	//private helper function for preOrderPrint
	//recursively prints tree values in preorder

	void postOrderPrintHelper(NodePtr root);
	//private helper function for postOrderPrint
	//recursively prints tree values in postorder

	bool findHelper(NodePtr root, string value);

	Song findSongHelper(NodePtr root, string value);

	bool findHelperHT(NodePtr root, string value);

	Song minimumHelper(NodePtr root);

	Song maximumHelper(NodePtr root);

	NodePtr removeHelper(NodePtr root, string value);
	NodePtr removeHelperS(NodePtr root,
			string value);

	int getSizeHelper(NodePtr root);

	int getHeightHelper(NodePtr root);

	void destructorHelper(NodePtr root);

	void copyHelper(NodePtr root, const BinarySearchTree &binarysearchtree);

	int getMinuteHelper(NodePtr root);

	int getSecondHelper(NodePtr root);

	/**Public functions*/

public:
	BinarySearchTree();

	~BinarySearchTree();

	BinarySearchTree(const BinarySearchTree &binarysearchtree);

	//Access functions
	Song minimum();

	Song maximum();

	bool isEmpty();

	int getSize();

	Song getRoot();

	int getHeight();

	bool find(string value);

	//Maniupulation functions
	void insert(Song value);

	void remove(string value);

	void removeS(string value);

	//Additional functions
	void in_order_print_to_file(ostream& fout);

	void inOrderPrint();

	void preOrderPrint();

	void postOrderPrint();

	bool findh(string value);

	Song findSong(string value);


	int getMinute();

	int getSecond();

	void statistic();

	string lowerCase(string title);

};



#endif /* BINARYSEARCHTREE_H_ */
