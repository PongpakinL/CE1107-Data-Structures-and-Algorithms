#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int precedence(char);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    LinkedList temp;
    temp.head = NULL;
    temp.size = 0;
    while (*infix != '\0') 
    {
        char num[SIZE];
        int i = 0;
        num[0] = '\0';
 
        while (*infix >= '0' && *infix != '\0')
        {
            num[i] = *infix;
            infix++;
            i++;
        }
        num[i] = '\0';

        if (num[0] == '\0')
        {
            insertNode(&temp,*infix,OPT);
        }
        else
        {
            insertNode(&temp,atoi(num),OPERAND);
            if (*infix != '\0')
            {
                insertNode(&temp,*infix,OPT);
            }
        }
 
        if (*infix != '\0')
        {
            infix++;
        } 
        else 
        {
            break;
        }
    }
    Stack s;
    s.head = NULL;
    s.size = 0;

    int i = 0;
    int j = 0;
    char c;
    ListNode* cur = NULL;
    cur = temp.head;
    while (cur != NULL)
    {
        if(cur->type == OPERAND)
        {
            insertNode(inExpLL,cur->item,OPERAND);
        }
        else
        {
            c = (char)(cur->item);
            switch(c)
            {
                case '*':
                case '/':
                case '+':
                case '-':
                    while(isEmptyStack(s)==0 && peek(s) != ')' && precedence(peek(s)) >= precedence(c) )
                    {
                        insertNode(inExpLL,peek(s),OPT);
                        pop(&s);
                    }
                    push(&s,cur->item);
                    break;
                case ')':
                    push(&s,cur->item);
                    break;
                case '(':
                    while (isEmptyStack(s) == 0)
                    {
                        if(peek(s) != ')')
                        {
                            insertNode(inExpLL,peek(s),OPT);
                            pop(&s);
                        }
                        else
                        {
                            pop(&s);
                            break;
                        }
                    }
                    break;
            }
        }
        cur = cur->next;
    }
    while (isEmptyStack(s) == 0)
    {
        insertNode(inExpLL,peek(s),OPT);
        pop(&s);
    }
    
}

int precedence(char op)
{
    if(op == '*' || op == '/')
        return 1;
    else return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
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

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}