#include"BinarySearchTree.h"

BinarySearchTree::BinarySearchTree() :
		root(NULL) {
}

void BinarySearchTree::destructorHelper(NodePtr root) {
	if (root) {
		if (root->left)
			destructorHelper(root->left);
		if (root->right)
			destructorHelper(root->right);
		delete root;
	}

}

void BinarySearchTree::copyHelper(NodePtr root,
		const BinarySearchTree &binarysearchtree) {
	if (binarysearchtree.root)
		root->data = binarysearchtree.root->data;
	if (binarysearchtree.root->left)
		copyHelper(root->left, binarysearchtree);
	if (binarysearchtree.root->right)
		copyHelper(root->right, binarysearchtree);
}

BinarySearchTree::BinarySearchTree(const BinarySearchTree &binarysearchtree) {
	copyHelper(root, binarysearchtree);
}

BinarySearchTree::~BinarySearchTree() {
	destructorHelper(root);
}

void BinarySearchTree::insert(Song value) {
	{
		if (root == NULL) {
			root = new Node(value);
		} else {
			insertHelper(root, value);
		}
	}
}

void BinarySearchTree::insertHelper(NodePtr root, Song value) {
	if (lowerCase(value.get_title()) == lowerCase(root->data.get_title()))
		return;
	else if (lowerCase(value.get_title()) < lowerCase(root->data.get_title())) {
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

void BinarySearchTree::in_order_print_to_file_helper(NodePtr root,
		ostream& fout) {
	if (root != NULL) {
		in_order_print_to_file_helper(root->left, fout);
		root->data.print_song_to_file(fout);
		in_order_print_to_file_helper(root->right, fout);
	}
}

void BinarySearchTree::in_order_print_to_file(ostream& fout) {
	in_order_print_to_file_helper(root, fout);
	fout << endl;
}

void BinarySearchTree::inOrderPrintHelper(NodePtr root) {
	if (root != NULL) {
		inOrderPrintHelper(root->left);
		root->data.print_song();
		inOrderPrintHelper(root->right);
	}
}

void BinarySearchTree::inOrderPrint() {
	inOrderPrintHelper(root);
	cout << endl;
}

void BinarySearchTree::preOrderPrintHelper(NodePtr root) {
	if (root != NULL) {
		root->data.print_song();
		preOrderPrintHelper(root->left);
		preOrderPrintHelper(root->right);
	}
}

void BinarySearchTree::preOrderPrint() {
	preOrderPrintHelper(root);
	cout << endl;
}

void BinarySearchTree::postOrderPrintHelper(NodePtr root) {
	if (root != NULL) {
		postOrderPrintHelper(root->left);
		postOrderPrintHelper(root->right);
		root->data.print_song();
	}
}

void BinarySearchTree::postOrderPrint() {
	postOrderPrintHelper(root);
	cout << endl;
}

bool BinarySearchTree::findHelper(NodePtr root, string value) {
	if (isEmpty()) {
		cout << "List of songs is empty!" << endl;
		return false;
	} else {
		if (lowerCase(root->data.get_title()) == lowerCase(value)) {
			cout << "Song found!" << endl;
			root->data.print_song();
			return true;
		} else if (lowerCase(value) > lowerCase(root->data.get_title())) {
			if (root->right == NULL) {
				cout << "Song not found!" << endl;
				return false;
			} else
				return findHelper(root->right, value);
		} else if (lowerCase(value) < lowerCase(root->data.get_title())) {
			if (root->left == NULL) {
				cout << "Song not found!" << endl;
				return false;
			} else
				return findHelper(root->left, value);
		} else {
			cout << "Song not found!" << endl;
			return false;
		}
	}
}

bool BinarySearchTree::find(string value) {
	if (isEmpty()) {
		cout << "List of songs is empty!" << endl;
		return false;
	} else {
			return findHelper(root, value);
	}
}

bool BinarySearchTree::findh(string value)
{
	if (isEmpty()) {
		//	cout << "List of songs is empty!" << endl;
			return false;
		} else {
				return findHelperHT(root, value);
		}
}

bool BinarySearchTree::findHelperHT(NodePtr root, string value) {
	if (isEmpty()) {

		return false;
	} else {
		if (lowerCase(root->data.get_title()) == lowerCase(value)) {

			return true;
		} else if (lowerCase(value) > lowerCase(root->data.get_title())) {
			if (root->right == NULL) {

				return false;
			} else
				return findHelperHT(root->right, value);
		} else if (lowerCase(value) < lowerCase(root->data.get_title())) {
			if (root->left == NULL) {
				return false;
			} else
				return findHelperHT(root->left, value);
		} else {

			return false;
		}
	}
}




Song BinarySearchTree::minimumHelper(NodePtr root) {
	while (root->left != NULL) {
		root = root->left;
	}
	return root->data;
}

Song BinarySearchTree::minimum() {
	assert(!isEmpty());
	return minimumHelper(root);
}

Song BinarySearchTree::maximumHelper(NodePtr root) {
	while (root->right != NULL) {
		root = root->right;
	}
	return root->data;
}

Song BinarySearchTree::maximum() {
	assert(!isEmpty());
	return maximumHelper(root);
}

bool BinarySearchTree::isEmpty() {
	return (root == NULL);
}

Song BinarySearchTree::getRoot() {
	assert(!isEmpty());
	return root->data;
}

int BinarySearchTree::getSizeHelper(NodePtr root) {
	if (root == NULL) {
		return 0;
	} else {
		return (1 + getSizeHelper(root->left) + getSizeHelper(root->right));
	}
}

int BinarySearchTree::getSize() {
	return getSizeHelper(root);
}

typename BinarySearchTree::NodePtr BinarySearchTree::removeHelper(NodePtr root,
		string value) {
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
			cout << "Song has been deleted!" << endl;
		} else if (root->left != NULL && root->right == NULL) {
			NodePtr temp = root;
			root = root->left;
			delete temp;
			cout << "Song has been deleted!" << endl;
		} else if (root->left == NULL && root->right != NULL) {
			NodePtr temp = root;
			root = root->right;
			delete temp;
			cout << "Song has been deleted!" << endl;
		} else {
			root->data = minimumHelper(root->right);
			root->right = removeHelper(root->right,
					minimumHelper(root->right).get_title());
		}
	}
	return root;
}

