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
struct node
{
	int data,count;
	Color color;
	bool leftChild;
	node *left,*right,*parent;
};
node* newNode(int n)
{
	node *temp = new node;
	temp->data = n;
	temp->count = 1;
	temp->color = RED;
	temp->leftChild = true;
	temp->left = temp->right = temp->parent = NULL;
	return temp;
}
class RBTree
{
	node *root;
	
public:
	RBTree(): root(NULL) {};

	node* getRoot()
	{
		return root;
	}
	void insert(int);
	void check(node *);
	void rotate(node *);
};

Color getColor(node* temp)
{
	if(temp)
		return temp->color;

	return BLACK;
}

void RBTree::rotate(node* temp)
{
	node *parent = temp->parent;
	node *grandparent = parent->parent;
	node *top;
	node *temp1,*temp2,*temp3,*temp4,*final;
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
			cout<<final->left->left->data<<" ";
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

void RBTree::check(node *temp)
{
	if(temp == root)
	{
		temp->color = BLACK;
		return;
	}

	//If Inserted node's parent is Black, then no problem.
	if(temp->parent->color == BLACK)
		return;

	node *uncle,*grandparent = temp->parent->parent;
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


void RBTree::insert(int n)
{
	//If first element inserted
	if(root == NULL)
	{
		root = newNode(n);
		root->color = BLACK;
		return;
	}

	//Insert element in BST fashion
	node *temp=root,*parent;
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

int traverse(node *temp, int key)
{
	if(!temp)
		return 0;

	if(key==temp->data)
		return temp->count;

	if(key < temp->data)
		return traverse(temp->left, key);

	return traverse(temp->right, key);
}

void mydel(node *temp, int key)
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

void iter(node *root)
{
	if(!root)
		return;

	iter(root->left);
	cout<<root->data<<":"<<root->count<<" ";
	iter(root->right);
}

class Map
{
	RBTree tree;
public:

	void insert(int);
	int find(int);
	void del(int);
	void iterate(void);
};

void Map::insert(int key)
{
	tree.insert(key);
}
int Map::find(int key)
{
	return traverse(tree.getRoot(),key);
}
void Map::del(int key)
{
	mydel(tree.getRoot(),key);
}
void Map::iterate()
{
	iter(tree.getRoot());
	cout<<endl;
}

int main()
{
	Map mymap;

	int n;
	while(cin>>n)
	{
		mymap.insert(n);
	}
	mymap.del(2);
	cout<<mymap.find(45345)<<endl;

	mymap.iterate();

	return 0;
}