#include <stdio.h>
#include <stdlib.h>

#define N_VERTEX 11
#define WHITE 1
#define GREY 2
#define BLACK 3
#define INFINITE 99999
#define NIL -1
#define NULL 0

#define CS111 0
#define CS141 1
#define CS151 2
#define CS211 3
#define CS251 4
#define CS261 5
#define CS301 6
#define CS342 7
#define CS361 8
#define CS362 9
#define CS401 10

class Queue
{
    struct Node
    {
        int data;
        struct Node* next;
    };

    struct Node* head;
    struct Node* tail;
    int length;

public:
    Queue()
    {
        init();
    }
    void init()
    {
        head = NULL;
        tail = NULL;
        length = 0;
    }
    bool is_empty()
    {
        if(length == 0)
            return true;
        return false;
    }
    void enqueue(int item)
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->data = item;
        newNode->next = NULL;
        if(head == NULL)
            head = newNode;
        else
            tail->next = newNode;
        tail = newNode;
        length++;
    }
    int dequeue()
    {
        struct Node* temp = head;
        int ret = temp->data;
        head = head->next;
        if(head == NULL)
            tail = NULL;
        free(temp);
        length--;
        return ret;
    }
    void print()
    {
        struct Node* temp = head;
        while(temp != NULL)
        {
            printf("%d ",temp->data);
            temp = temp->next;
        }
        printf("\n");
    }
};

struct Node
{
    int vertex;
    struct Node* next;
};

class Linked_list
{
public:
    struct Node* head;
    Linked_list()
    {
        init();
    }
    void init()
    {
        head = NULL;
    }
    bool is_empty()
    {
        if(head == NULL)
            return true;
        return false;
    }
    void insert(int v)
    {
        struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
        newNode->vertex = v;
        newNode->next = head;
        head = newNode;
    }
    void print()
    {
        struct Node* temp = head;
        while(temp != NULL)
        {
            printf("%d ",temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }
};

class Graph
{
public:
    Linked_list LL[N_VERTEX];
    void add_edge(int u, int v)
    {
        LL[u].insert(v);
        // LL[v].insert(u); // directed graph
    }
    void print_graph()
    {
        printf("Number of vertex %d\n", N_VERTEX);
        for(int i=0; i<N_VERTEX; i++)
        {
            printf("List of %d: ", i);
            LL[i].print();
        }
    }
    void BFS(int s)
    {
        int color[N_VERTEX];
        int d[N_VERTEX];
        int par[N_VERTEX];

        for(int i=0; i<N_VERTEX; i++)
        {
            color[i] = WHITE;
            d[i] = INFINITE;
            par[i] = NIL;
        }

        color[s] = GREY;
        d[s] = 0;
        par[s] = NIL;

        Queue q;
        q.enqueue(s);
        while( ! q.is_empty())
        {
            int u = q.dequeue();
            Node* temp = LL[u].head;
            while(temp != NULL)
            {
                int v = temp->vertex;
                if(color[v] == WHITE)
                {
                    color[v] = GREY;
                    d[v] = d[u] + 1;
                    par[v] = u;
                    q.enqueue(v);
                }
                temp = temp->next;
            }
            color[u] = BLACK;
        }
        // print the results
        for(int i=0; i<N_VERTEX; i++)
        {
            printf("%d ", d[i]);
        }
        printf("\n");
        for(int i=0; i<N_VERTEX; i++)
        {
            printf("%d ", par[i]);
        }
        printf("\n");
    }
    void DFS_Visit_topo(int u, int color[], int d[], int f[], int par[], int& time, Linked_list& Z)
    {
        /* write your code here
         *
         *
         *
         *
         */
         color[u]=GREY;
         time= time+1;
         d[u]= time;
         struct Node* temp = LL[u].head;
		 while(temp!=NULL){
		 	int v=temp->vertex;

		 	if(color[v] == WHITE){
		 		par[v] = u;
		 		DFS_Visit_topo(v,color,d,f,par,time,Z);
			 }
			 temp= temp->next;
		 }
		 color[u]= BLACK;
		 Z.insert(u);
		 time= time+1;
		 f[u]= time;



    }
    void DFS_topo(Linked_list& Z)
    {
        int color[N_VERTEX]; // tracks color of each vertex
        int d[N_VERTEX]; // tracks discovery time of each vertex
        int f[N_VERTEX]; // tracks finishing time of each vertex
        int par[N_VERTEX]; // tracks parent of each vertex
        int time; // tracks the time
		// you will need to pass these as parameters to DFS_Visit

        /* write your code here
         *
         *
         *
         *
         */
            for(int i=0; i<N_VERTEX; i++){
            color[i]= WHITE;
            par[i]= NIL;

         }
         time= 0;
         for(int i=0; i<N_VERTEX; i++){
            if(color[i]== WHITE)
                DFS_Visit_topo(i, color, d, f, par,time,Z);
         }


        // print the results
        printf("Vertex        : ");
        for(int i=0; i<N_VERTEX; i++)
        {
            printf("%3d ", i);
        }
        printf("\nDiscovery time: ");
        for(int i=0; i<N_VERTEX; i++)
        {
            printf("%3d ", d[i]);
        }
        printf("\nFinishing time: ");
        for(int i=0; i<N_VERTEX; i++)
        {
            printf("%3d ", f[i]);
        }
        printf("\nParent        : ");
        for(int i=0; i<N_VERTEX; i++)
        {
            printf("%3d ", par[i]);
        }
        printf("\n");
    }
    void topological_sort()
    {
        Linked_list Z;
        DFS_topo(Z);
        Node* temp = Z.head;
        printf("Topologically sorted order: ");
        while(temp != NULL)
        {
            printf("%3d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

};



int main()
{
    Graph G1;
    G1.add_edge(CS111, CS141);
    G1.add_edge(CS111, CS151);
    G1.add_edge(CS141, CS211);
    G1.add_edge(CS141, CS251);
    G1.add_edge(CS141, CS261);
    G1.add_edge(CS151, CS251);
    G1.add_edge(CS151, CS301);
    G1.add_edge(CS251, CS342);
    G1.add_edge(CS251, CS361);
    G1.add_edge(CS251, CS401);
    G1.add_edge(CS261, CS361);
    G1.add_edge(CS261, CS362);

    G1.print_graph();

    G1.topological_sort();

    return 0;

}
