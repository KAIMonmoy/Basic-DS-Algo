#include<stdio.h>
#include<stdlib.h>
#include<cstring>

#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3



class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
	if (length == queueMaxSize)
	{
		int * tempData ;
		//allocate new memory space for tempList
		queueMaxSize = 2 * queueMaxSize ;
		tempData = new int[queueMaxSize] ;
		int i, j;
		j = 0;
		for( i = rear; i < length ; i++ )
		{
			tempData[j++] = data[i] ; //copy items from rear
		}
		for( i = 0; i < rear ; i++ )
		{
			tempData[j++] = data[i] ; //copy items before rear
		}
		rear = 0 ;
		front = length ;
		delete[] data ; //free the memory allocated before
		data = tempData ; //make list to point to new memory
	}

	data[front] = item ; //store new item
	front = (front + 1) % queueMaxSize ;
	length++ ;
}


bool Queue::empty()
{
	if(length == 0) return true ;
	else return false ;
}


int Queue::dequeue()
{
	if(length == 0) return NULL_VALUE ;
	int item = data[rear] ;
	rear = (rear + 1) % queueMaxSize ;
	length-- ;
	return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
	int nVertices, nEdges ;
	bool directed ;
	int ** matrix ; //adjacency matrix to store the graph
	//define other variables required for bfs such as color, parent, and dist
	//you must use pointers and dynamic allocation

	int *parent, *distance, *color; /// for BFS
	int *start, *finish, time; /// for DFS

public:
	Graph(bool dir = false);
	~Graph();
	void setnVertices(int n);
	void addEdge(int u, int v);
	void removeEdge(int u, int v);
	bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
	void bfs(int source); //will run bfs in the graph
	void dfs( );//will run dfs in the graph
	void dfsVisit(int vertex);

	///for checking BFS and DFS
	int* getParent() const {return parent;}
	int* getDistance() const {return distance;}
	int* getStart() const {return start;}
	int* getFinish() const {return finish;}
	int getNumVertices() const {return nVertices;}
};


Graph::Graph(bool dir)
{
	nVertices = 0 ;
	nEdges = 0 ;
	matrix = 0 ;
	directed = false ; //set direction of the graph
	//define other variables to be initialized

	parent = 0;
	distance = 0;
	color = 0;

	start = 0;
	finish = 0;
	time = 0;

}

void Graph::setnVertices(int n)
{
	this->nVertices = n ;

	//allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0;i<nVertices;i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0;j<nVertices;j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }

    ///setting BFS and DFS parameters
	if(parent) delete[] parent;
	if(distance) delete[] distance;
	if(color) delete[] color;

	if(start) delete[] start;
	if(finish) delete[] finish;

	parent = new int[n];
	distance = new int[n];
	color = new int[n];

	start = new int[n];
	finish = new int[n];
	time = 0;

}

void Graph::addEdge(int u, int v)
{
    //write your code here
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    this->nEdges++;
    matrix[u][v] = 1;
    printf("%d",directed);
    if(!directed) matrix[v][u] = 1;

}

void Graph::removeEdge(int u, int v)
{
    //write this function
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return;
    this->nEdges-- ;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
}

bool Graph::isEdge(int u, int v)
{
    //returns true if (u,v) is an edge, otherwise should return false
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    if(matrix[u][v]) return true;
    return false;
}

int Graph::getDegree(int u)
{
    //returns the degree of vertex u
    if(u<0 || u>=nVertices) return 0;
    int deg=0;
    for(int i=0; i<nVertices; i++) {
        deg = deg + matrix[u][i];
        if(matrix[u][i] && u==i) deg++;
    }
    return deg;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    //returns true if vertices u and v have common adjacent vertices
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return false;
    for (int i = 0; i < nVertices; i++) {
        if(matrix[u][i] & matrix[v][i]) return true;
    }
    return false;

}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        distance[i] = INFINITY ;
    }
    Queue q ;

    color[source] = GREY;
    distance[source] = 0 ;

    q.enqueue(source) ;

    while( !q.empty() )
    {
        int u = q.dequeue();

        for(int v=0; v<nVertices; v++) {
            if(matrix[u][v]) {
                if(color[v] == WHITE) {
                    parent[v] = u;
                    distance[v] = distance[u] + 1;
                    color[v] = GREY;
                    q.enqueue(v);
                }
            }
        }

        color[u] = BLACK;
    }

}

void Graph::dfs( )
{
    //write this function
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        start[i] = -1 ;
        finish[i] = -1 ;
    }

    time = 0;

    for(int i=0; i<nVertices; i++) {
        if(color[i]==WHITE)
            dfsVisit(i);
    }

}

