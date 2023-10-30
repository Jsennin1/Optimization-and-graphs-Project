#include <stdio.h>
#include <stdlib.h>
#include "dfs.h"

int main(int argc, char* argv[])
{
  FILE *fp;
	graph *g;
	dfs_info *d_i;
  fp = fopen(argv[1], "r"); 
  if(fp == NULL) {
    fprintf(stderr, "File open failed\n");
    fclose(fp);
    return 0;
  }
	g = (graph*)malloc(sizeof(graph));
	d_i = (dfs_info*)malloc(sizeof(dfs_info));
  read_graph(fp, g);
  fclose(fp);
  
  initialize_search(g, d_i);
  dfs(g, d_i, 0);
	print_predecessors(g, d_i);
	print_visited_vertices(g, d_i);
	free(g);
	free(d_i);
  return 0;
}
