#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
//#include "QuickSort.cpp"

using namespace std;

bool ReadFile(vector<int> graph[], vector<int> reversedGraph[], string fileName);
void DFSLoop_rGraph(vector<int> rGraph, int* orderingArray);

int main(){
	
	vector<int> test(10);
	const int NUM_VERTS = 875714;
	//create graph and reversedGraph from .txt file
	
	//create the arrays on the heap. Too big for the stack.
	vector<int>* graph = new vector<int>[NUM_VERTS + 1]();//+1 because we want graph[1] to store data for the vector labelled '1'.
	vector<int>* reversedGraph = new vector<int>[NUM_VERTS + 1];

	//for (int i = 1; i < NUM_VERTS + 1; i++){
	//	reversedGraph[i].push_back(0);
	//	graph[i].push_back(0);
	//}

	bool success = ReadFile(graph, reversedGraph, "SCC.txt");
	if (!success) return 0;
	std::vector<int> *t = &graph[0];
	std::vector<int> *p = &reversedGraph[0];

	//run DFSLoop_rGraph on reversedGraph to create the "magic ordering" we will use to find the SCCs.

	int* magicOrdering = new int[NUM_VERTS]; //magicOrdering[0] is the first vertex we target when we run FindSCCs.
	//DFSLoop_rGraph(reversedGraph, magicOrdering);

	//run FindSCCs on the normal graph. Return a vector containing the SCC sizes.
	//vector<int> SCC_sizes = FindSCC(graph, magicOrdering);

	//sort the vector so we know what the 5 largest SCCs are. Print the sizes.
	////int numSCC = SCC_sizes.size();
	//QuickSort(SCC_sizes, 0, numSCC - 1);
	//for (int i = numSCC - 1; i > numSCC - 6; i--){
	//	cout << SCC_sizes[i] << " ";
	//}
	
	//we don't have to delete our graphs, once the program exits the memory will be freed. If we were running this program continously we'd have to be
	//wary of memory leaks though.
	return 0;
}

/*
Reads in a series of edges from a text file. Creates an adjacency list representing the graph: one for the normal graph and one for
a reversed version of the graph. Remember arrays are passed by reference so we don't need to return anything.
@param graph: the adj list we will be building for the normal graph
@param reversedGraph: the adj list we will be building for the reversed graph
*/
bool ReadFile(vector<int> graph[], vector<int> reversedGraph[], string fileName) {
	std::ifstream adjList_txt(fileName);

	if (!adjList_txt.is_open()) {
		std::cout << "Failed to open file.";
		return false;
	}
	else {
		int i, j;
		while (adjList_txt >> i >> j){
			--i; --j;
			graph[i].push_back(j);
			//reversedGraph[j].push_back(i);
		}
		//// Safely use the file stream
		//std::string line;
		//int vertex;
		//int vertices[2];

		//while (std::getline(adjList_txt, line))
		//{
		//	std::istringstream iss(line);
		//	//we will parse out two ints, the head and tail vertices. First entry in line is the tail, ie 2 7: 2 = tail. Edge is 2 -> 7. Reverse edge for rGraph.
		//	for (int i = 0; i < 2; i++){
		//		iss >> vertex;
		//		vertices[i] = vertex;
		//	}

		//	graph[vertices[0]].push_back(vertices[1]);//create edge in graph from tail to head: 2 7? 2->7
		//	reversedGraph[vertices[1]].push_back(vertices[0]);//create edge in opposite direction for the r graph: 2 7? 7->2
		//}
		adjList_txt.close();
		return true;
	}
}

void DFSLoop_rGraph(vector<int> rGraph, int* orderingArray) {

}
/*
for (int i = 1; i <= 20; i++){
	cout << i << ": ";
	for (int j = 0; j < graph[i].size(); j++){
		cout << graph[i][j] << " ";
	}
	cout << '\n';
}

for (int i = 1; i <= 20; i++){
	cout << i << ": ";
	for (int j = 0; j < reversedGraph[i].size(); j++){
		cout << reversedGraph[i][j] << " ";
	}
	cout << '\n';
}
*/
