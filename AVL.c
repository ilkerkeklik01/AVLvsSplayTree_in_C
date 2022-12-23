#include <stdio.h>
#include <stdlib.h>

// Ilker Keklik 150120074 balance tree de sikinti var gibi (hallettim)
typedef struct AVLNode
{
    int key;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
} AVLNode;

typedef AVLNode* AVLNodePtr;

//Prototypes
AVLNodePtr findMax(AVLNodePtr root);
AVLNodePtr findMin(AVLNodePtr root);
int height(AVLNodePtr N);
int max(int a, int b);
AVLNodePtr newNode(int key);
AVLNodePtr rightRotate(AVLNodePtr y);
AVLNodePtr leftRotate(AVLNodePtr x);
int getBalance(AVLNodePtr N);
void balanceTree(AVLNodePtr *node);
void insert(AVLNodePtr *node, int key);
void preOrder(AVLNodePtr root);
AVLNodePtr search(AVLNodePtr root, int key);
void deleteNode(AVLNodePtr *root, int key);


int main()
{
    AVLNodePtr root = NULL;
	/*insert(&root, 10);
    insert(&root, 15);
    insert(&root, 9);
    insert(&root, 20);
    insert(&root, 8);
    insert(&root, 16);
    preOrder(root);*/
 
 
    printf("Inserting keys: 10, 20, 30, 40, 50, 25\n");
    insert(&root, 10);
    insert(&root, 20);
    insert(&root, 30);
    insert(&root, 40);
    insert(&root, 50);
    insert(&root, 25);
 
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
 
 
 
    return 0;
}






//search functions searchs the given value in the tree whose root is given
AVLNodePtr search(AVLNodePtr root, int key)
{
    if (root == NULL || root->key == key)
       return root;
    
    if (root->key < key)
       return search(root->right, key);
 
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
void balanceTree(AVLNodePtr *node)
{
    // Get the balance factor of this ancestor
    int balance = getDf(*node);
    // If this node becomes unbalanced, then
    // there are 4 cases

    // Left Left Case
    if (balance > 1 && getDf((*node)->left) >= 0)
        *node = rightRotate(*node);

    // Right Right Case
    if (balance < -1 && getDf((*node)->right) <= 0)
        *node = leftRotate(*node);

    // Left Right Case
    if (balance > 1 && getDf((*node)->left) < 0)
    {
        (*node)->left =  leftRotate((*node)->left);
        *node = rightRotate(*node);
    }

    // Right Left Case
    if (balance < -1 && getDf((*node)->right) > 0)
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
        *node = newNode(key);
        return;
    }

    if (key < (*node)->key)
        insert(&(*node)->left, key);
    else if (key > (*node)->key)
        insert(&(*node)->right, key);
    else
        return; 

    
    (*node)->height = 1 + max(height((*node)->left),
                              height((*node)->right));

    // Balance the tree 
    balanceTree(node);
}



//inorder successor
/*void deleteNode(AVLNodePtr *root, int key)
{
    // Step 1: Perform standard BST delete
    if (*root == NULL)
        return;
 
    // If the key to be deleted is smaller than the
    // root's key, then it lies in left subtree
    if (key < (*root)->key)
        deleteNode(&(*root)->left, key);
 
    // If the key to be deleted is greater than the
    // root's key, then it lies in right subtree
    else if (key > (*root)->key)
        deleteNode(&(*root)->right, key);
 
    // if key is same as root's key, then This is
    // the node to be deleted
    else
    {
        // node with only one child or no child
        if (((*root)->left == NULL) || ((*root)->right == NULL))
        {
            AVLNodePtr temp = (*root)->left ? (*root)->left : (*root)->right;
 
            // No child case
            if (temp == NULL)
            {
                temp = *root;
                *root = NULL;
            }
            else // One child case
            *(*root) = *temp; // Copy the contents of the non-empty child
 
            free(temp);
        }
        else
        {
            // node with two children: Get the inorder successor
            // (smallest in the right subtree)
            AVLNodePtr temp = findMin((*root)->right);
 
            // Copy the inorder successor's data to this node
            (*root)->key = temp->key;
 
            // Delete the inorder successor
            deleteNode(&(*root)->right, temp->key);
        }
    }
 
    
    if (*root == NULL)
      return;
 
    (*root)->height = 1 + max(height((*root)->left), height((*root)->right));
    
    balanceTree(root);
}*/

//inorder predecessor
//deletes the given key from the tree if it is exist
void deleteNode(AVLNodePtr *root, int key)
{
    if (*root == NULL)
        return;//
 
    
    else if (key < (*root)->key)
        deleteNode(&(*root)->left, key);
 

    else if (key > (*root)->key)
        deleteNode(&(*root)->right, key);
 
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
    balanceTree(root);
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
