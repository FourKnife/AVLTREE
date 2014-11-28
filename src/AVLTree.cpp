#include<iostream>
#include<vector>
#include"AVLTree.h"
#include<fstream>
using namespace std;
ofstream out("res.txt");

AVLTree::AVLTree()
{
	root = NULL; // root is initialized
}

AVLTree::~AVLTree()
{
	
}
int AVLTree::insert(const nodeType newData)
{
	//if newData is in AVL tree, then return false, else insert it into AVL tree and keep the property of AVL unchanged
	bool taller; // indicates whether the height of tree is increased or not
	if(root == NULL)
	{
		root = new AVLnode;
		root->data = newData;
		root->balance = ehigher;
		root->left = root->right = NULL;
		taller = true;
		return success;
	}
	 
	// if the root is not NULL then invoke this method below
	else
		return avlInsert(root, newData, taller);
}

int AVLTree::avlInsert(AVLnode *&subRoot, const nodeType newData, bool &taller)
{
	int result = success;
	//terminal 
	if(subRoot == NULL)
	{
		subRoot = new AVLnode;
		subRoot->data = newData;
		subRoot->balance = ehigher;
		subRoot->left = subRoot->right = NULL;
		taller = true;
	}
	
	// if there is the same number then fail to insert
	else if(subRoot->data == newData)
	{
		result = overflow;
		taller = false;
	}
	else if(subRoot->data > newData) // insert into the left tree
	{
		result = avlInsert(subRoot->left, newData,taller);
		if(taller == true)
			switch(subRoot->balance)  
			{
				case lhigher:  // insert then the left sub tree is higher than right by 2 
					leftBalance(subRoot); // 左子树双倍不平衡
					taller = false;
					break;
				case ehigher:
					subRoot->balance = ehigher;
					break;
				case rhigher:
					subRoot->balance = ehigher;
					taller = false;
					break;
			}
	}
	else 
	{
		result = avlInsert(subRoot->right, newData, taller);
		if(taller == true )
			switch(subRoot->balance)
			{
				case lhigher:
					subRoot->balance = ehigher;
					taller = false;
					break;
				case ehigher:
					subRoot->balance = rhigher;
					break;
				case rhigher:
					rightBalance(subRoot);
					taller = false;
					break;
			}
	}
	return result;
}


/**
	leftRotate && rightRotate
*/

void AVLTree::rotateLeft(AVLnode *&subRoot)
{
	//pre: right sub tree is not NULL
	//post: fill in the requirement of AVL
	if(subRoot==NULL || subRoot->right == NULL)
		cout<<"Warning, cannot rotate left! "<<endl;
	else 
	{
		AVLnode *right_tree = subRoot->right;
		subRoot->right = right_tree->left;
		right_tree->left = subRoot;
		subRoot = right_tree;
	}
}

void AVLTree::rotateRight(AVLnode *&subRoot)
{
	//pre: the left sub tree cannot be NULL
	//post: fill in the requirement of AVL
	if(subRoot == NULL || subRoot->left == NULL)
		cout<<"Warning, cannot rotate right! "<<endl;
	else
	{
		AVLnode *left_tree = subRoot->left;
		subRoot->left = left_tree->right;
		left_tree->right = subRoot;
		subRoot = left_tree;
	}
}

void AVLTree::leftBalance(AVLnode *&subRoot)
{
	//pre: subTree is the root of AVLTree, and it's left sub tree is double unbalanced
	//post: AVL property is repaired
	AVLnode *left_tree = subRoot->left;
	AVLnode *temp = subRoot;
	switch(left_tree->balance)
	{
		case rhigher: // rotateRight once 
			subRoot->balance = ehigher;
			left_tree->balance = ehigher;
			rotateRight(subRoot);
			break;
		case ehigher:
			cout<<"Warning!: cannot go for left balance"<<endl;
		case lhigher: // double rotate	
			AVLnode *sub_tree = left_tree->right;
			if(sub_tree == NULL)
				rotateRight(temp);
			else
			{
				switch(sub_tree->balance)
				{
					case ehigher:
						cout<<"Warning!: cannot go for left balance"<<endl;
					case lhigher:
						subRoot->balance = ehigher;
						left_tree->balance =rhigher;
						break;
					case rhigher:
						subRoot->balance = lhigher;
						left_tree->balance = ehigher;
						break;
				}
				sub_tree->balance = ehigher;
				rotateLeft(left_tree);
				rotateRight(subRoot);
				break;
			}
	}
}


