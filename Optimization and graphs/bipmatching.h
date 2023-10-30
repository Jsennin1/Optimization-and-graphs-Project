#ifndef BIPMATCHING_H_INCLUDED
#define BIPMATCHING_H_INCLUDED

#include "dfs.h"

/* ************************** */
/* maximum-matching algorithm */
/* ************************** */

void construct_digraph_for_matching(graph* g)
{
	int i, source, sink;
	source = g->nvertices; insert_vertex(g);
	sink = g->nvertices; insert_vertex(g);
	for (i = 0; i < g->nvertices - 2; i++) {
		if (g->degree[i] == 0) insert_edge(g, i, sink);
		else                insert_edge(g, source, i);
	}
	return;
}


void augment(graph* g, dfs_info* d_i, graph* matching, int start, int end)
{
	int v = end;
	int p = d_i->predecessor[v];
	while (v != start)
	{
		if (is_edge(matching, v, p))
			remove_edge(matching, v, p);
		else if (is_edge(matching, p, v))
			remove_edge(matching, p, v);
		else {
			insert_edge(matching, p, v);
		}
		reorient_edge(g, p, v);

		v = p;
		p = d_i->predecessor[v];

	}

	return;
}

int find_maximum_matching(graph* g, graph* matching)
{
	int size = 0;			/* the size of a current matching */
	int source, sink;
	dfs_info* d_i;

	source = g->nvertices - 2;
	sink = g->nvertices - 1;
	d_i = (dfs_info*)malloc(sizeof(dfs_info));
	initialize_search(g, d_i);
	dfs(g, d_i, source);
	if (d_i->visited[sink] != 1)
		return size;
	while (d_i->visited[sink]) {
		augment(g, d_i, matching, source, sink);
		initialize_search(g, d_i);
		dfs(g, d_i, source);
		size++;
	}
	print_graph(matching);

	return size;
}

#endif
