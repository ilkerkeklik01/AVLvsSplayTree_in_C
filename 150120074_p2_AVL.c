#include <stdio.h>
#include <stdlib.h>

// Ilker Keklik 

FILE *readFilePtr1; 
FILE *readFilePtr2; 

FILE *writeFilePtr; 

int numberOfRotations;
int numberOfComparisons;

typedef struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef AVLNode* AVLNodePtr;

typedef enum boolean{
	true=1
}boolean;

//Prototypes

int height(AVLNodePtr N);
int max(int a, int b);
AVLNodePtr newNode(int key);
AVLNodePtr rightRotate(AVLNodePtr y);
AVLNodePtr leftRotate(AVLNodePtr x);
int getBalance(AVLNodePtr N);
void balanceTree(AVLNodePtr *node,int key);
void insert(AVLNodePtr *node, int key);
void preOrder(AVLNodePtr root);


void insertFromFile(AVLNodePtr *root,FILE* file);
void preOrderToFile(AVLNodePtr root);
void writeTheOutputFile(AVLNodePtr root,int a);


int searchFactor;
AVLNodePtr search(AVLNodePtr root, int key) {
  searchFactor++;
  if (root == NULL) {
    printf("\n%d cannot found\n",key);
	return NULL;
  }else if(root->key==key){
  	
  	printf("\n%d found\n",key);
  	return root;
  }
  else if(root->key>key) return search(root->left,key);
  else if(root->key<key) return search(root->right,key);
 
 
}




int main()
{

	searchFactor=0;
	numberOfRotations = 0;
	numberOfComparisons = 0;
	readFilePtr1 = fopen("input1.txt","r");
	readFilePtr2 = fopen("input2.txt","r");

	writeFilePtr = fopen("150120074_p2_output.txt","a");
	
	
    AVLNodePtr root = NULL;

	fprintf(writeFilePtr,"\nAVL TREE\n");
	printf("AVL Tree");
	printf("\nTest1\n");
	insertFromFile(&root,readFilePtr1);
	printf("\n");
	preOrder(root);
	printf("\n# of rotations: %d",numberOfRotations);
	printf("\n# of comparisons: %d",numberOfComparisons);
	printf("\n Cost: %d",(numberOfRotations+numberOfComparisons));
	
	writeTheOutputFile(root,1);
	
	numberOfRotations=0;
	numberOfComparisons=0;
	root=NULL;
 
 	
	printf("\nTest2\n");
	insertFromFile(&root,readFilePtr2);
	printf("\n");
	preOrder(root);
	printf("\n# of rotations: %d",numberOfRotations);
	printf("\n# of comparisons: %d",numberOfComparisons);
	printf("\n Cost: %d",(numberOfRotations+numberOfComparisons));
 
 writeTheOutputFile(root,2);
 
 
 /*
 //search 1 
 printf("\nsearch test 1\n");
 search(root,78);
 search(root,87);
 search(root,4);
 search(root,26);
 search(root,47);
 search(root,50);
 search(root,50);
 search(root,50);
 search(root,50);
 search(root,50);
 printf("Search factor: %d",searchFactor);
 searchFactor=0;
 //search2 
 printf("\nsearch test 2\n");
 search(root,13);
 search(root,96);
 search(root,2);
 search(root,45);
 search(root,91);
 search(root,77);
 search(root,14);
 search(root,50);
 search(root,17);
 search(root,49);
 printf("Search factor: %d",searchFactor);
  searchFactor=0;
 //search3
 printf("\nsearch test 3\n");
 search(root,52);
 search(root,99);
 search(root,41);
 search(root,6);
 search(root,55);
 search(root,100);
 search(root,101);
 search(root,102);
 search(root,103);
 search(root,104);
 printf("Search factor: %d",searchFactor);
 */
 
 fclose(readFilePtr1);
 fclose(readFilePtr2);
 fclose(writeFilePtr);
 
 
    return 0;
}
void writeTheOutputFile(AVLNodePtr root,int a){
	
	if(writeFilePtr==NULL){
		printf("Error while writing file");
	return ;
	}
	
	
	fprintf(writeFilePtr,"Test %d\n",a);
	preOrderToFile(root);
	
    fprintf(writeFilePtr,"\n");
    
    	fprintf(writeFilePtr,"\n# of rotations: %d",numberOfRotations);
	fprintf(writeFilePtr,"\n# of comparisons: %d",numberOfComparisons);
	fprintf(writeFilePtr,"\n Cost: %d\n",(numberOfRotations+numberOfComparisons));

	
	
}
void preOrderToFile(AVLNodePtr root){
	
	if(root!=NULL){
		fprintf(writeFilePtr,"%d ", root->key);
		preOrderToFile(root->left);
		preOrderToFile(root->right);
	}
	
}

