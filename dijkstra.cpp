/*By Eric 15/01/2021 -Dijkstra algorithm- */
#include <iostream>

#define CONVERT_CHAR_TO_INDEX(caracter) (caracter - 'A') 
#define CONVERT_INT_TO_CHAR(integer) (char(integer))
#define INFINITE (100000)

using namespace std;

// LINKED LIST STRUCTURE
struct Node
{
	char vertex;
	char parent;
	bool isVisited;
	int cost;
	Node *next;
};

class Graph
{
	private:
		Node **adjacencyList;
		int nVertices;
		
		Node *createVertex(char vertex, int cost);
		void insertList(Node *&edges, char vertex, int cost);
		void printList(Node *edges);
		void setParents(Node *edges, Node *parent);
		
	public:
		Graph();
		Graph(int nVertices);
		void setAdjacencyList();
		void showAdjacencyList();
		void dijkstra(char start);
		void clearRoutes();
		void getShortestPath(char start, char end, int cost);
		bool isEmpty();
};

Graph::Graph()
{
	nVertices = 0;
}

Graph::Graph(int nVertices)
{
	adjacencyList = new Node*[nVertices];
	
	for (int v = 0; v < nVertices; v++){
		// CREATE HASH TABLE
		adjacencyList[v] = NULL;
		insertList(adjacencyList[v], CONVERT_INT_TO_CHAR(v + 65), INFINITE);
	}
	
	this->nVertices = nVertices;
}

Node *Graph::createVertex(char vertex, int cost)
{
	Node *newNode = new Node();
	
	newNode->vertex = vertex;
	newNode->cost = cost;
	newNode->next = NULL;
	newNode->isVisited = false;
	newNode->parent = ' ';
	
	return newNode; 
}

void Graph::setAdjacencyList()
{
	int cost;
	char vertex;
	char option;
	char currentVertex;
	
	for (int v = 0; v < nVertices; v++) {
		currentVertex = CONVERT_INT_TO_CHAR(v + 65);
		cout<< "\n\n\t Add the routes of "<< currentVertex<< endl;
		
		// CREATE ROUTE
		do{
			cout<< "\n [Warning]-Would you like to add routes? [s/n]: ";
			cin>> option;
			
			option = toupper(option);
			
			if (option != 'S') {
				break;
			}
			
			cout<< "\n\n "<< currentVertex<< "--> ";
			cin>> vertex;
			
			vertex = toupper(vertex);
			
			cout<< " Type the cost from "<< currentVertex<< " TO "<< vertex<< ": ";
			cin>> cost;
			
			// INSERT ROUTE
			int index = CONVERT_CHAR_TO_INDEX(vertex);
			insertList(adjacencyList[index], currentVertex, cost);
			insertList(adjacencyList[v], vertex, cost);
			
		} while (option == 'S');
		
		cout<< "\n";
	}
}

void Graph::insertList(Node *&edges, char vertex, int cost)
{
	// INSERT ALWAYS AT THE END OF THE LIST
	if (edges == NULL) {
		Node *newNode = createVertex(vertex, cost);
		edges = newNode;
		return;		
	}
	
	// KEEP ITERATING
	insertList(edges->next, vertex, cost);
}

void Graph::showAdjacencyList()
{
	cout<< "\n\n\t\t\tShowing Adjacency List...\n"<< endl;
	cout<< "\n\t\tVertices\t\t\t\tEdges\n\n"<< endl;
	
	// ITERATE EACH OF THE LISTS
	for (int v = 0; v < nVertices; v++) {
		printList(adjacencyList[v]);
		cout<< "\n\n";	
	}	
}

void Graph::printList(Node *edges)
{
	// END OF THE LIST
	if (edges == NULL) {
		return;
	}
	
	cout<< " ("<< edges->vertex<< ") -|- cost: "<< edges->cost<< "   ";
	
	if (edges->isVisited) {
		cout<< "PARENT-> "<< edges->parent<< "  |--> ";
	}
	
	// KEEP ITERATING
    printList(edges->next);
}

