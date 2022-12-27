#include <stdio.h>
#include <stdlib.h>

// Ilker Keklik 150120074 balance tree de sikinti var gibi (hallettim)

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
AVLNodePtr findMax(AVLNodePtr root);
AVLNodePtr findMin(AVLNodePtr root);
int height(AVLNodePtr N);
int max(int a, int b);
AVLNodePtr newNode(int key);
AVLNodePtr rightRotate(AVLNodePtr y);
AVLNodePtr leftRotate(AVLNodePtr x);
int getBalance(AVLNodePtr N);
void balanceTree(AVLNodePtr *node,int key);
void insert(AVLNodePtr *node, int key);
void preOrder(AVLNodePtr root);
AVLNodePtr search(AVLNodePtr root, int key);
void deleteNode(AVLNodePtr *root, int key);
void insertFromFile(AVLNodePtr *root,FILE* file);
void preOrderToFile(AVLNodePtr root);
void writeTheOutputFile(AVLNodePtr root,int a);


int main()
{
	numberOfRotations = 0;
	numberOfComparisons = 0;
	readFilePtr1 = fopen("150120074_p2_input1.txt","r");
	readFilePtr2 = fopen("150120074_p2_input2.txt","r");

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
 
 	printf("AVL Tree");
	printf("n\nTest2\n");
	insertFromFile(&root,readFilePtr2);
	printf("\n");
	preOrder(root);
	printf("\n# of rotations: %d",numberOfRotations);
	printf("\n# of comparisons: %d",numberOfComparisons);
	printf("\n Cost: %d",(numberOfRotations+numberOfComparisons));
 
 writeTheOutputFile(root,2);
 /*
    printf("Inserting keys: 10, 20, 30, 40, 50, 25\n");
   
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);
    insert(&root, 25);
	
   insertFromFile(&root);
 
    printf("\nPreorder traversal of the tree: ");
    preOrder(root);
 
    printf("\n\nDeleting key 30 \n");
    deleteNode(&root, 30);
 
    printf("\nafter deletion 30: ");
    preOrder(root);
 
    printf("\n\nInserting keys: 5, 55, 35, 45, 15, 75\n");
    insert(&root, 5);
    insert(&root, 55);
    insert(&root, 35);
    insert(&root, 45);
    insert(&root, 15);
    insert(&root, 75);
 
    printf("\nPreorder traversal : ");
    preOrder(root);
 
    printf("\n\nDeleting key 55 \n");
    deleteNode(&root, 55);
 
    printf("\nPreorder traversal : ");
    preOrder(root);
 
    int key = 40;
    printf("\n\nSearching for key %d: ", key);
    AVLNodePtr result = search(root, key);
    if (result == NULL)
    {
        printf("Key not found \n");
    }
    else
    {
        printf("Key found \n");
    }
 
    printf("\nFinding minimum value: ");
    AVLNodePtr min = findMin(root);
    printf("%d\n", min->key);
 
    printf("Finding maximum value: ");
    AVLNodePtr max = findMax(root);
    printf("%d\n", max->key);
 
 
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
			printf("%d inserted\n",key);
			
		}
		
		
		
		
		
		
}



//search functions searchs the given value in the tree whose root is given
AVLNodePtr search(AVLNodePtr root, int key)
{
    if (root == NULL || root->key == key){
    numberOfComparisons++;
	return root;	
	}
       
       
    
    if (root->key < key){
    	numberOfComparisons++;
       return search(root->right, key);
	}
 	numberOfComparisons++;
    return search(root->left, key);
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

    // Left Left 
    if (balance > 1 && (*node)->left->key>key )
        *node = rightRotate(*node);

    // Right Right 
    else if (balance < -1 && (*node)->right->key<key )
        *node = leftRotate(*node);

    // Left Right 
    else if (balance > 1 && (*node)->left->key < key  )
    {
        (*node)->left =  leftRotate((*node)->left);
        *node = rightRotate(*node);
    }

    // Right Left 
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
        printf("%d eklendi ",key);
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




//inorder predecessor
//deletes the given key from the tree if it is exist
void deleteNode(AVLNodePtr *root, int key)
{
    if (*root == NULL){
    	numberOfComparisons++;
        return;//
	}
 
    
    else if (key < (*root)->key){
    	numberOfComparisons++;
        deleteNode(&(*root)->left, key);
	}
 

    else if (key > (*root)->key){
    	numberOfComparisons++;
        deleteNode(&(*root)->right, key);
	}
 
    //key is the root's key or we found the key to be deleted
    else
    {//
   
       	//case 1 : no child
       	
		if((*root)->left==NULL && (*root)->right==NULL) {
			free((*root));
			(*root)= NULL;
			
		}
		
		//case 2 : One child
		
		else if((*root)->left==NULL){
			AVLNodePtr temp = *root;
			*root = (*root)->right;
			free(temp);
			temp=NULL;
			
		}
		else if((*root)->right==NULL){
			AVLNodePtr temp = *root;
			(*root) = (*root)->left;
			free(temp);
			temp=NULL;
			
		}
	    else
        {//
            //2 children case swap with greatest in the left subtree
           	//finding and deleting the inorder predecessor recursively
            AVLNodePtr temp = findMax((*root)->left);
 
            
            (*root)->key = temp->key;
 
            deleteNode(&(*root)->left, temp->key);
        }
    }
 
    // if there is nothing after the deletion no need to calculate height and balance the tree
    if (*root == NULL)
      return;
      //update height all the accessed elements while deleting
    (*root)->height = 1 + max(height((*root)->left), height((*root)->right));
 
    // Balance the tree if it is necessary
    balanceTree(root,key);
}

//find the minimum key of the given tree and return it
AVLNodePtr findMin(AVLNodePtr root)
{
    AVLNodePtr current = root;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
//find the maximum key of the given tree and return it
AVLNodePtr findMax(AVLNodePtr root)
{
    AVLNodePtr current = root;
 
    while (current->right != NULL)
        current = current->right;
 
    return current;
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