typename BinarySearchTree::NodePtr BinarySearchTree::removeHelperS(NodePtr root,
		string value) {
	if (root == NULL)
		return root;
	else if (lowerCase(value) < lowerCase(root->data.get_title()))
		root->left = removeHelperS(root->left, value);
	else if (lowerCase(value) > lowerCase(root->data.get_title()))
		root->right = removeHelperS(root->right, value);
	else if (lowerCase(value) == lowerCase(root->data.get_title())) {
		if (root->left == NULL && root->right == NULL) {
			delete root;
			root = NULL;
			//cout << "Song has been deleted!" << endl;
		} else if (root->left != NULL && root->right == NULL) {
			NodePtr temp = root;
			root = root->left;
			delete temp;
			//cout << "Song has been deleted!" << endl;
		} else if (root->left == NULL && root->right != NULL) {
			NodePtr temp = root;
			root = root->right;
			delete temp;
			//cout << "Song has been deleted!" << endl;
		} else {
			root->data = minimumHelper(root->right);
			root->right = removeHelperS(root->right,
					minimumHelper(root->right).get_title());
		}
	}
	return root;
}

void BinarySearchTree::removeS(string value) {
	if (isEmpty()) {
		//cout << "List of songs is empty!" << endl;
	}
	if (findh(value))
		root = removeHelperS(root, value);

}


void BinarySearchTree::remove(string value) {
	if (isEmpty()) {
		cout << "List of songs is empty!" << endl;
	}
	if (findh(value))
		root = removeHelper(root, value);
	else
		cout << "This song is not in the list!" << endl;
}

int BinarySearchTree::getHeightHelper(NodePtr root) {
	if (root == NULL) {
		return -1;
	} else {
		return (max(getHeightHelper(root->left), getHeightHelper(root->right))
				+ 1);
	}
}

int BinarySearchTree::getHeight() {
	assert(!isEmpty());
	return getHeightHelper(root);
}

int BinarySearchTree::getMinuteHelper(NodePtr root) {
	if (root == NULL) {
		return 0;
	} else {
		return (root->data.get_minute() + getMinuteHelper(root->left)
				+ getMinuteHelper(root->right));
	}
}

int BinarySearchTree::getMinute() {
	return getMinuteHelper(root);
}

int BinarySearchTree::getSecondHelper(NodePtr root) {
	if (root == NULL) {
		return 0;
	} else {
		return (root->data.get_second() + getSecondHelper(root->left)
				+ getSecondHelper(root->right));
	}
}

int BinarySearchTree::getSecond() {
	return getSecondHelper(root);
}

string BinarySearchTree::lowerCase(string title) {
	for (int i = 0; i < title.length(); i++)
		title[i] = tolower(title[i]);
	return title;
}

void BinarySearchTree::statistic() {
	cout << "Total songs: " << getSize() << endl;
	cout << "Total length: " << getMinute() + (getSecond() / 60) << " minutes "
			<< (getSecond() % 60) << " seconds" << endl;
	int avg = (getMinute() * 60 + getSecond()) / getSize();
	cout << "Average length: " << (avg / 60) << " minutes " << (avg % 60)
			<< " seconds" << endl;
}


Song BinarySearchTree::findSongHelper(NodePtr root, string value) {
	if (isEmpty()) {
		cout << "List of songs is empty!" << endl;
	} else {
		if (lowerCase(root->data.get_title()) == lowerCase(value)) {
			return root->data;
		} else if (lowerCase(value) > lowerCase(root->data.get_title())) {
			if (root->right == NULL) {
				cout << "Song not found!" << endl;
			} else
				return findSongHelper(root->right, value);
		} else if (lowerCase(value) < lowerCase(root->data.get_title())) {
			if (root->left == NULL) {
				cout << "Song not found!" << endl;
			} else
				return findSongHelper(root->left, value);
		} else {
			cout << "Song not found!" << endl;
		}
	}
}
Song BinarySearchTree::findSong(string value) {
	if (isEmpty()) {
		cout << "List of songs is empty!" << endl;
	} else {
		if (lowerCase(value) == lowerCase(root->data.get_title())) {
			return root->data;
		} else
			return findSongHelper(root, value);
	}
}


