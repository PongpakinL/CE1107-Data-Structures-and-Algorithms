#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    //printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    // printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    //printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    //printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode** root,char* prefix)
{
    BTNode** stack[SIZE];
    int stackPosition = 0;

    char *token = strtok(prefix, " ");
	while (token != NULL)
    {
        *root = malloc(sizeof(BTNode));
        (*root)->left = NULL;
        (*root)->right = NULL;
        if (isdigit(token[0])) 
        {
            (*root)->item = *token;
            if (stackPosition == 0) break;
            root = stack[--stackPosition];
        }
        else
        {
            (*root)->item = *token;
            stack[stackPosition++] = &(*root)->right;
            root = &(*root)->left;
        }
        token = strtok(NULL, " ");
    }
}
void printTree(BTNode *node)
{
    if (node == NULL)
        return;
    printTree(node->left);
    printf("%c ", node->item);
    printTree(node->right);
}


void printTreePostfix(BTNode *node)
{
    if (node == NULL)
        return;
    printTreePostfix(node->left);
    printTreePostfix(node->right);
    printf("%c ", node->item);
}

double computeTree(BTNode *node)
{
	double x,y,z;
	if ((node->item) == '+'||(node->item) == '-'||(node->item) == '*'||(node->item) == '/')
	{
		x = computeTree(node->left);
		y = computeTree(node->right);
		if (node->item =='+')
			z=x+y;
		else if (node->item =='-')
			z=x-y;
		else if (node->item =='*')
			z=x*y;
		else if (node->item =='/')
			z=x/y;
		return z;
	}
	else 
	    return node->item - '0';	
}

void push(Stack *sPtr, BTNode *item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}