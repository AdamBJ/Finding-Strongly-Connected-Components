#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "QuickSort.h"

using namespace std;

bool ReadFile(vector<int> graph[], vector<int> reversedGraph[], string fileName);
void DFSLoop_rGraph(vector<int> rGraph[], vector<int>& orderingVector, const int NO_VERTS);
void DFS_rGraph(vector<int> rGraph[], vector<int>& orderingVector, int startVertex);
void FindSCC(vector<int> graph[], vector<int> magicOrdering, vector<int>& SCC_sizes, const int NUM_VERTS);
void DFS_graph(vector<int> graph[], int startVertex, int& SCC_size);

int main(){
	const int NUM_VERTS = 875714;
	//create graph and reversedGraph from .txt file
	
	//create the arrays on the heap. Too big for the stack.
	vector<int>* graph = new vector<int>[NUM_VERTS + 1];//+1 because we want graph[1] to store data for the vector labelled '1'.
	vector<int>* reversedGraph = new vector<int>[NUM_VERTS + 1];

	for (int i = 1; i < NUM_VERTS + 1; i++){
		graph[i].reserve(10);
		reversedGraph[i].reserve(10);
		graph[i].push_back(0);
		reversedGraph[i].push_back(0);
	}

	bool success = ReadFile(graph, reversedGraph, "SCC.txt");
	if (!success) return 0;

	//run DFSLoop_rGraph on reversedGraph to create the "magic ordering" we will use to find the SCCs.

	vector<int> magicOrdering; //magicOrdering[0] is the first vertex we target when we run FindSCCs.
	DFSLoop_rGraph(reversedGraph, magicOrdering, NUM_VERTS);//create the magic ordering. Pass magicOrdering in by reference.

	//run FindSCCs on the normal graph. Return a vector containing the SCC sizes.
	vector<int> SCC_sizes;
	FindSCC(graph, magicOrdering, SCC_sizes, NUM_VERTS);

	//sort the vector so we know what the 5 largest SCCs are. Print the sizes.
	int numSCC = SCC_sizes.size();
	QuickSort(SCC_sizes, 0, numSCC - 1);
	if (numSCC >= 5){
		for (int i = numSCC - 1; i > numSCC - 6; i--){
			cout << SCC_sizes[i] << " ";
		}
	}
	else {
		for (int i = numSCC - 1; i >= 0; i--){
			cout << SCC_sizes[i] << " ";
		}
	}
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
			graph[i].push_back(j);
			reversedGraph[j].push_back(i);
		}
		adjList_txt.close();
		return true;
	}
}

/*Creates the magic ordering that will be used to peel-off SCC. Relies on the helper function DFS_rGraph to perform the DFSs that generate the ordering.*/
void DFSLoop_rGraph(vector<int> rGraph[], vector<int>& orderingVector, const int NO_VERTS) {
	for (int i = NO_VERTS; i > 0; i--){//for every vertex
		if (rGraph[i][0] == 0){ //0 if not explored, 1 if explored
			DFS_rGraph(rGraph, orderingVector, i);
		}
	}
}

void DFS_rGraph(vector<int> rGraph[], vector<int>& orderingVector, int startVertex){
	rGraph[startVertex][0] = 1;//mark explored
	int head;
	for (int i = rGraph[startVertex].size()-1; i > 0; i--){
		head = rGraph[startVertex][i];
		if (rGraph[head][0] == 0){//if the head node of the edge currently under consideration hasn't been explored, DFS on it
			DFS_rGraph(rGraph, orderingVector, head);
		}
	}
	orderingVector.push_back(startVertex);
}

void FindSCC(vector<int> graph[], vector<int> magicOrdering, vector<int>& SCC_sizes, const int NUM_VERTS){
	int SCC_size = 0;
	for (int i = NUM_VERTS-1; i >= 0; i--){
		int currVertex = magicOrdering[i];
		if (graph[currVertex][0] == 0){
			DFS_graph(graph, currVertex, SCC_size);
			SCC_sizes.push_back(SCC_size);
			SCC_size = 0;
		}
	}
}

void DFS_graph(vector<int> graph[], int startVertex, int& SCC_size){
	graph[startVertex][0] = 1;//mark explored
	SCC_size++;
	int head;
	for (int i = graph[startVertex].size() - 1; i > 0; i--){
		head = graph[startVertex][i];
		if (graph[head][0] == 0){//if the head node of the edge currently under consideration hasn't been explored, DFS on it
			DFS_graph(graph, head, SCC_size);
		}
	}
}