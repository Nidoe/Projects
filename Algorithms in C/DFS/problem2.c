/*
Name: Luv Somani
Pawprint: lrsfh3
Programming Assignment #2
*/
#include <stdio.h>
#include <stdlib.h>

struct list{

    int data;

    struct list *next;

}list;

typedef struct Vertex{
	
	int data;
	
	int visited;

	int* listPtr;
	
	int root;
	
} Vertex;


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
/* Global Variables */

Queue *Q;
int rootofComponent = NULL;

/* Recursive DFS which takes in an index and an array of vertices, Queue's each of the vertices as they finish*/ 
void DFS(int index,int* vList[]){
	struct Vertex *temp;
	
	temp = (struct Vertex*)malloc(sizeof(struct Vertex*));
		
	temp = vList[index];
	
	temp->visited = 1;
	
	struct list *current;
	current = (struct list*)malloc(sizeof(struct list*));
	current = (struct list*)temp->listPtr;
	if(current->data != NULL){
		while(current->next != NULL){	
			temp = vList[current->data];	
			if(temp->visited == 0){
				DFS(current->data, vList);
			}
			current = current->next;
			
		}
		if(current->next == NULL){
			temp = vList[current->data];
			if(temp->visited == 0){
				DFS(current->data, vList);
			}
		}
	}
	temp = vList[index];
	temp->root = rootofComponent;
	
	Enqueue(Q, index);
	
	vList[index] = temp;
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

		
		// printf("%d\n", vertices);

		/*Create a pointer for each vertex */
		int* ourlist[vertices];
		int* reverselist[vertices];

		
		/* Create two linked lists for each vertex and reference it by the index : G and G-Transpose*/
		for(i = 0; i < vertices; i++){

			struct list *current;
			struct list *head;
			struct list *reverse;

			current = (struct list*)malloc(sizeof(struct list*));
			reverse = (struct list*)malloc(sizeof(struct list*));
			current->data = 0;
			reverse->data = 0;
			head = current;
			head->next = NULL;
			ourlist[i] = (int*)head;
			
			head = reverse;
			head->next = NULL;
			reverselist[i] = (int*)head;
			
		}

		/* Scan the edges and create the adjacency list for each vertex */
		int a = 0;
		int b = 0;
		while(fscanf(fp,"%d %d", &a, &b) != EOF){

			struct list *head;
			struct list *current;
			struct list *reverse;
			current = (struct list*)ourlist[a-1];
			reverse = (struct list*)reverselist[b-1];
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
			if(reverse->data == 0){
				reverse->data = a;
				reverse->next = NULL;
			}
			else{
				head = reverse;
				struct list *tmp;
				tmp = (struct list*)malloc(sizeof(struct list*));
				tmp->data = a;
				tmp->next = NULL;
				
				while(reverse->next != NULL){
					struct list *tmp;
					tmp = reverse->next;
					reverse = tmp;
				}
				
				reverse->next = tmp;
				reverse = tmp;
				reverselist[b-1] = (int*)head;
			}
		}
		fclose(fp);
		
		
		
			
		int* vertexList[vertices];
		/*Initialize all of the vertices and store all of them in an array of pointers*/
		for(i = 1; i <= vertices; i++){
			struct Vertex *newVertex;
			
			newVertex = (struct Vertex*)malloc(sizeof(struct Vertex*));
			
			newVertex->data = i;
			
			newVertex->visited = 0;
			
			newVertex->listPtr = ourlist[i-1];
			
			vertexList[i] = (int*)newVertex;
					
		}
		
		
		/*Initialize the global Queue based on number of vertices*/
		Q = CreateQueue(vertices);
		
		/*Run DFS G */
		
		for(i = 1; i<= vertices; i++){
			struct Vertex *temp;
			
			temp = (struct Vertex*)malloc(sizeof(struct Vertex*));
			
			temp = vertexList[i];
			
						
			if(temp->visited == 0){
			 	DFS(i, vertexList); 
			}
			
		}
		
		/*Reset each vertex after first pass and set it's adjacency list to the reverse of G*/
		
		for(i = 1; i<= vertices; i++){
			struct Vertex *temp;
			
			temp = (struct Vertex*)malloc(sizeof(struct Vertex*));
			
			temp = vertexList[i];
			
			temp->listPtr = reverselist[i-1];
			temp->visited = 0;
						
			vertexList[i] = temp;
		}
		
		
		/*Create the order of vertices for the second pass by storing the Queue in reverse*/
		int* order[vertices];
		for(i = vertices; i>0; i--){
			int item = Front(Q);			
			Dequeue(Q);
			
			order[i] = item;
			
			
			
		}
		
		
		/* Track the number of components/roots */
		int numRoots=0;
		/*Run DFS on G-transpose using the reverse of the Queue order */
		for(i = 1; i<= vertices; i++){
			
			int index = order[i];
			struct Vertex *temp;
			
			temp = (struct Vertex*)malloc(sizeof(struct Vertex*));
			
			temp = vertexList[index];
			
			/* Update the global index of the root vertex */
			rootofComponent = index;
			
			if(temp->visited == 0){
					/*Each iteration will result in a SCC with root node stored*/
					numRoots++;
					DFS(index, vertexList);
			}
		}
	
	
		/*Create a linked list for each component based on the root*/
		int* componentList[vertices];
		for(i = 0; i<= vertices; i++){
			struct list *tmp;
			struct list *head;
			tmp = (struct list*)malloc(sizeof(struct list*));

			tmp->data = 0;
			tmp->next = NULL;
			
			head = tmp;
			componentList[i] = (int*)head;
			
		}
		
		/*Store the size and value of each component */
		int size = 0;
		int rootptr[numRoots];
		int rootsize[numRoots];
		for(i=1; i <= vertices; i++){
			struct Vertex *temp;
			
			temp = (struct Vertex*)malloc(sizeof(struct Vertex*));
			temp = vertexList[i];
			
			int root = temp->root;

			struct list *head;
			head = (struct list*)componentList[root];
			
			if(head->data == 0){
				struct list *tmp;
				tmp = (struct list*)malloc(sizeof(struct list*));
				tmp->data = i;
				tmp->next = NULL;
				head = tmp;
				componentList[root] = (int*) head;
				size = size + 1;
				rootptr[size] = root;
				rootsize[size] = 1;
			}
			else{
				struct list *tmp;
				struct list *current;
				tmp = (struct list*)malloc(sizeof(struct list*));
				tmp->data = i;
				tmp->next = NULL;
				current = head;
				while(current->next != NULL){
					struct list *tmp2;
					tmp2 = (struct list*)malloc(sizeof(struct list*));
					tmp2 = current->next;
					current = tmp2;
				}
				rootsize[size] = rootsize[size] + 1;
				current->next = tmp;
				current = tmp;		
				componentList[root] = (int*) head;
			}
			
		}
	
		/*Reset the vertex edges back to original G*/
		for(i = 1; i<= vertices; i++){
			struct Vertex *temp;
			
			temp = (struct Vertex*)malloc(sizeof(struct Vertex*));
			
			temp = vertexList[i];
			
			temp->listPtr = ourlist[i-1];
			
			vertexList[i] = temp;
		}
		/*Create a matrix to keep track of edges between components */
		int incidenceMatrix[numRoots][numRoots];
		
		
		int j = 0;
		/* Initialize the matrix */
		for(i=1; i<=numRoots; i++){
			for(j=1; j<=numRoots; j++){
				incidenceMatrix[i][j] = 0;
			}
		}
		/*Runtime variable to roughly estimate efficiency of this section of the algorithm*/
		int runtime = 0;
		for(i=1; i<=numRoots; i++){
			for(j=1; j<=numRoots; j++){
				
				/*If Component[i]-> Component[j] == 0*/
		
				if(incidenceMatrix[i][j] == 0 && i != j){
					runtime = runtime + 1;
					struct list *current;
					int root1;
					int root2;
					int n;
					current = (struct list*)malloc(sizeof(struct list*));
					current = (struct list*)componentList[rootptr[i]];
					
					/*While loop to break if edge between components is found */
					while(incidenceMatrix[i][j] == 0){
						if(current->data != NULL){
							
							/*Scan each vertex from Component[i]*/
							
							
							while(current->next != NULL){	
								runtime = runtime + 1;
								
								n = current->data;
								
								struct Vertex *v;
								v = (struct Vertex*)malloc(sizeof(struct Vertex*));
								v = vertexList[n];
								
								root1 = v->root;
								
								//printf("Vertex %d\n", n);
								
								/*Scan through the vertices adjacent to vertex v in Component[i]*/
								struct list *adjList;
								adjList = (struct list*)malloc(sizeof(struct list*));
								
								adjList = (struct list*)v->listPtr;
								
								if(adjList->data != NULL){
									while(adjList->next != NULL){	
									
										v = vertexList[adjList->data];	
										root2 = v->root;
										
										runtime = runtime + 1;
									
										/*If an edge between vertex v in Component[i] has an edge to vertex u in Component[j], we have found our edge and break from loop */
										
										if(root1 == rootptr[i] && root2 == rootptr[j]){
											
											incidenceMatrix[i][j] = 1;
											break;
										}
										
										adjList = adjList->next;							
									}
									if(adjList->next == NULL){
										
										v = vertexList[adjList->data];	
										root2 = v->root;
										
										runtime = runtime + 1;
														
										if(root1 == rootptr[i] && root2 == rootptr[j]){
											incidenceMatrix[i][j] = 1;
											break;
										}
									}
								}
								current = current->next;
							}
							/*Considering all cases*/
							if(current->next == NULL){
								runtime = runtime + 1;
								n = current->data;
								struct Vertex *v;
								v = (struct Vertex*)malloc(sizeof(struct Vertex*));
								v = vertexList[n];
								root1 = v->root;								
								struct list *adjList;
								adjList = (struct list*)malloc(sizeof(struct list*));
								adjList = (struct list*)v->listPtr;
								
								if(adjList->data != NULL){
									while(adjList->next != NULL){	
										v = vertexList[adjList->data];	
										root2 = v->root;
										
										runtime = runtime + 1;
																				
										if(root1 == rootptr[i] && root2 == rootptr[j]){
												incidenceMatrix[i][j] = 1;
												break;
										}
										adjList = adjList->next;							
									}
									if(adjList->next == NULL){
										
										v = vertexList[adjList->data];	
										root2 = v->root;
										
										runtime = runtime + 1;
										
										if(root1 == rootptr[i] && root2 == rootptr[j]){
											incidenceMatrix[i][j] = 1;
											break;
										}
									}
								}
								break;
							}
						}
						
					}
					
				}
			}
		}
		
		
		int edges = 0;
		int degreeMax = 0;
		int degreeMin = vertices;
		int currentdegree = 0;
		
		/*Gather our data from the matrix*/
		for(i=1; i <= numRoots; i++){
			for(j=1; j<=numRoots; j++){
				if(incidenceMatrix[i][j] == 1){
					edges = edges + 1;
					currentdegree = currentdegree + 1;
				}
			}
			if(currentdegree > degreeMax){
				degreeMax = currentdegree;
			}
			if(currentdegree <= degreeMin){
				degreeMin = currentdegree;
			}
			currentdegree = 0;
		}
		printf("Number of Components: %d\n", numRoots);
		printf("Number of Edges between Components: %d\n", edges);
		printf("Smallest Degree: %d\n", degreeMin);
		printf("Largest Degree: %d\n", degreeMax);
		
		printf("/* Runtime:  %d */\n", runtime);
		
	
		
}
