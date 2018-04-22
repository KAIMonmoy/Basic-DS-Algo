#include<stdio.h>
#include<stdlib.h>
#include <string.h>

#define LIST_INIT_SIZE 2
#define NULL_VALUE -99999
#define SUCCESS_VALUE 99999

int listMaxSize;
int * list;
int length;

///********************** My function prototype declaration **************************
int getLength();
void shrinkList();
int insertItemAt(int pos, int item);
int deleteLast();
void clear();
int deleteAll();
///***********************************************************************************

void initializeList()
{
	listMaxSize = LIST_INIT_SIZE;
	list = (int*)malloc(sizeof(int)*listMaxSize) ;
	length = 0 ;
}

int searchItem(int item)
{
	int i = 0;
	for (i = 0; i < length; i++)
	{
		if( list[i] == item ) return i;
	}
	return NULL_VALUE;
}

int insertItem(int newitem)
{
	///initializing list in case clear() was called before
	if(!listMaxSize){
		initializeList();
	}

	int * tempList ;
	if (length == listMaxSize)
	{
		//allocate new memory space for tempList
		listMaxSize = 2 * listMaxSize ;
		tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
		int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
	};

	list[length] = newitem ; //store new item
	length++ ;
	return SUCCESS_VALUE ;
}


int deleteItemAt(int position) //version 2, do not preserve order of items
{
	if ( position >= length ) return NULL_VALUE;
	list[position] = list[length-1] ;
	length-- ;
    shrinkList(); ///calling shrinkList()
	return SUCCESS_VALUE ;
}


int deleteItem(int item)
{
	int position;
	position = searchItem(item) ;
	if ( position == NULL_VALUE ) return NULL_VALUE;
	return deleteItemAt(position) ;
}

void printList()
{
    int i;
	printf("\n>>> ");
    for(i=0;i<length;i++)
        printf("%d ", list[i]);
    printf("\nCurrent size: %d, current length: %d\n", listMaxSize, length);
}

///*********************** My Task Codes ******************************

///task-1
int getLength()
{
    return length;
}

///task-2
int insertItemAt(int pos, int item)
{
    if(pos >= length) return NULL_VALUE;

    int temp = list[pos];
    list[pos] = item;
    return insertItem(temp);
}


///task-3
void shrinkList()
{
    int * tempList ;
    if (length == (listMaxSize / 2) && listMaxSize>LIST_INIT_SIZE)
    {
        //allocate new memory space for tempList
        listMaxSize = (listMaxSize/2) ;
        tempList = (int*) malloc (listMaxSize*sizeof(int)) ;
        int i;
        for( i = 0; i < length ; i++ )
        {
            tempList[i] = list[i] ; //copy all items from list to tempList
        }
        free(list) ; //free the memory allocated before
        list = tempList ; //make list to point to new memory
    };
}

///task-4
int deleteLast()
{
	int position;
	position = length-1 ;
	if ( position < 0 ) return NULL_VALUE;
	return deleteItemAt(position);
}

///task-5
void clear()
{
    free(list);
	list = NULL;
    length = 0;
    listMaxSize = 0;
}

///task-6
int deleteAll()
{
    clear();
    initializeList();
	return ((length == 0) && (listMaxSize == LIST_INIT_SIZE)) ? SUCCESS_VALUE : NULL_VALUE;
}

///part of task-7
void getLastTwoItems(int *a, int *b)
{
	*a = list[length-2];
	*b = list[length-1];
	deleteLast();
	deleteLast();
}


///**********************************************************************

/*
///main function-1
int main(void)
{
    initializeList();
    while(1)
    {
        printf("\n 1. Insert new item.   2. Delete item at. 3. Delete item.\n");
        printf(" 4. Search item.       5. Get length.     6. Insert item at.\n");
		printf(" 7. Delete last item.  8. Clear list.     9. Delete all items.\n");
		printf("10. Print List        11. Exit.\n");


        int ch;
        scanf("%d",&ch);
		int returnValue = 0;
        if(ch==1)
        {
			printf("\nInserting item.\nEnter the value of the item : ");
            int item;
            scanf("%d", &item);
            returnValue = insertItem(item);
        }
        else if(ch==2)
        {
			printf("\nDeleting item at position.\nEnter the position of the item : ");
            int pos;
            scanf("%d", &pos);
            returnValue = deleteItemAt(pos);
        }
        else if(ch==3)
        {
			printf("\nDeleting item.\nEnter the value of the item : ");
            int item;
            scanf("%d", &item);
            returnValue = deleteItem(item);
        }
        else if(ch==4)
        {
			printf("\nSearching item.\nEnter the value of the item : ");
			int item;
            scanf("%d", &item);
            returnValue = searchItem(item);
			if(returnValue != NULL_VALUE) {
				printf("Item %d found at position %d .\n", item, returnValue);
			}
        }
        else if(ch==5)
        {
			returnValue = getLength();
			printf("\nLength of the list : %d\n", returnValue);
        }
		else if(ch==6)
        {
			printf("\nInserting item at.\nEnter the position and value of the item : ");
			int item, pos;
            scanf("%d %d", &pos, &item);
            returnValue = insertItemAt(pos, item);
        }
        else if(ch==7)
        {
			printf("\nDeleting last item\n");
			returnValue = deleteLast();
			if(returnValue == NULL_VALUE){
				printf("\nLength of the list : %d\n", length);
			}
        }
        else if(ch==8)
        {
			printf("\nClearing list\n");
			clear();
			returnValue = 0;
        }
		else if(ch==9)
        {
			printf("\nDeleting all items\n");
			returnValue = deleteAll();
        }
		else if(ch==10)
        {
			printList();
        }
        else if(ch==11)
        {
			printf("\nExiting...\n");
			break;
        }

		if(returnValue == NULL_VALUE) {
			printf("Operation failed!\n");
		}
    }

}
*/

//main function-2 (task-7)
int main(void)
{
    char command[101];

    while (1) {

        printf("\nEnter command line : ");
        gets(command);

        // printf("command : %s command_length : %d\n", command, strlen(command));

        int n = strlen(command);
        if(!n) break;

		initializeList();
        int first_num, second_num;
        for (int i = 0; i < n; i++) {
            switch (command[i]) {
                case '+':
                // printList();
                    getLastTwoItems(&first_num, &second_num);
                    insertItem((first_num + second_num));
                // printList();
                    break;
                case '-':
                // printList();
                    getLastTwoItems(&first_num, &second_num);
                    insertItem((first_num - second_num));
                // printList();
                    break;
                case '*':
                // printList();
                    getLastTwoItems(&first_num, &second_num);
                    insertItem((first_num * second_num));
                // printList();
                    break;
                case '/':
                // printList();
                    getLastTwoItems(&first_num, &second_num);
                    if(second_num) {
                        insertItem((first_num / second_num));
                    } else {
                        printf("\nDivided by zero!\nInserting zero in the list\n");
                        insertItem(0);
                    }
                // printList();
                    break;
                default:
                // printList();
                    insertItem(command[i] - '0');
                // printList();
            }
        }

        int answer = list[0];
        deleteLast();

        printf("%s = %d\n", command, answer);

        clear();
    }

    return 0;
}
