#include <fstream>

#include "macro.h"
#include "graph.h"


///use the method of DFS to find a path from vertex v to s 	
int findPathBFP(int v, int s, std::vector<int> &path)
{
	



	return RET_SUCCESS;
}

/// breadth first path
int BFP(int v)
{




	return RET_SUCCESS;
}

	/// breadth first search
int Graph::BFS(int s)
{
	std::set<int> stack;
	std::set<int>::iterator siter;

//	mark[s] = true;
	stack.insert(s);

//	stack.insert(adj_matrix[s].begini(),
//			adj_matrix[s].end());

	while (!stack.empty())
	{
		int v = *(stack.begin());
		stack.erase(stack.begin());

		mark[v] = true;
		for (siter = adj_matrix[v].begin();
				siter != adj_matrix[v].end();
				siter ++)
		{
			if (!mark[*siter])
			{
				v_edges[*siter] = v;
				mark[*siter] = true;
				stack.insert(adj_matrix[*siter].begin(),
						adj_matrix[*siter].end());
			}
		}
	}
	

	return RET_SUCCESS;
}



///use the method of DFS to find a path from vertex v to s 	
int Graph::findPathDFS(int v, int s, std::vector<int> &path)
{

	INF_LOG(GRAPH_DEBUG, "find a path: %d --> %d...\n", v, s);
	// generate the v_edges;
	DFP(v);

	//std::vector<int> path;

	if (v_edges.find(s) == v_edges.end())
	{
		ERROR_LOG("s isn't in the edges, in find the path: v-->s\n");
		return RET_FAILURE;
	}
	
	for (int x = s; x != v; x = v_edges[x])
	{
		INF_LOG(GRAPH_DEBUG, "vertex: %d add to path. \n", x);
		path.push_back(x);
	}

	path.push_back(v);

	return RET_SUCCESS;
}



// depth first paths
int Graph::DFP(int s)
{
	INF_LOG(GRAPH_DEBUG, "DFP...\n");
	mark.reset();
	v_edges.clear();
	v_path.clear();
	
	BFS(s);

	INF_LOG(GRAPH_DEBUG, "END DFP...\n");
	return RET_SUCCESS;
}


// depth first search
int Graph::DFS(int v)
{
	
	INF_LOG(GRAPH_DEBUG, "DFS...\n");
	INF_LOG(GRAPH_DEBUG, "searching for vertex: %d\n", v);

	mark[v] = true;

	std::set<int> adj_set = adj_matrix[v];
	std::set<int>::iterator siter;

	if (adj_set.empty())
	{
		INF_LOG(GRAPH_DEBUG, "vertex: %d ,adjoin set is empty.\n", v);
		return RET_SUCCESS;
	}


	for (siter = adj_set.begin();
			siter != adj_set.end();
			siter ++)
	{
		if (!mark[*siter])
		{
			INF_LOG(GRAPH_DEBUG, "add vertex: %d --> %d\n", *siter, v);
			v_edges[*siter] = v;
			DFS(*siter);
		}
	}


	INF_LOG(GRAPH_DEBUG, "END DFS...\n");
	return RET_SUCCESS;
}



int Graph::printDot(std::ofstream &ofs)
{
	ofs << "digraph G{" << std::endl;


	std::map<int, std::set<int> >::iterator miter;
	std::set<int>::iterator siter;

	INF_LOG(GRAPH_DEBUG, "Print Dot...\n");
	
	// vertex
	INF_LOG(GRAPH_DEBUG, "print vertex.\n");
	for (siter = vertex.begin();
			siter != vertex.end();
			siter ++)
	{
		ofs << *siter << ";" << std::endl;
	}

	INF_LOG(GRAPH_DEBUG, "vertex END.\n");


	// edges
	INF_LOG(GRAPH_DEBUG, "print edges.\n");
	for (miter = adj_matrix.begin();
			miter != adj_matrix.end();
			miter ++)
	{
		std::set<int> vertexs = adj_matrix[miter->first];

		for (siter = vertexs.begin();
				siter != vertexs.end();
				siter ++)
		{
			ofs << miter->first << " -> "
				<< *siter << ";" << std::endl;
		}
	}
	
	INF_LOG(GRAPH_DEBUG, "edges END.\n");


	ofs << "}" << std::endl;


	return RET_SUCCESS;
}
