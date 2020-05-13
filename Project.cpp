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
                    
                    addEdge(iD, iD + vertexes);
                    addEdge(iD + vertexes, iD);
                      
                    if (i == 1 || i == avenues) {
                        if (i == 1) {
                            addEdge(iD + vertexes, iD + streets);
                            addEdge(iD + streets, iD + vertexes);
                        }
                        
                        else if (i == avenues) {
                            addEdge(iD + vertexes, iD - streets);
                            addEdge(iD - streets, iD + vertexes);
                        }

                        if (j == 1) {
                            addEdge(iD + vertexes, iD + 1);
                            addEdge(iD + 1, iD + vertexes);
                        }
                        
                        else if (j == streets) {
                            addEdge(iD + vertexes, iD - 1);
                            addEdge(iD - 1, iD + vertexes);
                        }
                        
                        else {
                            addEdge(iD + vertexes, iD - 1);
                            addEdge(iD - 1, iD + vertexes);
                            
                            addEdge(iD + vertexes, iD + 1);
                            addEdge(iD + 1, iD + vertexes);
                        }
                        continue;
                    }
                    
                    if(j == 1 || j == streets){
                        if (j == 1) {
                            addEdge(iD + vertexes, iD + 1);
                            addEdge(iD + 1, iD + vertexes);
                        }
                        
                        else if (j == streets) {
                            addEdge(iD + vertexes, iD - 1);
                            addEdge(iD - 1, iD + vertexes);
                        }
                        
                        if (i == avenues){
                            addEdge(iD + vertexes, iD - streets);
                            addEdge(iD - streets, iD + vertexes);
                        }
                        
                        else {
                            addEdge(iD + vertexes, iD + streets);
                            addEdge(iD + vertexes, iD - streets);

                            addEdge(iD + streets, iD + vertexes);
                            addEdge(iD - streets, iD + vertexes);
                        }
                        continue;
                    }

                    else { 
                        addEdge(iD + vertexes, iD + 1);
                        addEdge(iD + 1, iD + vertexes);

                        addEdge(iD + vertexes, iD - 1);
                        addEdge(iD - 1, iD + vertexes);

                        addEdge(iD + vertexes, iD + streets);
                        addEdge(iD + streets, iD + vertexes);
                        
                        addEdge(iD + vertexes, iD - streets);
                        addEdge(iD - streets, iD + vertexes);
                    }
                }
            }
        }

        void addEdge(int vertex, int edge) {
            adj[vertex].push_back(edge);
            resAdj[vertex].push_back(1);
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
                
                for (int i = 0; i < adj[u].size(); i++) {
                    if (!visited[adj[u].at(i)] && resAdj[u].at(i) > 0 ) { 
                        q.push(adj[u].at(i)); 
                        parent[adj[u].at(i)] = u; 
                        visited[adj[u].at(i)] = true; 
                        
                        if (adj[u].at(i) == sink) {
                            puts("entrei");
                            return true;
                        }
                    } 
                }
            } 
            puts("Boas");
            return false;
        } 

        int fordFulkerson(int source, int sink, int citizens, int markets) { 

            int u, v, parent[sink], max_flow = 0;
            
            while (citizens != 0 || markets != 0) { 
                
                if (bfs(source, sink, parent)) {
                    citizens--;
                    markets--;
                    
                    for (v = sink; v != source; v = parent[v]) { 
                        u = parent[v]; 
                        
                        for (int i = 0; i < adj[u].size(); i++) {
                            if (adj[u].at(i) == v) {
                                resAdj[u].at(i) -= 1;
                                if (u != source && v != sink)
                                    resAdj[v].at(i) += 1;
                                break;
                            }
                        }
                        if (v != sink) {
                            resAdj[v].at(0) -= 1;
                            resAdj[v - (avenues * streets)].at(0) += 1;
                        }
                    } 
                    max_flow += 1;
                    
                    continue;
                } 
                return max_flow; 
            }  
            return max_flow;
        }

};

int main(int argc, char* argv[]) {

    int avenues, streets, markets, citizens, a, s, vertexes, marketsCpy, citizensCpy;

    scanf("%d %d", &avenues, &streets);

    vertexes = avenues * streets;

    Graph graph(avenues, streets);
    graph.buildGraph();

    scanf("%d %d", &markets, &citizens);

    marketsCpy = markets;
    citizensCpy = citizens;

    while (markets-- != 0) {
        scanf("%d %d", &a, &s);
        graph.addEdge(((a - 1) * streets + s) + vertexes, (vertexes * 2) + 1);
    }

    while (citizens-- != 0) {
        scanf("%d %d", &a, &s);
        graph.addEdge(0, (a - 1) * streets + s);
    }

    cout << graph.fordFulkerson(0, (vertexes * 2) + 1, citizensCpy, marketsCpy) << endl;

    graph.~Graph();

    exit(EXIT_SUCCESS);
}