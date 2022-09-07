
#include <stdio.h>
#define size 4
int data[size];
int top = 0;

void push(int input)
{
    if(top == 4){
        printf("push : Full\t top : %d\n", top);
    }
    else{
        data[top] = input;
        top++;
        printf("push : %d\t top : %d\n", input, top);
    }
}

int pop(void)
{
    if(top == 0){
        printf("pop : Empty\t top : %d\n", top);
        return ;
    }
    else{
        int output;
        output = data[top-1];
        data[top-1] = 0;
        top--;
        printf("pop : %d\t top : %d\n", output, top);
        return output;
    }
}

void display()
{
    printf("Stack : [0][1][2][3]\n");
    printf("         %d  %d  %d  %d\n\n", data[0], data[1], data[2], data[3]);
}

int main() {
    display();
    
    pop();
    display();

    push(3);
    display();

    push(6);
    display();
    
    pop();
    display();
    
    pop();
    display();

    pop();
    display();

    push(1);
    display();
    
    push(2);
    display();

    push(3);
    display();

    push(4);
    display();
    
    push(5);
    display();

    return 0;
}