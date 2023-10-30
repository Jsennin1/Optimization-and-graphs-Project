#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

/* ************* */
/* main function */
/* ************* */

int main(int argc, char* argv[])
{
	int x, y; 		/* vertices */
	int i, k;
	FILE *fp;
	graph *g;
  fp = fopen(argv[1], "r"); 
  if(fp == NULL) {
  	fprintf(stderr, "File open failed\n");
    fclose(fp);
  	return 0;
  }
	g = (graph*)malloc(sizeof(graph));
  read_graph(fp, g);
  fclose(fp);

	for(k = 0; k < 4; k++) {
		switch (k) {
		case 0:
			break;
		case 1:
			printf("***** insert an edge (input two numbers): \n");
			scanf("%d %d", &x, &y);
			insert_edge(g, x, y);
			break;
		case 2:
			printf("***** remove an edge (input two numbers): \n");
			scanf("%d %d", &x, &y);
			remove_edge(g, x, y);
			break;
		case 3:
			printf("***** reorient an edge (input two numbers): \n");
			scanf("%d %d", &x, &y);
			reorient_edge(g, x, y);
			break;
		default:
			break;
		}
		print_graph(g);
		for(i = 0; i < g->nvertices; i++) {
			printf("degree[%d}: %d\n", i, g->degree[i]);
		}
		printf("nedges = %d\n", g->nedges);
	}

	free(g);
	return 0;
}
