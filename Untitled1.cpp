#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct node{
 int partnum;
 char name[100];
 struct node *left,*right;
 int ht;
};

int getHeight(struct node *curr){
 if(curr == NULL) return 0;
 return curr->ht;
}

int getBF(struct node *curr){
 if(curr == NULL) return 0;
 return getHeight(curr->left) - getHeight(curr->right);
}

int getMax(int a, int b){
 if(a > b) return a;
 else return b;
}

struct node *rightRotate(struct node *C){

 struct node *B = C->left;
 struct node *x = B->right;
 

 B->right = C;
 C->left = x;
 
 C->ht = getMax(getHeight(C->left), getHeight(C->right)) + 1;
 B->ht = getMax(getHeight(B->left), getHeight(B->right)) + 1;
 
 return B;
}

struct node *leftRotate(struct node *A){

 struct node *B = A->right;
 struct node *y = B->left;

 B->left = A;
 A->right = y;
 
 A->ht = getMax(getHeight(A->left), getHeight(A->left)) + 1;
 B->ht = getMax(getHeight(B->left), getHeight(B->right)) + 1;
 
 return B;
}

struct node *push(struct node *curr, int pt, char descrip[]){
 if(curr == NULL){
  struct node *temp = (struct node *) malloc(sizeof(struct node));
  temp->partnum = pt;
  temp->ht = 1;
  strcpy(temp->name,descrip);
  temp->left = temp->right = NULL;
  
  return temp;
 }
 else if(pt < curr->partnum){
  curr->left = push(curr->left, pt, descrip);
 }
 else if(pt > curr->partnum){
  curr->right = push(curr->right, pt, descrip);
 }
 
 curr->ht = getMax(getHeight(curr->left), getHeight(curr->right)) + 1;
 
 int BF = getBF(curr);
 
 if(BF > 1 && pt < curr->left->partnum){
  return rightRotate(curr);
 }
 else if(BF < -1 && pt > curr->right->partnum){
  return leftRotate(curr);
 }
 
 else if(BF > 1 && pt > curr->left->partnum){
  curr->left = leftRotate(curr->left);
  return rightRotate(curr);
 }

 else if(BF < -1 && pt < curr->right->partnum){
  curr->right = rightRotate(curr->right);
  return leftRotate(curr);
 } 
 
 return curr;
}

void inOrder(struct node *curr){
 if(curr == NULL) return;
 inOrder(curr->left);
 
 printf("%d %s Height=%d\n", curr->partnum, curr->name, curr->ht);
 
 inOrder(curr->right); 
}

void search(struct node *curr, int target){
 if(curr == NULL) return;
 search(curr->left,target);
 if(curr->partnum == target){
  printf("found\n");
  return;
 }
 search(curr->right,target);
}

int main(){
 int pil,partnum,target;
 char desc[100];
 struct node *root=NULL;
 while(pil!=5){
  printf("List of Items in Store\n");
  printf("======================\n");
  printf("1>Insert\n");
  printf("2>Print\n");
  printf("3>Search\n");
  printf("4>Quit\n");
  printf("\n Enter Your Choice: ");
  scanf("%d", &pil);
  
  switch(pil){
   case 1:
    printf("Enter Partnum: ");
    scanf("%d", &partnum); getchar();
    printf("Enter Description: ");
    scanf("%[^\n]", desc); getchar();
    
    root = push(root, partnum, desc);
    
    break;
    
   case 2:
    inOrder(root);
    break; 
   case 3:
    printf("Enter a partnum: ");
    scanf("%d", &target);
    search(root,target);
    break; 
  }
 }
 
 return 0;
}
