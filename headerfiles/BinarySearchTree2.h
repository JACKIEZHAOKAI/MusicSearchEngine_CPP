#ifndef BINARYSEARCHTREE2_H_
#define BINARYSEARCHTREE2_H_

#include <iostream>
#include <cstddef>
#include <string>
#include <assert.h>
#include <fstream>
#include "Song.h"

using namespace std;

class BinarySearchTree2 {
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

	void inOrderPrintHelper(NodePtr root);
	//private helper function for inOrderPrint
	//recursively prints tree values in order from smallest to largest

	void preOrderPrintHelper(NodePtr root);
	//private helper function for preOrderPrint
	//recursively prints tree values in preorder

	void postOrderPrintHelper(NodePtr root);
	//private helper function for postOrderPrint
	//recursively prints tree values in postorder

	bool findHelper(NodePtr root, string value);

	bool findArtistHelper(NodePtr root, string value);

	Song minimumHelper(NodePtr root);

	Song maximumHelper(NodePtr root);

	NodePtr removeHelper(NodePtr root, string value);

	int getSizeHelper(NodePtr root);

	void destructorHelper(NodePtr root);

	void copyHelper(NodePtr root, const BinarySearchTree2 &binarysearchtree);

	/**Public functions*/

public:
	BinarySearchTree2();

	~BinarySearchTree2();

	BinarySearchTree2(const BinarySearchTree2 &binarysearchtree);

	//Access functions
	Song minimum();

	Song maximum();

	bool isEmpty();

	Song getRoot();

	bool find(string value);

	bool findArtist(string value);

	//Maniupulation functions
	void insert(Song value);

	void remove(string value);

	//Additional functions
	void inOrderPrint();

	void preOrderPrint();

	void postOrderPrint();

	string lowerCase(string title);

};

BinarySearchTree2::BinarySearchTree2() :
		root(NULL) {
}

void BinarySearchTree2::destructorHelper(NodePtr root) {
	if (root) {
		if (root->left)
			destructorHelper(root->left);
		if (root->right)
			destructorHelper(root->right);
		delete root;
	}

}

void BinarySearchTree2::copyHelper(NodePtr root,
		const BinarySearchTree2 &binarysearchtree) {
	if (binarysearchtree.root)
		root->data = binarysearchtree.root->data;
	if (binarysearchtree.root->left)
		copyHelper(root->left, binarysearchtree);
	if (binarysearchtree.root->right)
		copyHelper(root->right, binarysearchtree);
}

BinarySearchTree2::BinarySearchTree2(
		const BinarySearchTree2 &binarysearchtree) {
	copyHelper(root, binarysearchtree);
}

BinarySearchTree2::~BinarySearchTree2() {
	destructorHelper(root);
}

void BinarySearchTree2::insert(Song value) {
	{
		if (root == NULL) {
			root = new Node(value);
		} else {
			insertHelper(root, value);
		}
	}
}

void BinarySearchTree2::insertHelper(NodePtr root, Song value) {
	if (lowerCase(value.get_artist()) <= lowerCase(root->data.get_artist())) {
		if (root->left == NULL)
			root->left = new Node(value);
		else
			insertHelper(root->left, value);
	} else {
		if (root->right == NULL)
			root->right = new Node(value);
		else
			insertHelper(root->right, value);
	}
}

void BinarySearchTree2::inOrderPrintHelper(NodePtr root) {
	if (root != NULL) {
		inOrderPrintHelper(root->left);
		root->data.print_song();
		inOrderPrintHelper(root->right);
	}
}

void BinarySearchTree2::inOrderPrint() {
	inOrderPrintHelper(root);
	cout << endl;
}

void BinarySearchTree2::preOrderPrintHelper(NodePtr root) {
	if (root != NULL) {
		root->data.print_song();
		preOrderPrintHelper(root->left);
		preOrderPrintHelper(root->right);
	}
}

void BinarySearchTree2::preOrderPrint() {
	preOrderPrintHelper(root);
	cout << endl;
}

