/* Second ASA project               */
/* Authors: Andre Marinho 93687    */
/*          Joao Domingos 93726    */

#include <iostream>
#include <vector>
#include <limits.h> 
#include <string.h> 
#include <queue> 

using namespace std;

typedef struct Vertex {
    bool citizens = false;
    bool markets = false;
    int weight = 1;

} Vertex;


class Graph {

    private:
        int avenues, streets;
        vector<int>* adj;

    public:
        Graph(int Avenues, int Streets) 
        :  avenues(Avenues), streets(Streets), adj(new vector<int>[(Avenues * Streets) + 2]) {}

        ~Graph() {
            delete[]adj;
        }

        void buildGraph() {
            int iD;
            for (int i = 1; i <= avenues; i++) {
                for (int j = 1; j <= streets; j++) {
                    
                    iD = (i - 1) * streets + j;  
                    if (i == 1 || i == avenues) {
                        if (i == 1) 
                            addEdge(iD, iD + streets);
                        
                        else if (i == avenues)
                            addEdge(iD, iD - streets);

                        if (j == 1) 
                            addEdge(iD, iD + 1);
                        
                        else if (j == streets) 
                            addEdge(iD, iD - 1);
                        
                        else {
                            addEdge(iD, iD - 1);
                            addEdge(iD, iD + 1);
                        }
                        continue;
                    }
                    
                    if(j == 1 || j == streets){
                        if (j == 1) 
                            addEdge(iD, iD + 1);
                        
                        else if (j == streets)
                            addEdge(iD, iD - 1);
                        
                        if (i == avenues)
                            addEdge(iD, iD - streets);
                        
                        else {
                            addEdge(iD, iD + streets);
                            addEdge(iD, iD - streets);
                        }
                        continue;
                    }

                    else { 
                        addEdge(iD, iD + 1);
                        addEdge(iD, iD - 1);
                        addEdge(iD, iD + streets);
                        addEdge(iD, iD - streets);
                    }
                }
            }
        }

        void addEdge(int vertex, int edge) {
            adj[vertex].push_back(edge);
        }

        void connectSource(vector<Vertex> vInfo) {
            for (int i = 1; i <= (avenues * streets); i++) {
                if (vInfo[i].citizens)
                    addEdge(0, i);
            }    
        }

        void connectEnd(vector<Vertex> vInfo) {
            for (int i = 1; i <= (avenues * streets); i++) {
                if (vInfo[i].markets)
                    addEdge(i, (avenues * streets) + 2);
            }
        }

        bool bfs(int s, int t, int parent[]) { 

            int v;
            // Create a visited array and mark all vertices as not visited 
            bool visited[(avenues * streets) + 2]; 
            memset(visited, 0, sizeof(visited)); 
        
            // Create a queue, enqueue source vertex and mark source vertex 
            // as visited 
            queue <int> q; 
            q.push(s); 
            visited[s] = true; 
            parent[s] = -1; 
        
            // Standard BFS Loop 
            while (!q.empty()) { 
                int u = q.front(); 
                q.pop(); 

                vector<int>::iterator i; 
        
                for (i = adj[u].begin(); i != adj[u].end(); ++i) { 
                    v = *i;
                    if (visited[v]==false && adj[u][v] > 0) { 
                        q.push(v); 
                        parent[v] = u; 
                        visited[v] = true; 
                    } 
                } 
            } 
        
            // If we reached sink in BFS starting from source, then return 
            // true, else false 
            return (visited[t] == true); 
        } 
        
};
/* Returns true if there is a path from source 's' to sink 't' in 
  residual graph. Also fills parent[] to store the path */
  
// Returns the maximum flow from s to t in the given graph 
int fordFulkerson(int graph[V][V], int s, int t) 
{ 
    int u, v; 
  
    // Create a residual graph and fill the residual graph with 
    // given capacities in the original graph as residual capacities 
    // in residual graph 
    int rGraph[V][V]; // Residual graph where rGraph[i][j] indicates  
                     // residual capacity of edge from i to j (if there 
                     // is an edge. If rGraph[i][j] is 0, then there is not)   
    for (u = 0; u < V; u++) 
        for (v = 0; v < V; v++) 
             rGraph[u][v] = graph[u][v]; 
  
    int parent[V];  // This array is filled by BFS and to store path 
  
    int max_flow = 0;  // There is no flow initially 
  
    // Augment the flow while tere is path from source to sink 
    while (bfs(rGraph, s, t, parent)) 
    { 
        // Find minimum residual capacity of the edges along the 
        // path filled by BFS. Or we can say find the maximum flow 
        // through the path found. 
        int path_flow = INT_MAX; 
        for (v=t; v!=s; v=parent[v]) 
        { 
            u = parent[v]; 
            path_flow = min(path_flow, rGraph[u][v]); 
        } 
  
        // update residual capacities of the edges and reverse edges 
        // along the path 
        for (v=t; v != s; v=parent[v]) 
        { 
            u = parent[v]; 
            rGraph[u][v] -= path_flow; 
            rGraph[v][u] += path_flow; 
        } 
  
        // Add path flow to overall flow 
        max_flow += path_flow; 
    } 
  
    // Return the overall flow 
    return max_flow; 
} 

int main(int argc, char* argv[]) {

    int avenues, streets, markets, citizens, a, s, vertexes;

    Vertex v;
    vector<Vertex> vertexInfo;

    scanf("%d %d", &avenues, &streets);

    vertexes = (avenues * streets) + 2;

    while (vertexes-- != 0)
        vertexInfo.push_back(v);

    Graph graph(avenues, streets);
    graph.buildGraph();

    scanf("%d %d", &markets, &citizens);

    while (markets-- != 0) {
        scanf("%d %d", &a, &s);
        vertexInfo.at((a - 1) * streets + s).markets = true;
    }

    while (citizens-- != 0) {
        scanf("%d %d", &a, &s);
        vertexInfo.at((a - 1) * streets + s).citizens = true;
    }

    graph.connectSource(vertexInfo);
    graph.connectEnd(vertexInfo);
    graph.~Graph();

    exit(EXIT_SUCCESS);
}
