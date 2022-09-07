#include <stdio.h>

struct Queue{
    int data[4];
    int f; 
    int r;
}que;

void enQ(int input){
    if(que.f == ((que.r+1)%4)){ //Queue full
        printf("FULL  pull front\n");
        //full scenario case 1 : rear input
//      data[rear] = input;

        //full scenario case 2 : pull front 
      que.f = (que.f+1)%4;    
      que.data[que.f] = NULL;         //not return
      que.r = (que.r+1)%4;
      que.data[que.r] = input;
      printf("enQ : %d\n", que.data[que.r]); //dispaly

    }
    else{ // enqueue sequence
        que.r = (que.r+1)%4;
        que.data[que.r] = input;
        printf("enQ : %d\n", que.data[que.r]); //dispaly
    }
}

int deQ(void){
    if(que.f == que.r) { //Queue empty
        printf("EMPTY\n");
        return ;
    }
    else{ // dequeue sequence
        int output;
        que.f = (que.f+1)%4;
        printf("deQ : %d\n", que.data[que.f]); //dispaly
        output = que.data[que.f];
        que.data[que.f] = NULL;
        return output;
    }
}

void display()
{
        printf("Queue : [0] [1] [2] [3] F: %d R: %d\n", que.f, que.r);
        printf("         %d  %d  %d  %d\n\n", que.data[0], que.data[1], que.data[2], que.data[3]);
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