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
            if(temp!=0) printf("-> ");
        }
        printf("\n");
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
            return deleteItem(tail->item);
        }

        ListNode *temp = list;
        while(temp->next!=tail) {
            temp = temp->next;
        }

        delete tail;
        tail = temp;
        tail->next = 0;
        length--;

        return SUCCESS_VALUE;

    }

    ~LinkedListWithTail()
    {
        while(length) {
            deleteLast();
        }
    }
};

void showError(int retVal)
{
    if(retVal == SUCCESS_VALUE) {
        cout << "Success!" << endl;
    }
    else {
        cout << "Failed!" << endl;
    }
}

int main(void)
{
    LinkedListWithTail ll;

    while(1)
    {
        printf("\n1. Insert new item. 2. Delete item.  3. Search item. \n");
        printf("4. Insert Last    . 5. Print.        6. Get Item At.\n");
        printf("7. Delete Last    . 8. Exit.\n");

        int ch;
        scanf("%d",&ch);
        if(ch==1)
        {
            int item;
            scanf("%d", &item);
            showError(ll.insertItem(item));
        }
        else if(ch==2)
        {
            int item, retVal;
            scanf("%d", &item);
            showError(ll.deleteItem(item));
        }
        else if(ch==3)
        {
            int item;
            scanf("%d", &item);
            ListNode * res = ll.searchItem(item);
            if(res!=0) printf("Found.\n");
            else printf("Not found.\n");
        }
        else if(ch==4)
        {
            int item;
            scanf("%d", &item);
            showError(ll.insertLast(item));
        }
        else if(ch==5)
        {
            ll.printList();
        }
        else if(ch==6)
        {
            int pos;
            scanf("%d", &pos);
            ListNode *node = ll.getItemAt(pos);
            if(node == 0) {
                printf("%d no. node not found!\n", pos);
            }
            else {
                printf("%d found at %d no. position\n", node->item, pos);
            }
        }
        else if(ch==7)
        {
            showError(ll.deleteLast());
        }
        else if(ch==8)
        {
            printf("\n\nExiting...\n");
            break;
        }

    }

}