void Graph::dfsVisit(int vertex)
{
    color[vertex] = GREY;
    start[vertex] = ++time;

    for(int i=0; i<nVertices; i++) {
        if(matrix[vertex][i]) {
            if(color[i] == WHITE)
                dfsVisit(i);
        }
    }

    color[vertex] = BLACK;
    finish[vertex] = ++time;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return INFINITY;

    bfs(u);
    return distance[v];
}


void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0;i<nVertices;i++)
    {
        printf("%d:", i);
        for(int j=0; j<nVertices;j++)
        {
            if(matrix[i][j]==1)
                printf(" %d", j);
        }
        printf("\n");
    }
}

Graph::~Graph()
{
    //write your destructor here
    nVertices = 0;
    nEdges = 0;
    directed = false;

    ///delete matrix
    for(int i = 0; i < nVertices; ++i) {
        delete[] matrix[i];
    }
    delete[] matrix;

    delete[] parent; parent = 0;
    delete[] distance; distance = 0;
    delete[] color; color = 0;
    delete[] start; start = 0;
    delete[] finish; finish = 0;
    time = 0;
}


//**********************Graph class ends here******************************


//******main function to test your code*************************
int main(void)
{
    int n;
    Graph g = 0;

    while(1)
    {
        printf("\n1. Create new graph. 2. Add Edge.   3. Remove Edge.         4. Is Edge.\n");
        printf("5. Print Graph.      6. Get Degree. 7. Has Common Adjacent. 8. get Distance.\n");
        printf("9. BFS.             10. DFS.       11. Exit.\n");

        int ch;
        scanf("%d%*c",&ch);

        if(ch==1)
        {
            printf("\nCreating new graph...\n\n");

            printf("Enter number of vertices: ");
            scanf("%d", &n);
            g.setnVertices(n);
        }
        else if(ch==2)
        {
            int u, v;
            printf("\nAdding Edge...\n\n");
            printf("Enter starting node & ending node : ");
            scanf("%d %d", &u, &v);
            g.addEdge(u, v);
        }
        else if(ch==3)
        {
            int u, v;
            printf("\nRemoving Edge...\n\n");
            printf("Enter starting node & ending node : ");
            scanf("%d %d", &u, &v);
            g.removeEdge(u, v);
        }
        else if(ch==4)
        {
            int u, v;
            printf("\nChecking Edge...\n\n");
            printf("Enter starting node & ending node : ");
            scanf("%d %d", &u, &v);
            if(g.isEdge(u, v)) {
                printf("%d -> %d is an edge.", u, v);
            } else {
                printf("%d -> %d is NOT an edge.", u, v);
            }
        }
        else if(ch==5)
        {
            printf("\nGraph with adjacency matrix:\n");
            g.printGraph();
        }
        else if(ch==6)
        {
            int u;
            printf("\nChecking degree of a node...\n\n");
            printf("Enter the node : ");
            scanf("%d", &u);
            printf("%d node has &d degree.", u, g.getDegree(u));
        }
        else if(ch==7)
        {
            int u, v;
            printf("\nChecking if edges have common adjacent nodes...\n\n");
            printf("Enter two nodes : ");
            scanf("%d %d", &u, &v);
            if(g.hasCommonAdjacent(u, v)) {
                printf("%d & %d have common adjacent nodes.", u, v);
            } else {
                printf("%d & %d do NOT have common an edge.", u, v);
            }
        }
        else if(ch==8)
        {
            int u, v;
            printf("\nChecking distance between two nodes...\n\n");
            printf("Enter two nodes : ");
            scanf("%d %d", &u, &v);
            printf("Distance between %d & %d is : %d", u, v, g.getDist(u,v));
        }
        else if(ch==9)
        {
            int u;
            printf("\nRunning BFS...\n\n");
            printf("Enter starting node : ");
            scanf("%d", &u);
            g.bfs(u);
            printf("\nStarting node : %d", u);
            int* prtLst = g.getParent();
            int* distLst = g.getDistance();
            printf("\nParent List : ");
            for(int i =0; i<g.getNumVertices(); i++) {
                printf("\n\tP:%d->C:%d ", prtLst[i], i);
            }
            printf("\nDistance List : ");
            for(int i =0; i<g.getNumVertices(); i++) {
                printf("\n\t%d->D:%d ", i, distLst[i]);
            }
            printf("\n");
        }
        else if(ch==10)
        {
            printf("\nRunning DFS...\n\n");
            g.dfs();
            int* strtLst = g.getStart();
            int* fnsLst = g.getFinish();
            for(int i=0; i<g.getNumVertices(); i++) {
                printf("%d->Start:%d Finish:%d\n",i, strtLst[i], fnsLst[i]);
            }
        }
        else if(ch==11)
        {
            printf("\nExiting...\n\n");
            break;
        }
    }

}