void Graph::dijkstra(char start)
{
	int index = CONVERT_CHAR_TO_INDEX(start); 
	
	adjacencyList[index]->cost = 0;
	setParents(adjacencyList[index]->next, adjacencyList[index]);
}

void Graph::setParents(Node *edges, Node *parent)
{
	// END OF THE LIST
	if (edges == NULL) {
		
		// CHOOSE THE MINIMUM NODE NOT VISITED
		int min = INFINITE;
		int vertex = 0;
				
		for (int v  = 0; v < nVertices; v++) {
			if (adjacencyList[v]->cost < min && !adjacencyList[v]->isVisited) {
				min = adjacencyList[v]->cost;
				vertex = v;
			}		
		}
		
		// ALL NODES WERE VISITED
		if (vertex == 0) {
			return;
		}
		
		// CONTINUE WITH A NODE NOT VISITED
		return setParents(adjacencyList[vertex]->next, adjacencyList[vertex]);	
	}
    
    // GET NEIGHBOR
    int index = CONVERT_CHAR_TO_INDEX(edges->vertex);
    
    parent->isVisited = true;
    
    // MODIFY NODE PARENT AND COST OF OUR NEIGHBORS NOT VISITED BY THE LOWER PATH
    if (edges->cost + parent->cost < adjacencyList[index]->cost && !adjacencyList[index]->isVisited) {
    	adjacencyList[index]->cost = edges->cost + parent->cost;
    	adjacencyList[index]->parent = parent->vertex;	
	}
	
	// CONTINUE WITH THE NEXT EDGE
    setParents(edges->next, parent);
}

void Graph::getShortestPath(char start, char end, int cost)
{
	if (start == end) {
		cout<< "("<< start<< ")\n"<< endl;
		cout<< " Total cost: "<< cost<< "\n"<< endl;
		
		return;
	}
	
	int index = CONVERT_CHAR_TO_INDEX(end);
	
	// GET COST FROM THE END
	if (cost == 0) {
		cost = adjacencyList[index]->cost;
	}
	
	cout<< "("<< adjacencyList[index]->vertex<< ")<--";
	
	// KEEP SEARCHING
	getShortestPath(start, adjacencyList[index]->parent, cost);	
}

bool Graph::isEmpty() 
{
	return nVertices == 0 ? true : false; 
}

void Graph::clearRoutes()
{
	for (int v = 0; v < nVertices; v++) {
		adjacencyList[v]->parent = ' ';
		adjacencyList[v]->cost = INFINITE;
		adjacencyList[v]->isVisited = false;
	}
}

int main()
{
	Graph *graph = new Graph();
	int nVertices;
	char start, end;
	
	int option;
	
	do {
		cout<< "\t DIJKSTRA ALGORITHM\n"<< endl;
		cout<< "\t.::MENU::.\n"<< endl;
		cout<< " [1] Create Graph"<< endl;
		cout<< " [2] Shortest Path"<< endl;
		cout<< " [3] Exit"<< endl;
		cout<< "\n Choose: ";
		cin>>option;
		
		switch(option) {
			case 1:
				delete graph;
				
				cout<< "\n\n Type the number of vertices ";
				cin>> nVertices;
				
				graph = new Graph(nVertices);
				
				graph->setAdjacencyList();
				break;
				
			case 2:
				if (!graph->isEmpty()) {
					graph->clearRoutes();
					
					cout<< "\n\n from what point would you like to start? ";
					cin>> start;
					
					cout<< "\n\n to what point would like to go? ";
					cin>> end;
					
					start = toupper(start);
					end = toupper(end);
					
					graph->dijkstra(start);
					graph->showAdjacencyList();
					
					cout<< "\n\n The shortest path: ";
					graph->getShortestPath(start, end, 0);	
				} else {
					cout<< "\n\n [Warning]-there's no a graph\n"<< endl;
				}
				break;
				
			case 3:
				cout<< "\n\n\t**Big thanks for using this program**\n"<< endl;
				break;
				
			default:
				cout<< "\n\n\tWrong option... try again!\n"<< endl;
		}
		
		system("pause");
		system("cls");
	} while (option != 3);
	
	return 0;
}
