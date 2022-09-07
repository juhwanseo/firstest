#include <stdio.h>
#include <stdlib.h>

struct NODE {
	struct NODE *node;
	int data;
};

struct NODE *Top = NULL;
/*
void push(int input){
    if(Top == NULL){
        struct NODE *newnode = malloc(sizeof(struct NODE));
        newnode->data = input;
        newnode->node = NULL; //first data
        Top = newnode;
    }
    else {
        struct NODE *newnode = malloc(sizeof(struct NODE));
        newnode->data = input;
        newnode->node = Top;
        Top = newnode;
    }
    printf("push : %d\n", input);
}
*/

void push(int input){
    struct NODE *newnode = malloc(sizeof(struct NODE));
    newnode->data = input;
    if(Top == NULL){
        newnode->node = NULL; //first data
    }
    else {
        newnode->node = Top;
    }
    Top = newnode;

    printf("push : %d\n", input);
}

int pop(void){
        if(Top == NULL){
            printf("empty stack : \n");//empty
            return ;
    }
    else {
        struct NODE *delnode = Top;
        int pop_data = Top->data;
        Top = Top->node;
        free(delnode);
        printf("pop : %d\n", pop_data);
        return pop_data;
    }
    
}

int main() {
    
    pop();
    push(10);
    push(20);
    push(30);
    push(40);
    pop();
    push(50);
    push(60);
    pop();
    pop();
    pop();
    pop();
    pop();
    pop();

    return 0;
}