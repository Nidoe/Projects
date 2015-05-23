/*Luv Somani
  Problem 3
  CS3050
*/
/* Main algorithm:
	
   For each vertex, set size to 1 and parent to itself.
   
   As we scan the list of edges,
   
   for each edge u->v, if the parent of u is not equal to the parent of v{
		if(size[parent[u]] >= size[parent[v]]){
			size[parent[u]] = size[u] + size[parent[v]]
			parent[v] = parent[u]
			reset size of parent[v]
		}
		else{
			size[parent[v]] = size[v] + size[parent[u]]
			parent[u] = parent[v]
			reset size of parent[u]
		} 
   }
*/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	
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

	int size[vertices];
	int parentList[vertices];
	
	for(i=1; i <= vertices; i++){
		size[i] = 1;
		parentList[i] = i;
	}
	
	int u = 0;
	int v = 0;
	
	
	while(fscanf(fp,"%d %d",&u,&v) != EOF){
		if(parentList[u] != parentList[v]){
			if(size[parentList[u]] >= size[parentList[v]]){
				size[parentList[u]] += size[parentList[v]];
				size[parentList[v]] = 1;
				parentList[v] = parentList[u];
			}
			if(size[parentList[u]] < size[parentList[v]]){
				size[parentList[v]] += size[parentList[u]];
				size[parentList[u]] = 1;
				parentList[u] = parentList[v];
			}
		}	
	}
	/*Read through each vertex, if the size is greater than 1, we know it's a component */
	int minSize = vertices;
	int numberofComponents = 0;
	for(i=1; i<= vertices; i++){
		if(size[i] != 1){
			numberofComponents++;
			if(size[i] < minSize){
				minSize = size[i];
			}
		}
		if(size[i] == 1 && parentList[i] == i){
			numberofComponents++;
			minSize = 1;
		}
	}
	
	printf("Number of components is %d and the minimum size is %d\n", numberofComponents, minSize);
		
}
