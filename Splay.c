#include <stdio.h>
#include <stdlib.h>


typedef struct SplayNode {
  int key;
  struct SplayNode *left;
  struct SplayNode *right;
} SplayNode;

typedef SplayNode* SplayNodePtr;

// Function prototypes for the splay tree operations
void insert(SplayNodePtr *root, int key);
SplayNodePtr newNode(int key);
SplayNodePtr search(SplayNodePtr root, int key);
SplayNodePtr leftRotate(SplayNodePtr node);
SplayNodePtr rightRotate(SplayNodePtr node);
void splay(SplayNodePtr *root, int key);
int max(int a, int b);
SplayNodePtr findMax(SplayNodePtr root);
SplayNodePtr findMin(SplayNodePtr root);
void preOrder(SplayNodePtr root);


int main(){
	
	SplayNodePtr root = NULL;
	
	
	root = newNode(6);
	root->right = newNode(7);
	root->right->right = newNode(8);
	
	splay(&root,8);
	
	/*
	insert(&root,25);
	insert(&root,12);
	insert(&root,17);
	insert(&root,27);
	insert(&root,53);
	insert(&root,65);
	insert(&root,8);
	insert(&root,19);
	*/
	
	
	
	preOrder(root);
	
	return 0;
}

void insert(SplayNodePtr *root, int key) {

  if (*root == NULL) {
    *root = newNode(key);
    return;
  }

 
  if (key < (*root)->key) {
    insert(&((*root)->left), key);
  } else if(key > (*root)->key){
    insert(&((*root)->right), key);
  }else{
  	return;
  }

 
  splay(root, key);
}





// Splay the tree to bring the given node to the root
void splay(SplayNodePtr *root, int key) {
	if((*root)==NULL){
		return ;
	}
  while ((*root)->key != key) {
    
    //key rootun keyinden kuculse key soldaysa
    if(key < (*root)->key){
 			
 			if((*root)->left ==NULL){
 				return;
			 }else if((*root)->left->key == key){
			 	
			 	(*root) = rightRotate(*root);
			 	return;//burayi sonradan koydum
			 }
			 
			 //iki durum cgkar
			 
			 //rootun leftinin keyi ,keyden buyukse
			 if((*root)->left->key>key){
			 	
			 	//rootun solunun solu null ise
			 	if((*root)->left->left ==NULL){
			 		return ;
				 }	
			 		//rootun solunun solu null degil ise
			 		else {
			 			
			 			
			 			
			 			//rootun solunun solunun keyi, key e esitse
			 			//Zig zig right right rotations
			 			if((*root)->left->left->key==key){
			 				
			 				(*root) = rightRotate(*root);
			 				(*root) = rightRotate(*root);
			 				
						 }
						 
						 //rootun solunun solunun keyi, key e esit degilse
						 else{
						 	splay(&((*root)->left->left),key);
						 }
			 			
			 			
			 			
			 			
			 			
					 }
			 
			 
			 }
			 
			 
			 //rootun leftinin keyi ,keyden kucukse
			 else if((*root)->left->key <key){
			 	
			 	//rootun solunun sagi null ise
			 	if((*root)->left->right ==NULL){
			 		return ;
				 }
				 //rootun solunun saci null degil ise
				 else {
				 	
				 	
				 	
				 	
				 	
				 	//rootun solunun saginin keyi, key e esitse
			 			if((*root)->left->right->key==key){
			 				
			 				(*root)->left = leftRotate((*root)->left);
			 				*root = rightRotate(*root);
						 }
						 
						 //rootun solunun sagiinin keyi, key e esit degilse
						 else{
						 	splay(&((*root)->left->right) ,key);
						 }
				 	
				 	
				 	
				 	
				 	
				 }
				 
				 
			 }
			 
 			
 			
		 }//ilk durum bitti
		 //key rootun keyinden buyukse key sagdaysa
		 else if(key > (*root)->key){
 			//rootun sagi nulsa
 			if((*root)->right ==NULL){
 				return;
			 }//rootun saginin keyi keye esitse
			 else if((*root)->right->key == key){
			 	
			 	(*root) = leftRotate(*root);
			 	return;//burayi sonradan koydum
			 }
			 
			 //iki durum cikar
			 
			 //rootun rightinin keyi ,keyden buyukse key solda
			 if((*root)->right->key>key){
			 	
			 	//rootun saginin solu null ise
			 	if((*root)->right->left ==NULL){
			 		return ;
				 }	
			 		//rootun saginin solu null degil ise
			 		else {
			 			
			 			
			 			
			 			//rootun saginin solunun keyi, key e esitse
			 			//Zig zag right left rotations
			 			if((*root)->left->left->key==key){
			 				
			 				(*root)->right = rightRotate((*root)->right);
			 				(*root) = leftRotate(*root);
			 				
						 }
						 
						 //rootun saginin solunun keyi, key e esit degilse
						 else{
						 	splay(&((*root)->right->left),key);
						 }
			 			
			 			
			 			
			 			
			 			
					 }
			 
			 
			 }
			 
			 
			 //rootun rightinin keyi ,keyden kucukse key sagda
			 else if((*root)->right->key <key){
			 	
			 	//rootun saginin sagi null ise
			 	if((*root)->right->right ==NULL){
			 		return ;
				 }
				 //rootun saginin sagi null degil ise
				 else {
				 	
				 	
				 	
				 	
				 	
				 	//rootun saginin saginin keyi, key e esitse zig zig left left
			 			if((*root)->right->right->key==key){
			 				
			 				(*root) = leftRotate((*root));
			 				*root = leftRotate(*root);
						 }
						 
						 //rootun saginin sagiinin keyi, key e esit degilse
						 else{
						 	splay(&((*root)->right->right) ,key);
						 }
				 	
				 	
				 	
				 	
				 	
				 }
				 
				 
			 }
			 
 			
 			
		 }
    
  }//while end
  
  
}





SplayNodePtr rightRotate(SplayNodePtr a)
{
    SplayNodePtr b = a->left;
    SplayNodePtr c = b->right;

    b->right = a;
    a->left = c;

    return b;
}

SplayNodePtr leftRotate(SplayNodePtr a)
{
    SplayNodePtr b = a->right;
    SplayNodePtr c = b->left;

    b->left = a;
    a->right = c;

    return b;
}
//find the minimum key of the given tree and return it
SplayNodePtr findMin(SplayNodePtr root)
{
    SplayNodePtr current = root;
 
    while (current->left != NULL)
        current = current->left;
 
    return current;
}
//find the maximum key of the given tree and return it
SplayNodePtr findMax(SplayNodePtr root)
{
    SplayNodePtr current = root;
 
    while (current->right != NULL)
        current = current->right;
 
    return current;
}

int max(int a, int b)
{
    return (a > b)? a : b;
}

SplayNodePtr newNode(int key)
{
    SplayNodePtr node = (SplayNodePtr) malloc(sizeof(SplayNode));
    node->left = NULL;
    node->right = NULL;
    node->key = key;  
    return(node);
}

//print the tree in preorder traversal order
void preOrder(SplayNodePtr root)
{
    if(root != NULL)
    {
        printf("%d ", root->key);
        preOrder(root->left);
        preOrder(root->right);
    }
}