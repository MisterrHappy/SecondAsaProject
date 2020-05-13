/* Second ASA project               */
/* Authors: Andre Marinho 93687    */
/*          Joao Domingos 93726    */

#include <iostream>
#include <vector>
#include <limits.h> 
#include <string.h> 
#include <queue> 

using namespace std;

class Graph {

    private:
        int avenues, streets;
        vector<int>* adj, *resAdj;

    public:
        Graph(int Avenues, int Streets) 
        :  avenues(Avenues), streets(Streets), adj(new vector<int>[(Avenues * Streets * 2) + 2]),
        resAdj(new vector<int>[(Avenues * Streets * 2) + 2]) {}

        ~Graph() {
            delete[]adj;
            delete[]resAdj;
        }

        void buildGraph() {
            int iD, vertexes = avenues * streets;

            for (int avenue = 1; avenue <= avenues; avenue++) {
                for (int street = 1; street <= streets; street++) {
                    
                    iD = (avenue - 1) * streets + street;

                    addEdge(iD, iD + vertexes, 1);
                    addEdge(iD + vertexes, iD, 0);

                    if (street != 1) {
                        addEdge(iD + vertexes, iD - 1, 1);
                        addEdge(iD - 1, iD + vertexes, 0);
                    }
        
                    if (street != streets) {
                        addEdge(iD + vertexes, iD + 1, 1);
                        addEdge(iD + 1, iD + vertexes, 0);
                    }

                    if (avenue != 1) {
                        addEdge(iD + vertexes, iD - streets, 1);
                        addEdge(iD - streets, iD + vertexes, 0);
                    }

                    if (avenue != avenues) {
                        addEdge(iD + vertexes, iD + streets, 1);
                        addEdge(iD + streets, iD + vertexes, 0);
                    }
                }
            }
        }

        void addEdge(int vertex, int edge, int capacity) {
            adj[vertex].push_back(edge);
            resAdj[vertex].push_back(capacity);
        }

        void updateResAdj(int v, int vParent, int update) {
            for (int i = 0; i < (int) adj[vParent].size(); i++) {
                if (adj[vParent].at(i) == v) {
                    resAdj[vParent].at(i) += update;
                    break;
                }
            }
        }

        bool bfs(int source, int sink, int parent[]) { 
           
            bool visited[sink + 1]; 
            memset(visited, 0, sizeof(visited)); 

            vector<int>::iterator i;
            queue<int> q; 
            q.push(source); 
            visited[source] = true; 
            parent[source] = -1; 
        
            while (!q.empty()) { 
                int u = q.front(); 
                q.pop(); 
                
                for (int i = 0; i < (int) adj[u].size(); i++) {
                    if (!visited[adj[u].at(i)] && resAdj[u].at(i) > 0 ) {

                        q.push(adj[u].at(i)); 
                        parent[adj[u].at(i)] = u; 
                        visited[adj[u].at(i)] = true; 
                        
                         if (adj[u].at(i) == sink) 
                            return true;
                    } 
                }
            } 
            return false;
        } 

        int fordFulkerson(int source, int sink) { 

            int u, v, parent[sink + 1], max_flow = 0;
            
            while (bfs(source, sink, parent)) { 
                
                for (v = sink; v != source; v = parent[v]) { 
                    u = parent[v];

                    if (v != sink) {
                        updateResAdj(v, u, -1);
                        updateResAdj(u, v, 1);
                        continue;
                    }
                    updateResAdj(v, u, -1);

                } 
                max_flow += 1; 
                memset(parent, 0, sizeof(parent));
            } 
            return max_flow;
        }

};

int main() {

    int avenues, streets, markets, citizens, a, s, vertexes;

    scanf("%d %d", &avenues, &streets);

    vertexes = avenues * streets;

    Graph graph(avenues, streets);
    graph.buildGraph();

    scanf("%d %d", &markets, &citizens);

    while (markets-- != 0) {
        scanf("%d %d", &a, &s);
        graph.addEdge(((a - 1) * streets + s) + vertexes, (vertexes * 2) + 1, 1);
    }

    while (citizens-- != 0) {
        scanf("%d %d", &a, &s);
        graph.addEdge(0, (a - 1) * streets + s, 1);
        graph.addEdge((a - 1) * streets + s, 0, 0);
    }

    cout << graph.fordFulkerson(0, (vertexes * 2) + 1) << endl;

    graph.~Graph();

    exit(EXIT_SUCCESS);
}