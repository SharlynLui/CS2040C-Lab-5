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
		cout << " " << s;
	}
	else {
		printPath(s, pathArray[d], pathArray);
		cout << " " << d;
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
	int currentNode = -1;
	while (!pq.empty()) {
		nodeWeightPair max = pq.extractMax();
		currentNode = max.nodeIndex();
		if (currentNode == d) {
			break;
		}
		//update the neighbours
		for (_al[currentNode].start(); !_al[currentNode].end(); _al[currentNode].next()) {
			int currNeighNode = _al[currentNode].current().nodeIndex();
			int newDist = distArray[currentNode] + _al[currentNode].current().weight();
			int neighDist = distArray[_al[currentNode].current().nodeIndex()];
			//replace heap with node with new distance
			if (newDist < neighDist) {
				pq.deleteItem(nodeWeightPair(currNeighNode, negative(neighDist)));
				pathArray[currNeighNode] = currentNode; //storing parent of node into pathArray
				distArray[currNeighNode] = newDist;
				nodeWeightPair newNeighNode(currNeighNode, negative(newDist));
				pq.insert(newNeighNode);
			}
		}
	}

	int sssp = distArray[d];
	//distance will be max if there is no path between s and d
	if (sssp == 1e9) {
		return -1;
	}
	//print Path
	cout << "Path:";
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