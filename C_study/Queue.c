#include <stdio.h>
#define size 4

int data[size];
int front; 
int rear;

void enQ(int input){
    if(front == ((rear+1)%size)){ //Queue full
        printf("FULL  pull front\n");
        //full scenario case 1 : rear input
//      data[rear] = input;

        //full scenario case 2 : pull front 
      front = (front+1)%size;    
      data[front] = NULL;         //not return
      rear = (rear+1)%size;
      data[rear] = input;
      printf("enQ : %d\n", data[rear]); //dispaly

    }
    else{ // enqueue sequence
        rear = (rear+1)%size;
        data[rear] = input;
        printf("enQ : %d\n", data[rear]); //dispaly
    }
}

int deQ(void){
    if(front == rear) { //Queue empty
        printf("EMPTY\n");
        return ;
    }
    else{ // dequeue sequence
        int output;
        front = (front+1)%size;
        printf("deQ : %d\n", data[front]); //dispaly
        output = data[front];
        data[front] = NULL;
        return output;
    }
}

void display()
{
        printf("Queue : [0] [1] [2] [3] F: %d R: %d\n", front, rear);
        printf("         %d  %d  %d  %d\n\n", data[0], data[1], data[2], data[3]);
}

int main() {
    display();
    
    enQ(5);
    display();
    
    enQ(10);
    display();
    
    enQ(20);
    display();
    
    enQ(30);
    display();
    
    enQ(40);
    display();
    
    deQ();
    display();
    
    deQ();
    display();
    
    deQ();
    display();
    
    deQ();
    display();

return 0;
}
