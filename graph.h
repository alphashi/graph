#ifndef __GRAPH_H__

#define __GRAPH_H__


#include <iostream>
#include <set>
#include <map>
#include <vector>
#include <bitset>

#include "local_const.h"

#define GRAPH_DEBUG true



class Graph
{
public:

	int num_v;
	int num_e;

	std::bitset<MAX_VERTEX_NUM> mark;

	std::set<int> vertex;
	std::map<int, std::set<int> > adj_matrix;
	
	std::map<int, int> v_edges;
	std::vector<int> v_path;

	///use the method of DFS to find a path from vertex v to s 	
	int findPathBFP(int v, int s, std::vector<int> &path);

	/// breadth first path
	int BFP(int v);

	/// breadth first search
	int BFS(int s);


	///use the method of DFS to find a path from vertex v to s 	
	int findPathDFS(int v, int s, std::vector<int> &path);

	/// depth first path
	int DFP(int s);

	/// depth first search
	int DFS(int v);

	int printVertex();
	int printEdge();

	int printDot(std::ofstream &ofs);
};




#endif
