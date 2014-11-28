typedef int nodeType;
#define queuesize 100
enum Bfactor {lhigher, ehigher, rhigher};
enum {success, overflow};
struct AVLnode{
	nodeType data;
	AVLnode *left;
	AVLnode *right;
	Bfactor balance;
};

typedef struct
{
	int front, rear;
	AVLnode * data[queuesize]; // the element of queue is the pointer to AVLnode
	int count;
} cirqueue; //define a circle queue


class AVLTree
{
private:
	AVLnode *root;
	void recursivePreorder(AVLnode *x);
	void recursiveInorder(AVLnode *x);
	void recursivePostorder(AVLnode *x);
	void levelOrder(AVLnode *x);
	int searchDelete(AVLnode *subRoot, const nodeType target);
	int removeRoot(AVLnode *subRoot);
	AVLnode *searchNode(AVLnode *&subRoot, const nodeType newData, bool &taller);
	int searchInsert(AVLnode *&subRoot, const nodeType newData, bool &taller);
	int avlInsert(AVLnode *&subRoot, const nodeType newData, bool &taller);
	
	void leftBalance(AVLnode *&subRoot);
	void rightBalance(AVLnode *&subRoot);
	
	void rotateLeft(AVLnode *&subRoot);
	void rotateRight(AVLnode *&subRoot);
	
public:
	AVLTree();
	~AVLTree();
	AVLTree(const AVLTree &original);
	AVLTree &operator=(const AVLTree &original);
	
	bool empty() const;
	void clear();
	int height() const;
	int size() const;
	int insert(const nodeType x);
	int remove(const nodeType x);
	int search(const nodeType x) const;
	//invoke the private methods above
	void preorder();
	void inorder();
	void postorder();
	void levelorder();
};

