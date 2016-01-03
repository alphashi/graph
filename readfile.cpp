#include <iostream>
#include <string>

#include "macro.h"
#include "local_const.h"
#include "readfile.h"

//#define READFILE_DEBUG true


ReadGraph::ReadGraph(std::string fname)
: graph(NULL)
{
	ifs.open(fname.c_str());

	if (!ifs.good())
	{
		ERROR_LOG("open file failed... \n");
	}

	graph = new Graph();
}



ReadGraph::ReadGraph(std::string fname, Graph* _graph)
: graph(_graph)
{
	ifs.open(fname.c_str());

	if (!ifs.good())
	{
		ERROR_LOG("open file failed... \n");
	}

}



int ReadGraph::read()
{
	std::string line;

	while(!ifs.eof())
	{
		getline(ifs, line);
	
		//std::cout << "top line: " << line << std::endl;
		if (line == "vertex")
		{
			INF_LOG(READ_FILE_DEBUG, "read vertex...\n");
			readVertex();
		}
		else if (line == "edges")
		{
			INF_LOG(READ_FILE_DEBUG, "read edges...\n");
			readAdjMatrix();
		}
		else if (line == " \n" || line == "\n" || line == "\r\n")
		{
			continue;
		}
		else
		{
			continue;
			ERROR_LOG("graph file format error...\n");

			return RET_FAILURE;
		}
	}

	return RET_SUCCESS;
}


int ReadGraph::readVertex()
{
	std::string line;

	getline(ifs, line);

	INF_LOG(READ_FILE_DEBUG, "LINE: %s \n", line.c_str()); 

	if (line == "{")
	{

		int index_b = 0;
		int index_e = 0;
		int end = 0;

		while(!ifs.eof())
		{
			getline(ifs, line);

			if (line == "}")
			{
				break;
			}
			INF_LOG(READ_FILE_DEBUG, "LINE: %s \n", line.c_str()); 
			
			end = line.find(";");
			INF_LOG(READ_FILE_DEBUG, "find [;] at: %d \n", end);

			index_e = line.find(",");
			INF_LOG(READ_FILE_DEBUG, "find [,] at: %d \n", index_e);
		

			while (index_e != -1)
			{
				std::string str_id = line.substr(index_b, index_e-index_b);
			//	line = line.substr(index_e+1);


				INF_LOG(READ_FILE_DEBUG, "vertex_s is: %s \n", str_id.c_str());
				
				int v_id = atoi(str_id.c_str());
				INF_LOG(READ_FILE_DEBUG, "vertex_d is: %d \n", v_id);
				
				graph->vertex.insert(v_id);
			
//				std::cout << "new line: " << line << std::endl;
				index_b = index_e + 1;
				index_e = line.find(",", index_b);

				INF_LOG(READ_FILE_DEBUG, "find [,] at: %d \n", index_e);
			}

			std::string str_id = line.substr(index_b, end-index_b);
			int v_id = atoi(str_id.c_str());
			INF_LOG(READ_FILE_DEBUG, "vertex_d is: %d \n", v_id);
			
			graph->vertex.insert(v_id);
		}

	}

	return RET_SUCCESS;
}



int ReadGraph::readAdjMatrix()
{
	std::string line;

	getline(ifs, line);

	INF_LOG(READ_FILE_DEBUG, "LINE: %s \n", line.c_str()); 

	if (line == "{")
	{

		int index_b = 0;
		int index_e = 0;
		int end = 0;

		while(!ifs.eof())
		{
			getline(ifs, line);

			if (line == "}")
			{
				break;
			}
			INF_LOG(READ_FILE_DEBUG, "LINE: %s \n", line.c_str()); 
			
			index_b = line.find(":");
			INF_LOG(READ_FILE_DEBUG, "find [:] at: %d \n", index_b);

			int v_begin = atoi(line.substr(0,index_b).c_str());
			
			index_b = line.find(">");
			INF_LOG(READ_FILE_DEBUG, "find [>] at: %d \n", index_b);
	
			index_e = line.find(";");
			int v_end = atoi(line.substr(index_b+1, index_e-index_b).c_str());

			if (graph->vertex.find(v_begin) == graph->vertex.end()
					|| graph->vertex.find(v_end) == graph->vertex.end())
			{
				ERROR_LOG("the vertex is not in the set. \n");
				
				return RET_FAILURE;
			}


			INF_LOG(READ_FILE_DEBUG, "find edge: %4d --> %4d \n", v_begin, v_end);

			graph->adj_matrix[v_begin].insert(v_end);
		}
	}

	return RET_SUCCESS;
}


