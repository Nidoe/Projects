/*
Name: Luv Somani
Pawprint: lrsfh3
Programming Assignment #1
*/

/*
Pseudocode for algorithm:

Store the adjacency list by creating a separate list for each vertex with an array of "head" pointers for each vertex

BFS function:

Input: array of pointers for the linked lists, the initial vertex, the list of "visited" vertexes, and the total number of vertices.

Step 1: Set the visited value for the vertex to "1" or "visited"

Step 2: Create an empty queue and initialize it to null and push the vertex to the queue

Step 3: The main loop:
				While the queue isn't empty -> Retrieve the first vertex on the queue and remove it from the queue
				Retrieve the adjacency list for that vertex and check each adjacent vertex to see if it has been "visited" or not
				For all "unvisited" nodes, add each one to the queue and set it to "visited"
				Once all the connected vertices have been found and processed through the queue, return the list of "visited" vertices.
				
To determine the number of connected components -> the number of times the BFS function is executed.

To determine the smallest component size -> Global variable to track the smallest component based on number of vertices "queued" during one execution of the BFS function.
		

*/



/* Imports */

#include <stdio.h>
#include <stdlib.h>

/* Global variable to help keep track of component sizes */
int smallestComponent = 0;

/* Simple Node/List structure */
struct list{

    int data;

    struct list *next;

}list;

/* Queue structure  */
typedef struct Queue
{
        int capacity;
        int size;
        int front;
        int rear;
        int *elements;
}Queue;
/* crateQueue function takes argument the maximum number of elements the Queue can hold, creates
   a Queue according to it and returns a pointer to the Queue. */
Queue * CreateQueue(int maxElements)
{
        /* Create a Queue */
        Queue *Q;
        Q = (Queue *)malloc(sizeof(Queue));
        /* Initialise its properties */
        Q->elements = (int *)malloc(sizeof(int)*maxElements);
        Q->size = 0;
        Q->capacity = maxElements;
        Q->front = 0;
        Q->rear = -1;
        /* Return the pointer */
        return Q;
}
void Dequeue(Queue *Q)
{
        /* If Queue size is zero then it is empty. So we cannot pop */
        if(Q->size==0)
        {
                printf("Queue is Empty\n");
                return;
        }
        /* Removing an element is equivalent to incrementing index of front by one */
        else
        {
                Q->size--;
                Q->front++;
                /* As we fill elements in circular fashion */
                if(Q->front==Q->capacity)
                {
                        Q->front=0;
                }
        }
        return;
}
int Front(Queue *Q)
{
        if(Q->size==0)
        {
                printf("Queue is Empty\n");
                exit(0);
        }
        /* Return the element which is at the front*/
        return Q->elements[Q->front];
}
void Enqueue(Queue *Q,int element)
{
        /* If the Queue is full, we cannot push an element into it as there is no space for it.*/
        if(Q->size == Q->capacity)
        {
                printf("Queue is Full\n");
        }
        else
        {
                Q->size++;
                Q->rear = Q->rear + 1;
                /* As we fill the queue in circular fashion */
                if(Q->rear == Q->capacity)
                {
                        Q->rear = 0;
                }
                /* Insert the element in its rear side */ 
                Q->elements[Q->rear] = element;
        }
        return;
}

/*BFS function as described above */


int* BFS(int *list[], int vertex, int visitedList[], int maxVertices){
		/* Set initial vertex to "visited" */
		visitedList[vertex] = 1;
		
		int currentSize = 0;
		
		// printf("\nBFS called on :%d\n", vertex);
		
		/* Create a Queue and place initial vertex on queue*/
		Queue *Q = 	CreateQueue(maxVertices);	
		
		Enqueue(Q, vertex);
		// printf("enqueued! %d\n", vertex);
		
		/*Execute until queue is empty */
		while(Q->size){
			
			/* Pop off the queue */
			
			vertex = Front(Q);
			
			// printf("Visting Vertex #%d\n", vertex);
			
			currentSize = currentSize + 1;

			/* Reduce queue size */
			
			Dequeue(Q);
			
			int i = 0;
			
			/* Retrieve the adjacency list for the vertex retrieved from queue*/
			
			struct list *listptr;
			listptr = (struct list*)malloc(sizeof(struct list*));
			listptr = (struct list*)list[vertex];
			
			// printf("Listptr data: %d\n", listptr->data);
			
			/* Scan the adjacency list for "unvisited" vertices and add them to the queue */
			int vertexAdjustment = 0;
			while(listptr->next !=NULL){ 
			
				vertexAdjustment = listptr->data;
				vertexAdjustment = vertexAdjustment - 1;
				
				if(visitedList[vertexAdjustment] == 0){
					
					visitedList[vertexAdjustment] = 1;
					Enqueue(Q, vertexAdjustment);
				// printf("enqueued! %d\n Size of queue: %d", vertexAdjustment, Q->size);
				}
				
				listptr = listptr->next;
			}
			if(listptr->next == NULL){
			
				vertexAdjustment = listptr->data;
				vertexAdjustment = vertexAdjustment - 1;
				
				if(visitedList[vertexAdjustment] == 0){
					
					visitedList[vertexAdjustment] = 1;
					Enqueue(Q, vertexAdjustment);
					// printf("enqueued! %d\n Size of queue: %d", vertexAdjustment, Q->size);
				}
			}				
		}
		/* Track the smallest component size */
		if(currentSize < smallestComponent){
		
			smallestComponent = currentSize;
		
		}
		
		/* Return the new list of visited vertices */
		
		int* returnptr = visitedList;
		
		return returnptr;
}




