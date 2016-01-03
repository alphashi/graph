#ifndef __READ_FILE_H__
#define __READ_FILE_H__

#include <fstream>

#include "graph.h"


#define READ_FILE_DEBUG false 

class ReadGraph
{
public:
	ReadGraph();
	ReadGraph(std::string fname);
	ReadGraph(std::string fname, Graph* graph);

	std::ifstream ifs;
	Graph* graph;

	int read();
	int readVertex();
	int readAdjMatrix();
	int printGraph(std::string fname);

};




#endif
