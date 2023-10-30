#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "graph_param.h"


/* *************** */
/* graph structure */
/* *************** */

typedef struct {
	int edges[MAXV][MAXDEGREE];	/* adjacency info */
	int degree[MAXV];		/* outdegree of each vertex */
	int nvertices;			/* number of vertices in the graph */
	int nedges;			/* number of edges in the graph */
} graph;

/* ****************************** */
/* functions for graph operations */
/* ****************************** */

void initialize_graph(graph* g)
{
	int i;
	g->nvertices = 0;
	g->nedges = 0;
	for (i = 0; i < MAXV; i++) {
		g->degree[i] = 0;
	}
	return;
}

void insert_vertex(graph* g)
{
	g->nvertices++;
	if (g->nvertices > MAXV)
		fprintf(stderr, "Warning: insertion exceeds max number of vertices\n");
	return;
}

int is_edge(graph* g, int x, int y)
{
	int i;
	for (i = 0; i < g->degree[x]; i++) {
		if (g->edges[x][i] == y) {
			return 1;
		}
	}
	return 0;
}

void insert_edge(graph* g, int x, int y)
{
	if (is_edge(g, x, y)) {
		fprintf(stderr, "Warning: (%d, %d) already exists, no insertion is performed\n", x, y);
	}
	else {
		if (g->degree[x] >= MAXDEGREE) {
			fprintf(stderr, "Warning: insertion(%d, %d) exceeds max degree\n", x, y);
		}
		g->edges[x][g->degree[x]] = y;
		g->degree[x] ++;
		g->nedges++;
	}
	return;
}

void read_graph(FILE* fp, graph* g)
{
	int i;
	int m;
	int x, y;

	initialize_graph(g);

	fscanf(fp, "%d %d\n", &(g->nvertices), &m);

	for (i = 0; i < m; i++) {
		fscanf(fp, "%d %d\n", &x, &y);
		insert_edge(g, x, y);
	}

	return;
}

void remove_edge(graph* g, int x, int y)
{
	if (!is_edge(g, x, y)) {
		fprintf(stderr, "Warning: (%d, %d) does not exists, no removing is performed\n", x, y);
	}
	else {
		int i;
		int found = 0;
		for (i = 0; i < g->degree[x]; i++) {
			if (g->edges[x][i] == y) {
				found = 1;
			}
			if (found && i + 1 < g->degree[x])
				g->edges[x][i] = g->edges[x][i + 1];
		}
		g->degree[x]--;
		g->nedges--;
	}
}

void reorient_edge(graph* g, int x, int y)
{
	if (!is_edge(g, x, y)) {
		fprintf(stderr, "Warning: (%d, %d) does not exists, no reorientation is performed\n", x,y);
		return;
	}
	if (is_edge(g, y,x)) {
		fprintf(stderr, "Warning: (%d, %d) already exists, no reorientation is performed\n", y,x);
		return;
	}

	remove_edge(g, x, y);
	insert_edge(g, y, x);
}

void print_graph(graph* g)
{
	int i, j;

	for (i = 0; i < g->nvertices; i++) {
		printf("%d:", i);
		for (j = 0; j < g->degree[i]; j++) {
			printf(" %d", g->edges[i][j]);
		}
		printf("\n");
	}
	return;
}

#endif
