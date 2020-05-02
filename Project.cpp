/* Second ASA project               */
/* Authors: Andre Marinho 93687    */
/*          Joao Domingos 93726    */

#include <iostream>
#include <vector>

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

};

int main(int argc, char* argv[]) {

    int avenues, streets, markets, citizens, a, s;

    vector<Vertex> vertexInfo;

    scanf("%d %d", &avenues, &streets);

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
