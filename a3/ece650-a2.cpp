#include<iostream>
#include <vector>
#include <regex>
#include <bits/stdc++.h>
using namespace std;
class Graph
{
  
public:
    int V;			// No. of vertices
    std::vector < int >*adj;  // Pointer to an array containing adjacency 
    Graph (int V);		// Constructor
    void addEdge (int v, int w); // function to add an edge to graph
    int BFS (vector < int >adj[], int src, int dest, int v, int pred[]); // prints BFS traversal from a given source s
    void printShortestDistance (vector < int >adj[], int s, int dest, int v); //computes shortest distance path if exists
};

Graph::Graph (int V)    //Constructor definition
{
  this->V = V;
  adj = new vector < int >[V];
}

void Graph::addEdge (int v, int w)
{
  //since the graph isunweighted
  adj[v].push_back (w);		// Add w to v's list.
  adj[w].push_back (v);		// Add v to w's list.
}

int Graph::BFS (vector < int >adj[], int src, int dest, int v,
	    int pred[])         // refrences https://www.geeksforgeeks.org/shortest-path-unweighted-graph/
{
  vector < int >queue;  // creating a queue vector
  bool visited[v];  //checks if the vertex has been visited or not

   for (int i = 0; i < v; i++)  //Loop to intialize all vertices to unvisited and paths to max
    {
      visited[i] = false;
      pred[i] = -1;
    }

  visited[src] = true; // setting source to visited
  queue.push_back (src); 

  
  while (!queue.empty ())// standard BFS algorithm
    {
      int q = queue.front ();
      if (queue.size()){ //check if there any elements in the vector array
            queue.erase(queue.begin()); //erase the first element
        }
      for (unsigned int i = 0; i < adj[q].size (); i++)
	  {
	  if (visited[adj[q][i]] == false)
	    {
	      visited[adj[q][i]] = true;
	      pred[adj[q][i]] = q;
	      queue.push_back (adj[q][i]);
	      if (adj[q][i] == dest)
		    return 1;
	    }

	  }
    }

  return 0;
}

void Graph::printShortestDistance (vector < int >adj[], int s, int dest, int v)
{
  int pred[v];
  if (BFS (adj, s, dest, v, pred) == 0)
    {
      cout << "Error: vertices are not connected."<< endl;
      return;
    }
  vector < int >path; 
  int c = dest;
  path.push_back (c);
  while (pred[c] != -1)
    {
      path.push_back (pred[c]);
      c = pred[c];
    }
  int i;
  for ( i = path.size () - 1; i > 0; i--)
    cout << path[i] << "-";
  cout <<path[i]<< endl;
}

Graph *g;
int main ()
{
    int v=1;    
    while(!std::cin.eof()){
        std::string line;
        std::getline(std::cin,line);
        regex expr("-?[0-9]+"); //match consectuive numbers
        sregex_iterator next(line.begin(), line.end(), expr);
        sregex_iterator end;
        
        if (line.empty()){
            continue;
        }
        if (line[0] == 'V' && line[1] == ' '){
	    std::cout << line << endl;
            v = stoi(line.substr(2));
            v=v+1;
            delete g;
            g = new Graph(v);
        }
        if (line[0] == 'E' && line[1] == ' '){
	    std::cout << line << endl;
            while (next != end) {
                smatch var1;
                smatch var2;
                var1 = *next;
                next++;
                if (next != end) {
                    var2 = *next;
                    int e0 = std::stoi(var1.str());
                    int e1 = std::stoi(var2.str());
                    if (e0>=v or e1>=v or e0<0 or e1<0 or e0==e1){
                        std::cout << "Error: edges entered are not valid." << endl;
                        break;
                    }
                    else{
                        g->addEdge(e0,e1);
                    }
                    next++;
            }
        }
        }
        if (line[0] == 's' && line[1] == ' '){
            while (next != end) {
                smatch var1;
                smatch var2;
                var1 = *next;
                next++;
                if (next != end) {
                    var2 = *next;
                    int src = std::stoi(var1.str());
                    int dest = std::stoi(var2.str());
                    next++;
                    if (src >= v or dest >= v) {
                        std::cout << "Error: source or destination entered do not exist." << endl;
                    }
                    else{
                        g->printShortestDistance(g->adj,src,dest,v);
                    }
                }    
            }

        }
    }

  return 0;
}
