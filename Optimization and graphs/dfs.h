#ifndef DFS_H_INCLUDED
#define DFS_H_INCLUDED

#include <stdio.h>
#include "graph.h"

/* ****************** */
/* Depth-first search */
/* ****************** */

typedef struct {
	int visited[MAXV];
	int predecessor[MAXV];
} dfs_info;

void initialize_search(graph *g, dfs_info *d_i)
{
  int i;
  for (i = 0; i < g->nvertices; i++) {
    d_i->visited[i]     =  0;
    d_i->predecessor[i] = -1;
  }
  return;
}

void dfs(graph *g, dfs_info *d_i, int start)
{
	d_i->visited[start] = 1;
	int i;
	for (i = 0; i < g->degree[start]; i++) {
		int cell = g->edges[start][i];
		if (d_i->visited[cell]==0) {
			d_i->predecessor[cell] = start;
			dfs(g, d_i, cell);
		}
	}
  return;
}

void print_predecessors(graph *g, dfs_info *d_i)
{
	int i;
  for(i = 0; i < g->nvertices; i++) {
    printf("%d: predecessor[%d] = %d\n", i, i, d_i->predecessor[i]);
  }
	return;
}

void print_visited_vertices(graph *g, dfs_info *d_i)
{
	int i;
  for(i = 0; i < g->nvertices; i++) {
    printf("%d: visited[%d] = %d\n", i, i, d_i->visited[i]);
  }
	return;
}

#endif
