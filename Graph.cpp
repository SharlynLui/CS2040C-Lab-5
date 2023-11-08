#include "Graph.h"
//uncomment this to include your own "heap.h"
//we will assume that you use the same code in your previous assignment
#include "heap.h"

std::ostream& operator<<(std::ostream& os, nodeWeightPair const& n) {
	return os << " (idx:" << n._node << " w:" << n._weight << ")";
}




Graph::Graph(int n)
{
	_al = new List<nodeWeightPair> [n];
	_nv = n;
}

//to help convert max heap to min heap
int negative(int value) {
	return -value;
}

//print Path of sssp
void printPath(int s, int d, int* pathArray) {
	if (s == d) {
		cout << s << " ";
	}
	else {
		printPath(s, pathArray[d], pathArray);
		cout << d << " ";
	}
}

// can only access privating when writing implementation of the methods of the class
int Graph::shortestDistance(int s, int d)
{	//heap is max heap, need order
	//insert all the nodes into array with distance as INT_MAX
	Heap<nodeWeightPair> pq;
	int* distArray = new int[_nv] {0}; //remember delete array
	int* pathArray = new int[_nv] {-1};

	//initialise the heap and distance array
	for (int i = 0; i < _nv; i++) {
		if (i == s) {
			nodeWeightPair temp(s, 0);
			pq.insert(temp);
			distArray[s] = 0;
		}
		else {
			distArray[i] = 1e9;
			nodeWeightPair temp(i, -1e9); //will it delete itself
			pq.insert(temp);
		}
	}

	//set starting vertex estimated distance as 0
	int curr = -1;
	while (!pq.empty()) {
		nodeWeightPair max = pq.extractMax();
		curr = max.nodeIndex();
		if (curr == d) {
			break;
		}
		//update the neighbours
		for (_al[curr].start(); !_al[curr].end(); _al[curr].next()) {
			if (distArray[curr] + _al[curr].current().weight() < distArray[_al[curr].current().nodeIndex()]) {
				pq.deleteItem(nodeWeightPair(_al[curr].current().nodeIndex(), negative(distArray[_al[curr].current().nodeIndex()])));
				pathArray[_al[curr].current().nodeIndex()] = curr; //storing parent of node into pathArray
				distArray[_al[curr].current().nodeIndex()] = distArray[curr] + _al[curr].current().weight();
				nodeWeightPair smaller(_al[curr].current().nodeIndex(), negative(distArray[_al[curr].current().nodeIndex()]));
				pq.insert(smaller);
			}
		}
	}

	int sssp = distArray[d];
	//distance will be max if there is no path between s and d
	if (sssp == 1e9) {
		return -1;
	}
	//print Path
	cout << "Path: ";
	printPath(s, d, pathArray);
	cout << endl;

	delete[] distArray;
	delete[] pathArray;
	return sssp;
}

void Graph::addEdge(int s, int d, int w)
{
	_al[s].insertHead(nodeWeightPair(d, w));
}

void Graph::printGraph()
{
	for (int i=0; i < _nv; i++)
	{
		cout << "Node " << i << ": ";
		for (_al[i].start(); !_al[i].end(); _al[i].next())
			cout << " (" << _al[i].current().nodeIndex() << "," << _al[i].current().weight() << ")";
		cout << endl;

	}

}
Graph::~Graph()
{

	delete[] _al;

}