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
        vector<int>* adj;
        vector<int>* resAdj;

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

            for (int i = 1; i <= avenues; i++) {
                for (int j = 1; j <= streets; j++) {
                    
                    iD = (i - 1) * streets + j;
                    
                    addEdge(iD, iD + vertexes, 1);
                    addEdge(iD + vertexes, iD, 0);
                      
                    if (i == 1 || i == avenues) {
                        if (i == 1) {
                            addEdge(iD + vertexes, iD + streets, 1);
                            addEdge(iD + streets, iD + vertexes, 0);
                        }
                        
                        else if (i == avenues) {
                            addEdge(iD + vertexes, iD - streets, 1);
                            addEdge(iD - streets, iD + vertexes, 0);
                        }

                        if (j == 1) {
                            addEdge(iD + vertexes, iD + 1, 1);
                            addEdge(iD + 1, iD + vertexes, 0);
                        }
                        
                        else if (j == streets) {
                            addEdge(iD + vertexes, iD - 1, 1);
                            addEdge(iD - 1, iD + vertexes, 0);
                        }
                        
                        else {
                            addEdge(iD + vertexes, iD - 1, 1);
                            addEdge(iD - 1, iD + vertexes, 0);
                            
                            addEdge(iD + vertexes, iD + 1, 1);
                            addEdge(iD + 1, iD + vertexes, 0);
                        }
                        continue;
                    }
                    
                    if(j == 1 || j == streets){
                        if (j == 1) {
                            addEdge(iD + vertexes, iD + 1, 1);
                            addEdge(iD + 1, iD + vertexes, 0);
                        }
                        
                        else if (j == streets) {
                            addEdge(iD + vertexes, iD - 1, 1);
                            addEdge(iD - 1, iD + vertexes, 0);
                        }
                        
                        if (i == avenues){
                            addEdge(iD + vertexes, iD - streets, 1);
                            addEdge(iD - streets, iD + vertexes, 0);
                        }
                        
                        else {
                            addEdge(iD + vertexes, iD + streets, 1);
                            addEdge(iD + vertexes, iD - streets, 0);

                            addEdge(iD + streets, iD + vertexes, 1);
                            addEdge(iD - streets, iD + vertexes, 0);
                        }
                        continue;
                    }

                    else { 
                        addEdge(iD + vertexes, iD + 1, 1);
                        addEdge(iD + 1, iD + vertexes, 0);

                        addEdge(iD + vertexes, iD - 1, 1);
                        addEdge(iD - 1, iD + vertexes, 0);

                        addEdge(iD + vertexes, iD + streets, 1);
                        addEdge(iD + streets, iD + vertexes, 0);
                        
                        addEdge(iD + vertexes, iD - streets, 1);
                        addEdge(iD - streets, iD + vertexes, 0);
                    }
                }
            }
        }

        /* void printGraph() {
            vector<int>::iterator j;
            for (int i = 0; i < ((avenues * streets * 2) + 2); i++) {
                for (j = adj[i].begin(); j != adj[i].end(); ++j) {
                    cout << *j << "  ";
                }
                cout << "\n";
            }
            cout << "\n";

            for (int i = 0; i < ((avenues * streets * 2) + 2); i++) {
                for (j = resAdj[i].begin(); j != resAdj[i].end(); ++j) {
                    cout << *j << "  ";
                }
                cout << "\n";
            }
        } */

        void addEdge(int vertex, int edge, int capacity) {
            adj[vertex].push_back(edge);
            resAdj[vertex].push_back(capacity);
        }

        int checkEdge(int index) {
            vector<int>::iterator i; 
            for (i = adj[index].begin(); i != adj[index].end(); ++i) 
                return *i;
            return -1;
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
                
                for (unsigned int i = 0; i < adj[u].size(); i++) {
                    if (!visited[adj[u].at(i)] && resAdj[u].at(i) > 0 ) { 
                        q.push(adj[u].at(i)); 
                        parent[adj[u].at(i)] = u; 
                        visited[adj[u].at(i)] = true; 
                        
                        if (adj[u].at(i) == sink) {
                            return true;
                        }
                    } 
                }
            } 
            return false;
        } 

        int fordFulkerson(int source, int sink) { 

            int u, v, parent[sink], max_flow = 0;
            
            while (bfs(source, sink, parent)) { 
                
                for (v = sink; v != source; v = parent[v]) { 
                    u = parent[v];

                    if (v == sink) {
                        for (unsigned int i = 0; i < adj[u].size(); i++) {
                            if (adj[u].at(i) == v) {
                                resAdj[u].at(i) -= 1;
                                break;
                            }
                        }
                        continue;
                    }
                    
                    for (unsigned int i = 0; i < adj[u].size(); i++) {
                        if (adj[u].at(i) == v) {
                            resAdj[u].at(i) -= 1;
                            break;
                        }
                    }

                    for (unsigned int i = 0; i < adj[v].size(); i++) {
                        if (adj[v].at(i) == v) {
                            resAdj[v].at(i) += 1;
                            break;
                        }
                    }
                } 
                max_flow += 1; 
            }  
            return max_flow;
        }

};

int main(int argc, char* argv[]) {

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