int main(int argc, char *argv[])
{
		/* Open file or error out */
	
		FILE * fp;
		if(argc > 1){
			fp = fopen(argv[1],"r");
		}
		else{
			printf("The arguments are invalid: please used ./{programname} {path}");
			return(1);
		}
		int vertices = 0;
		int i = 0;

		/* Grab total number of vertices */
		fscanf(fp,"%d", &vertices);

		smallestComponent = vertices;
		
		// printf("%d\n", vertices);

		/*Create a pointer for each vertex */
		int* ourlist[vertices];


		
		/* Create a linked list for each vertex and reference it by the index*/
		for(i = 0; i < vertices; i++){

			struct list *current;
			struct list *head;

			current = (struct list*)malloc(sizeof(struct list*));
			current->data = 0;
			head = current;
			head->next = NULL;
			ourlist[i] = (int*)head;
		}

		/* Scan the edges and create the adjacency list for each vertex */
		int a = 0;
		int b = 0;
		while(fscanf(fp,"%d %d", &a, &b) != EOF){

			struct list *head;
			struct list *current;
			current = (struct list*)ourlist[a-1];
			if(current->data == 0){
				current->data = b;
				current->next = NULL;
			}
			else{
				head = current;

				struct list *tmp;
				tmp = (struct list*)malloc(sizeof(struct list*));
				tmp->data = b;
				tmp->next = NULL;

				while(current->next != NULL){
					struct list *tmp;
					tmp = current->next;
					current = tmp;
				}

				current->next = tmp;
				current = tmp;
				ourlist[a-1] = (int*)head;
			}
			struct list *head2;
			struct list *current2;
			current2 = (struct list*)ourlist[b-1];
			if(current2->data == 0){
				current2->data = a;
				current2->next = NULL;
				head2 = current2;
				ourlist[b-1] = (int*)head2;
			}
			else{
				head2 = current2;

				struct list *tmp;
				tmp = (struct list*)malloc(sizeof(struct list*));
				tmp->data = a;
				tmp->next = NULL;

				while(current2->next != NULL){
					struct list *temp;
					temp = current2->next;
					current2 = temp;
				}

				current2->next = tmp;
				current2 = tmp;
				ourlist[b-1] = (int* )head2;
			}
		}
		fclose(fp);
		
		/* Create an array to keep track of the "visited" vertices */
		int visited[vertices];
			
		int *visitedptr = visited;
		
		/* Initialize all vertices to be "unvisited" */
	
		for(i = 0; i < vertices; i++){
			visited[i] = 0;
		}
		
		// for(i = 0; i < vertices; i++){
			// printf("%d is adjacent to: ", i+1 );
			// struct list *current;
			// current = (struct list*)malloc(sizeof(struct list*));
			// current = ourlist[i];

			// int plz = current->data;

			// printf("%d", plz);
			// while(current->next != NULL){
			// current = current->next;
			// plz = current->data;
			// printf("\, %d", plz);
			// }
			// printf(" Visited: %d \n", visited[i]);
		// }
		
		/* Keep track of the number of Components */
		
		int numComponents = 0;
		
		/* For each vertex, if "unvisited" -> run BFS on the vertex */
		
		for(i = 0; i < vertices; i++){				
			if(visited[i] == 0){
				
				visitedptr = BFS(ourlist, i, visited, vertices);		
				numComponents = numComponents + 1;
				
			}
		}
		
		printf("******************************************\nNumber of Connected Components is %d      |\n******************************************\n", numComponents);
		printf("The smallest component has %d vertices  |\n******************************************\n", smallestComponent);
		
		return 0;
}