void AVLTree::rightBalance(AVLnode *&subRoot)
{
	//pre: subTree is the root of AVLTree, and it's right sub tree is double unbalanced
	//post: AVL property is repaired
	AVLnode *right_tree = subRoot->right;
	AVLnode *temp = subRoot;
	switch(right_tree->balance)
	{
		case rhigher: // rotateLeft once 
			subRoot->balance = ehigher;
			right_tree->balance = ehigher;
			rotateLeft(subRoot);
			break;
		case ehigher:
			cout<<"Warning!: cannot go for right balance"<<endl;
		case lhigher: // double rotate	
			AVLnode *sub_tree = right_tree->left;
			if(sub_tree == NULL)
				rotateLeft(temp);
			else
			{
				switch(sub_tree->balance)
				{
					case ehigher:
						cout<<"Warning!: cannot go for right balance"<<endl;
					case lhigher:
						subRoot->balance = ehigher;
						right_tree->balance =rhigher;
						break;
					case rhigher:
						subRoot->balance = lhigher;
						right_tree->balance = ehigher;
						break;
				}
				sub_tree->balance = ehigher;
				rotateRight(right_tree);
				rotateLeft(subRoot);
				break;
			}
	}
}

void AVLTree::preorder()
{
	recursivePreorder(root);
}
void AVLTree::recursivePreorder(AVLnode *x)
{
	if(x!=NULL)
	{
		cout << x->data << " ";
		out<< x->data << " ";
		recursivePreorder(x->left);
		recursivePreorder(x->right);
	}
}

void AVLTree::inorder()
{
	recursiveInorder(root);
}

void AVLTree::recursiveInorder(AVLnode *x)
{
	if(x != NULL)
	{
		recursiveInorder(x -> left);
		cout<< x-> data << " ";
		out<< x->data << " ";
		recursiveInorder(x -> right);
	}
}

void AVLTree::postorder()
{
	recursivePostorder(root);
}

void AVLTree::recursivePostorder(AVLnode *x)
{
	if(x != NULL)
	{
		recursivePostorder(x->left);
		recursivePostorder(x->right);
		cout<< x->data <<" ";
		out<< x-> data <<" ";
	}
}
void AVLTree::levelorder()
{
	levelOrder(root);
}
void AVLTree::levelOrder(AVLnode *t)
{
	cirqueue *q;
	AVLnode *p;
	q = new cirqueue; //申请循环队列空间
	q->rear = q->front = q->count = 0; //初始化
	q->data[q->rear] = t;
	q->count++;
	q->rear = (q->rear + 1) % queuesize; // 根结点入队
	while(q->count) // 队列不为空时
		if(q->data[q->front]) // 队首元素不为空指针时
		{
			p = q->data[q->front]; //取队首元素 *p
			cout<<p->data << " ";
			out<<p->data << " ";
			q->front = (q->front + 1) % queuesize;
			q->count--; //队首元素出队
			if(q->count == queuesize)
				cout<<"error, queue is full";
			else
			{
				q->count++;
				q->data[q->rear] = p->left;
				q->rear = (q->rear + 1) % queuesize;
			}
			if(q->count == queuesize)
				cout<<"error, queue is full";
			else
			{
				q->count++;
				q->data[q->rear] = p->right;
				q->rear = (q->rear + 1) % queuesize;
			}
		}
		else 
		{
			q->front = (q->front + 1) %queuesize;
			q->count--;
		}

}

