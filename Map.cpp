/* Implementation of Ordered Map DS using Red Black Tree 
	
	Four Methods:
	insert(key): insert key in map
	del(key): delete one occurence of key(if present)
	find(key):	 find if key exist
	iterate():	 print all keys in increasing order with frequencies
*/

#include <bits/stdc++.h>
using namespace std;
enum Color { RED, BLACK };
//structure of each node of a Red-Black Tree

template <class T>
struct node
{
	T data;
	int count;
	Color color;
	bool leftChild;
	node *left,*right,*parent;
};

template <class T>
node<T>* newNode(T n)
{
	node<T> *temp = new node<T>;
	temp->data = n;
	temp->count = 1;
	temp->color = RED;
	temp->leftChild = true;
	temp->left = temp->right = temp->parent = NULL;
	return temp;
}

template <class T>
class RBTree
{
	node<T> *root;
	
public:
	RBTree(): root(NULL) {};

	node<T>* getRoot()
	{
		return root;
	}
	void insert(T);
	void check(node<T> *);
	void rotate(node<T> *);
};

template <class T>
Color getColor(node<T>* temp)
{
	if(temp)
		return temp->color;

	return BLACK;
}

template <class T>
void RBTree<T>::rotate(node<T>* temp)
{
	node<T> *parent = temp->parent;
	node<T> *grandparent = parent->parent;
	node<T> *top;
	node<T> *temp1,*temp2,*temp3,*temp4,*final;
	bool leftChild;
	int c=0;

	if(parent->leftChild)
	{
		if(temp->leftChild)
			c=0;
		else
			c=1;
	}
	else
	{
		if(temp->leftChild)
			c=3;
		else
			c=2;
	}

	top = grandparent->parent;
	switch(c)
	{
		// Left Left case
		case 0:

			//rotation
			temp3 = parent->right;
			parent->right = grandparent;
			grandparent->parent = parent;
			grandparent->left = temp3;
			if(temp3)
				temp3->parent = grandparent;

			//color change
			parent->color = BLACK;
			grandparent->color = RED;

			//adjust left right value of nodes
			leftChild = grandparent->leftChild;
			grandparent->leftChild = false;
			parent->leftChild = leftChild;

			final = parent;
			break;

		// Left Right case
		case 1:

			//rotation
			temp2 = temp->left;
			temp3 = temp->right;
			temp->left = parent;
			temp->right = grandparent;
			grandparent->left = temp3;
			parent->right = temp2;

			grandparent->parent = temp;
			parent->parent = temp;
			if(temp3)
				temp3->parent = grandparent;
			if(temp2)
				temp2->parent = parent;

			//color change
			grandparent->color = RED;
			temp->color = BLACK;

			//adjust left right value of nodes
			leftChild = grandparent->leftChild;
			grandparent->leftChild = false;
			temp->leftChild = leftChild;

			final = temp;
			break;

		// Right Right case
		case 2:

			//rotation
			temp3 = parent->left;
			parent->left = grandparent;
			grandparent->parent = parent;
			grandparent->right = temp3;
			if(temp3)
				temp3->parent = grandparent;

			//color change
			parent->color = BLACK;
			grandparent->color = RED;

			//adjust left right value of nodes
			leftChild = grandparent->leftChild;
			grandparent->leftChild = true;
			parent->leftChild = leftChild;

			final = parent;
			break;

		// Right Left case
		case 3:

			//rotation
			temp3 = temp->left;
			temp4 = temp->right;
			temp->left = grandparent;
			temp->right = parent;
			grandparent->right = temp3;
			parent->left = temp4;

			grandparent->parent = temp;
			parent->parent = temp;
			if(temp3)
				temp3->parent = grandparent;
			if(temp4)
				temp4->parent = parent;

			//color change
			grandparent->color = RED;
			temp->color = BLACK;

			//adjust left right value of nodes
			leftChild = grandparent->leftChild;
			grandparent->leftChild = true;
			temp->leftChild = leftChild;

			final = temp;
			break;

	}

	//final touch
	if(top)
	{
		if(leftChild)
			top->left = final;
		else
			top->right = final;
		final->parent = top;
	}
	else
	{
		final->parent  = NULL;
		root = final;
	}
}

template <class T>
void RBTree<T>::check(node<T> *temp)
{
	if(temp == root)
	{
		temp->color = BLACK;
		return;
	}

	//If Inserted node's parent is Black, then no problem.
	if(temp->parent->color == BLACK)
		return;

	node<T> *uncle,*grandparent = temp->parent->parent;
	if(temp->parent->leftChild)	
		uncle = grandparent->right;
	else
		uncle = grandparent->left;

	if(getColor(uncle) == RED)
	{
		temp->parent->color = uncle->color = BLACK;
		grandparent->color = RED;
		check(grandparent);
	}
	else
		rotate(temp);
}

template <class T>
void RBTree<T>::insert(T n)
{
	//If first element inserted
	if(root == NULL)
	{
		root = newNode(n);
		root->color = BLACK;
		return;
	}

	//Insert element in BST fashion
	node<T> *temp=root,*parent;
	while(true)
	{
		if(n < temp->data)
		{
			if(temp->left)
				temp = temp->left;
			else
			{
				temp->left = newNode(n);
				temp->left->leftChild = true;
				temp->left->parent = temp;
				temp = temp->left;
				break;
			}
		}
		else if(n > temp->data)
		{
			if(temp->right)
				temp = temp->right;
			else
			{
				temp->right = newNode(n);
				temp->right->leftChild = false;
				temp->right->parent = temp;
				temp = temp->right;
				break;
			}
		}
		else
		{
			temp->count++;
			return;
		}
	}
	check(temp);
}

template <class T>
int traverse(node<T> *temp, T key)
{
	if(!temp)
		return 0;

	if(key==temp->data)
		return temp->count;

	if(key < temp->data)
		return traverse(temp->left, key);

	return traverse(temp->right, key);
}

template <class T>
void mydel(node<T> *temp, T key)
{
	if(!temp)
		return;

	if(key==temp->data)
	{
		if(temp->count)
			temp->count--;
	}

	if(key < temp->data)
		mydel(temp->left, key);

	mydel(temp->right, key);
}

template <class T>
void iter(node<T> *root)
{
	if(!root)
		return;

	iter(root->left);
	cout<<root->data<<":"<<root->count<<" ";
	iter(root->right);
}

template <class T>
class Map
{
	RBTree<T> tree;
public:

	void insert(T);
	int find(T);
	void del(T);
	void iterate(void);
};

template <class T>
void Map<T>::insert(T key)
{
	tree.insert(key);
}

template <class T>
int Map<T>::find(T key)
{
	return traverse(tree.getRoot(),key);
}

template <class T>
void Map<T>::del(T key)
{
	mydel(tree.getRoot(),key);
}

template <class T>
void Map<T>::iterate()
{
	iter(tree.getRoot());
	cout<<endl;
}

int main()
{
	Map<int> intmap;

	int n;
	while(cin>>n)
	{
		intmap.insert(n);
	}
	intmap.del(2);
	cout<<intmap.find(4)<<endl;

	intmap.iterate();

	cin.clear();

	Map<char> charmap;

	char c;
	cin>>c;
	while(c!='-')
	{
		charmap.insert(c);
		cin>>c;
	}
	charmap.del('a');
	cout<<charmap.find('p')<<endl;

	charmap.iterate();

	return 0;
}