void BinarySearchTree2::postOrderPrintHelper(NodePtr root) {
	if (root != NULL) {
		postOrderPrintHelper(root->left);
		postOrderPrintHelper(root->right);
		root->data.print_song();
	}
}

void BinarySearchTree2::postOrderPrint() {
	postOrderPrintHelper(root);
	cout << endl;
}

bool BinarySearchTree2::findHelper(NodePtr root, string value) {
	assert(!isEmpty());
	if (lowerCase(root->data.get_title()) == lowerCase(value))
		return true;
	else if (lowerCase(value) > lowerCase(root->data.get_title())) {
		if (root->right == NULL)
			return false;
		else
			return findHelper(root->right, value);
	} else if (lowerCase(value) < lowerCase(root->data.get_title())) {
		if (root->left == NULL)
			return false;
		else
			return findHelper(root->left, value);
	} else
		return false;

}

bool BinarySearchTree2::find(string value) {
	assert(!isEmpty());
	if (lowerCase(value) == lowerCase(root->data.get_title()))
		return true;
	else
		return findHelper(root, value);
}

Song BinarySearchTree2::minimumHelper(NodePtr root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root->data;
}

Song BinarySearchTree2::minimum() {
	assert(!isEmpty());
	return minimumHelper(root);
}

Song BinarySearchTree2::maximumHelper(NodePtr root) {
	while (root->right != NULL) {
		root = root->right;
	}
	return root->data;
}

Song BinarySearchTree2::maximum() {
	assert(!isEmpty());
	return maximumHelper(root);
}

bool BinarySearchTree2::isEmpty() {
	return (root == NULL);
}

Song BinarySearchTree2::getRoot() {
	assert(!isEmpty());
	return root->data;
}

typename BinarySearchTree2::NodePtr BinarySearchTree2::removeHelper(
		NodePtr root, string value) {
	if (root == NULL)
		return root;
	else if (lowerCase(value) < lowerCase(root->data.get_title()))
		root->left = removeHelper(root->left, value);
	else if (lowerCase(value) > lowerCase(root->data.get_title()))
		root->right = removeHelper(root->right, value);
	else if (lowerCase(value) == lowerCase(root->data.get_title())) {
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
		} else if (root->left != NULL && root->right == NULL) {
			NodePtr temp = root;
			root = root->left;
			delete temp;
		} else if (root->left == NULL && root->right != NULL) {
			NodePtr temp = root;
			root = root->right;
			delete temp;
		} else {
			root->data = minimumHelper(root->right);
			root->right = removeHelper(root->right,
					minimumHelper(root->right).get_title());
		}
	}
	return root;
}

void BinarySearchTree2::remove(string value) {
	if (find(value))
		root = removeHelper(root, value);
	else
		return;
}

bool BinarySearchTree2::findArtistHelper(NodePtr root, string value) {
	if (isEmpty()) {
		cout << "List of songs is empty!" << endl;
		return false;
	} else {
		if (lowerCase(root->data.get_artist()) == lowerCase(value)) {
			cout << "Artist found!" << endl;
			root->data.print_song();
			return true;
		} else if (lowerCase(value) > lowerCase(root->data.get_artist())) {
			if (root->right == NULL) {
				cout << "Artist not found!" << endl;
				return false;
			} else
				return findArtistHelper(root->right, value);
		} else if (lowerCase(value) < lowerCase(root->data.get_artist())) {
			if (root->left == NULL) {
				cout << "Artist not found!" << endl;
				return false;
			} else
				return findArtistHelper(root->left, value);
		} else {
			cout << "Artist not found!" << endl;
			return false;
		}
	}
}

bool BinarySearchTree2::findArtist(string value) {
	if (isEmpty()) {
		cout << "List of songs is empty!" << endl;
		return false;
	} else {
		if (lowerCase(value) == lowerCase(root->data.get_artist())) {
			cout << "Artist found!" << endl;
			root->data.print_song();
			return true;
		} else
			return findArtistHelper(root, value);
	}
}

string BinarySearchTree2::lowerCase(string title) {
	for (int i = 0; i < title.length(); i++)
		title[i] = tolower(title[i]);
	return title;
}

#endif /* BINARYSEARCHTREE2_H_ */
