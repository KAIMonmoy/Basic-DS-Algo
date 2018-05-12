#include<stdio.h>
#include<stdlib.h>
#include<iostream>

using namespace std;


#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

class ListNode
{
public:
    int item;
    ListNode * next;
};

class LinkedListWithTail
{

    ListNode * list;
    ListNode * tail;
    int length;

public:
    LinkedListWithTail()
    {
        list = 0;  //initially set to NULL
        tail = 0;
        length=0;
    }

    int getLength()
    {
        return length;
    }

    //add required codes to set up tail pointer
    int insertItem(int item) //insert at the beginning
    {
        ListNode * newNode ;
        newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = list ; //point to previous first node
        list = newNode ; //set list to point to newnode as this is now the first node
        length++;

        if(length==1) {
            tail = list;
        }

        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    int deleteItem(int item)
    {
        ListNode *temp, *prev ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) break ;
            prev = temp;
            temp = temp->next ; //move to next node
        }
        if (temp == 0) return NULL_VALUE ; //item not found to delete
        if (temp == list) //delete the first node
        {
            list = list->next ;
            delete temp ;
            length--;
        }
        else
        {
            if(temp == tail) {
                tail = prev;
            }
            prev->next = temp->next ;
            delete temp;
            length--;
        }

        if(!length) {
            tail = 0;
        }

        return SUCCESS_VALUE ;
    }

    //add required codes to set up tail pointer
    ListNode * searchItem(int item)
    {
        ListNode * temp ;
        temp = list ; //start at the beginning
        while (temp != 0)
        {
            if (temp->item == item) return temp ;
            temp = temp->next ; //move to next node
        }
        return 0 ; //0 means invalid pointer in C, also called NULL value in C
    }


    void printList()
    {
        ListNode * temp;
        temp = list;
        printf("\n>>> ");
        while(temp!=0)
        {
            printf(" %d ", temp->item);
            temp = temp->next;
            if(temp!=0) printf("<- ");
        }
        printf(" <- Head\n");
        printf("Length: %d\n",length);
    }


    //------------write code for the functions below-----------
    int insertLast(int item)
    {
        //write your codes here
        if(!length) {
            return insertItem(item);
        }

        ListNode * newNode = new ListNode() ;
        newNode->item = item ;
        newNode->next = 0 ;

        tail->next = newNode ;
        tail = newNode;
        length++;

        return SUCCESS_VALUE ;
    }

    ListNode * getItemAt(int pos)
    {
         //write your codes here
         if(pos > length || pos <= 0) return 0;

         ListNode *temp = list;

         for(int i=1; i<pos; i++) {
            temp = temp->next;
         }

         return temp;

    }

    int deleteLast()
    {
        //write your codes here
        if(tail == 0) return NULL_VALUE;

        if(length == 1) {
            int data = tail->item;
            deleteItem(tail->item);
            return data;
        }

        ListNode *temp = list;
        while(temp->next!=tail) {
            temp = temp->next;
        }

        int data = tail->item;
        delete tail;
        tail = temp;
        tail->next = 0;
        length--;

        return data;

    }

    ~LinkedListWithTail()
    {
        while(length) {
            deleteItem(list->item);
        }
    }
};

class Queue
{
    LinkedListWithTail ll;
public:
    Queue() { }

    void enqueue(int item)
    {
        //write your codes here
        ll.insertItem(item);
    }

    int dequeue()
    {
       //write your codes here
        if(ll.getLength()==0) return NULL_VALUE;

        return ll.deleteLast();
    }

    void printStack()
    {
        ll.printList();
    }

    ~Queue()
    {
        delete &ll;
    }
};

int main(void)
{
    Queue qu;

    while(1)
    {
        printf("\n1. Enqueue. 2. Dequeue. 3. Print. 4. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            qu.enqueue(item);
        }
        else if(ch==2)
        {
            int item=qu.dequeue();
            if(item!=NULL_VALUE) printf("Dequeued : %d\n",item);
            else printf("Queue is empty!\n");
        }
        else if(ch==3)
        {
            qu.printStack();
        }
        else if(ch==4)
        {
            printf("\n\nExiting...\n");
            break;
        }
    }

}

