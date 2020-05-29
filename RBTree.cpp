#include <bits/stdc++.h>
using namespace std;
enum Color { RED, BLACK };
//structure of each node of a Red-Black Tree
struct node
{
	int data;
	Color color;
	bool leftChild;
	node *left,*right,*parent;
}*notify;

bool checkleft;

node* newNode(int n)
{
	node *temp = new node;
	temp->data = n;
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

	node* getRoot() {
		return root;
	}
	void insert(int);
	void check(node *);
	void rotate(node *,bool);
	void remove(int);
	void removeExt(node *);
};

Color getColor(node* temp)
{
	if(temp)
		return temp->color;
	return BLACK;
}

node *LLRotation(node *temp, bool inserted)
{
	bool leftChild;
	node *parent = temp->parent;
	node *grandparent = parent->parent;

	node *temp3;
	//rotation
	temp3 = parent->right;
	parent->right = grandparent;
	grandparent->parent = parent;
	grandparent->left = temp3;
	if(temp3)
		temp3->parent = grandparent;

	//color change
	if(inserted)
		parent->color = BLACK, grandparent->color = RED;
	else
		temp->color = BLACK;

	//adjust left right value of nodes
	leftChild = grandparent->leftChild;
	grandparent->leftChild = false;
	parent->leftChild = leftChild;

	return parent;
}

node *LRRotation(node *temp, bool inserted)
{
	node *parent = temp->parent;
	node *grandparent = parent->parent;
	bool leftChild;
	node *temp2,*temp3;
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
	if(inserted)
		grandparent->color = RED, temp->color = BLACK;
	else
		temp->color = BLACK;

	//adjust left right value of nodes
	leftChild = grandparent->leftChild;
	grandparent->leftChild = false;
	temp->leftChild = leftChild;

	return temp;
}

node *RRRotation(node *temp, bool inserted)
{
	bool leftChild;
	node *parent = temp->parent;
	node *grandparent = parent->parent;

	node *temp3;
	//rotation
	temp3 = parent->left;
	parent->left = grandparent;
	grandparent->parent = parent;
	grandparent->right = temp3;
	if(temp3)
		temp3->parent = grandparent;

	//color change
	if(inserted)
		parent->color = BLACK, grandparent->color = RED;
	else
		temp->color = BLACK;

	//adjust left right value of nodes
	leftChild = grandparent->leftChild;
	grandparent->leftChild = true;
	parent->leftChild = leftChild;

	return parent;
}

node *RLRotation(node *temp, bool inserted)
{
	bool leftChild;
	node *parent = temp->parent;
	node *grandparent = parent->parent;
	node *temp3,*temp4;
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
	if(inserted)
		grandparent->color = RED,temp->color = BLACK;
	else
		temp->color = BLACK;

	//adjust left right value of nodes
	leftChild = grandparent->leftChild;
	grandparent->leftChild = true;
	temp->leftChild = leftChild;

	return temp;
}

void RBTree::rotate(node* temp, bool inserted = true)
{
	node *top, *final, *grandparent = temp->parent->parent;
	bool leftChild = grandparent->leftChild;
	int c=0;

	if(temp->parent->leftChild)
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

			final = LLRotation(temp,inserted);
			break;

		// Left Right case
		case 1:

			final = LRRotation(temp,inserted);
			break;

		// Right Right case
		case 2:

			final = RRRotation(temp,inserted);
			break;

		// Right Left case
		case 3:

			final = RLRotation(temp,inserted);
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
		if(n <= temp->data)
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
		else
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
	}
	check(temp);
}

node *deleteNode(node *root, int key)
{
	if(!root)
		return NULL;

	node *temp;
	if(key < root->data)
	{
		temp = deleteNode(root->left, key);
		root->left = temp;
		if(temp)
			temp->parent = root;
	}

	else if(key > root->data)
	{
		temp = deleteNode(root->right, key);
		root->right = temp;
		if(temp)
			temp->parent = root;
	}

	else
	{
		int color;

		if(!root->left)
		{
			color = (getColor(root) == BLACK);
			color += (getColor(root->right) == BLACK);

			if(color == 2)
				notify = root->parent, checkleft = root->leftChild;

			node *temp = root->right;
			free(root);

			if(temp)
				temp->color = BLACK;

			return temp;
		}
		else if(!root->right)
		{
			color = (getColor(root) == BLACK);
			color += (getColor(root->left) == BLACK);

			if(color == 2)
				notify = root->parent, checkleft = root->leftChild;
			
			node *temp = root->left;
			free(root);
			
			if(temp)
				temp->color = BLACK;

			return temp;
		}
		node *temp = root->right;
		while(temp->left)
			temp = temp->left;

		root->data = temp->data;
		temp = deleteNode(root->right, temp->data);
		root->right = temp;
		if(temp)
			temp->parent = root;
	}
	return root;
}

node *LRotate(node *parent)
{
	node *sibling = parent->left;
	node *temp = sibling->right;
	bool leftChild;

	//rotation
	sibling->right = parent;
	parent->left = temp;

	parent->parent = sibling;
	if(temp)
		temp->parent = parent;

	//color change
	sibling->color = BLACK;
	parent->color = RED;

	//adjust left right value of nodes
	leftChild = parent->leftChild;
	parent->leftChild = false;
	sibling->leftChild = leftChild;

	return sibling;
}

node *RRotate(node *parent)
{
	node *sibling = parent->right;
	node *temp = sibling->left;
	bool leftChild;

	//rotation
	sibling->left = parent;
	parent->right = temp;

	parent->parent = sibling;
	if(temp)
		temp->parent = parent;

	//color change
	sibling->color = BLACK;
	parent->color = RED;

	//adjust left right value of nodes
	leftChild = parent->leftChild;
	parent->leftChild = true;
	sibling->leftChild = leftChild;

	return sibling;
}

void RBTree::removeExt(node *notify)
{
	if(notify == NULL)
		return;

	node *parent,*sibling,*temp;
	int color;

	parent = notify;
	if(checkleft)
		sibling = parent->right;
	else
		sibling = parent->left;
	
	if(getColor(sibling) == BLACK)
	{
		if(sibling)
			color = getColor(sibling->left) + getColor(sibling->right);
		else
			color = 2;

		if(color != 2)
		{
			if(getColor(sibling->right) == RED)
				rotate(sibling->right,false);
			else
				rotate(sibling->left,false);
		}
		//not tested yet
		else
		{
			sibling->color = RED;
			if(getColor(parent) == RED)
			{
				parent->color = BLACK;
				return;
			}
			checkleft = parent->leftChild;
			removeExt(parent->parent);
		}
	}
	else
	{
		temp = parent->parent;

		if(sibling->leftChild)
			parent = LRotate(parent);
		else
			parent = RRotate(parent);

		checkleft = parent->leftChild;
		if(temp)
		{
			if(checkleft)
				temp->left = parent;
			else
				temp->right = parent;
			parent->parent = temp;
			removeExt(temp);
		}
		else
		{
			parent->parent= NULL;
			root = parent;
			return;
		}
	}
}

void RBTree::remove(int key)
{
	notify = NULL;
	root = deleteNode(root,key);

	removeExt(notify);
}
/*
void traverse(node *temp)
{
	if(!temp)
		return;

	traverse(temp->left);
	cout<<temp->data<<":";
	if(temp->color == BLACK)
		cout<<"B ";
	else
		cout<<"R ";
	traverse(temp->right);
}
*/
int main()
{
	RBTree tree;

	int n;
	while(cin>>n)
	{
		tree.insert(n);
	}

	//traverse(tree.getRoot());
	
	tree.remove(10);

	
	return 0;
}