void insertFromFile(AVLNodePtr *root,FILE* file){
		if(file == NULL){
			printf("Error while reading file!");
			return;
		}
		
		int key;
		
		while(true){
			 boolean result = fscanf(file,"%d",&key);
			 
			if(result!=true){
				
				break;
			}
			
			insert(root,key);
			
			
		}
		
		
		
		
		
		
}

//returns height of the tree whose root is given
int height(AVLNodePtr N)
{
    if (N == NULL)
        return 0;
    return N->height;
}

//max value btw two integers
int max(int a, int b)
{
    return (a > b)? a : b;
}

//This functions creates AVLNode pointer with the given value and also returns it
AVLNodePtr newNode(int key)
{
    AVLNodePtr node = (AVLNodePtr) malloc(sizeof(AVLNode));
    node->left = NULL;
    node->right = NULL;
    node->key = key;
    node->height = 1;  
    return(node);
}

//Right rotation of AVL Tree.This function accepts a as a root and it changes the root with b.
AVLNodePtr rightRotate(AVLNodePtr a)
{
    AVLNodePtr b = a->left;
    AVLNodePtr c = b->right;

    b->right = a;
    a->left = c;
	numberOfRotations++;
    a->height = max(height(a->left), height(a->right))+1;
    b->height = max(height(b->left), height(b->right))+1;

    return b;
}

//Left rotation of AVL Tree.This function accepts a as a root and it changes the root with b.
AVLNodePtr leftRotate(AVLNodePtr a)
{
    AVLNodePtr b = a->right;
    AVLNodePtr c = b->left;

    b->left = a;
    a->right = c;
    a->height = max(height(a->left), height(a->right))+1;
    b->height = max(height(b->left), height(b->right))+1;
numberOfRotations++;
    return b;
}

// 	it returns height difference of left and right subtree of a given node
int getDf(AVLNodePtr node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Balance the tree if necessary
void balanceTree(AVLNodePtr *node,int key)
{
	
    int balance = getDf(*node);

    // Left heavy right rotation
    if (balance > 1 && (*node)->left->key>key )
        *node = rightRotate(*node);

    // Right heavy left rotation
    else if (balance < -1 && (*node)->right->key<key )
        *node = leftRotate(*node);

    // Left subtree Right heacy Left-Right rotation
    else if (balance > 1 && (*node)->left->key < key  )
    {
        (*node)->left =  leftRotate((*node)->left);
        *node = rightRotate(*node);
    }

    // Right subtree left heacy Right-Left rotation
    else if (balance < -1 && (*node)->right->key > key  )
    {
        (*node)->right = rightRotate((*node)->right);
        *node = leftRotate(*node);
    }
}






//this function insert a key unless Tree have the given key and then balances the tree if it is needed
void insert(AVLNodePtr *node, int key)
{
   
    if (*node == NULL)
    {	
//	numberOfComparisons++;					//buraya numberOfComparison++ koymicam sanirim
        *node = newNode(key);
       
        return;
    }

    if (key < (*node)->key){
    	numberOfComparisons++;
    	insert(&(*node)->left, key);
	}
        
        
        
    else if (key > (*node)->key){
    	numberOfComparisons++;
    	
        insert(&(*node)->right, key);
	}
    
	
	else {
		numberOfComparisons++;
        return; 
	}

    
    (*node)->height = 1 + max(height((*node)->right),height((*node)->left));

    // Balance the tree 
    balanceTree(node,key);
}





//print the tree in preorder traversal order
void preOrder(AVLNodePtr root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}
