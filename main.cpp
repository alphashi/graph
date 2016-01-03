#include <iostream>
#include <string>


#include "macro.h"
#include "readfile.h"


using namespace std;


void printVector(vector<int> array)
{
	vector<int>::iterator iter;

	cout << "The array is: " << endl;
	for (iter = array.begin();
			iter != array.end();
			iter ++)
	{
		cout << *iter << "	";

	}

	cout << endl;

}


int main()
{
	//string ifname = "graph.data_bak";
	string ifname = "graph.data";
	Graph* graph = new Graph();
	
	ReadGraph rgraph(ifname, graph);
	rgraph.read();

	string ofname = "graph.dot";
	ofstream ofs(ofname.c_str());

	if (!ofs.good())
	{
		ERROR_LOG("open file failed... \n");

	}

	graph->printDot(ofs);
	ofs.close();


//	graph->DFS(7);
//	cout << "can accept node is: " << endl;
//	cout << graph->mark << endl;
	
	vector<int> path;

	graph->findPath(1, 10, path);
	printVector(path);
	

	return 0;
}




