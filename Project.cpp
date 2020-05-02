/* Second ASA project               */
/* Authors: Andre Marinho 93687    */
/*          Joao Domingos 93726    */

#include <iostream>
#include <vector>

using namespace std;

class Graph {

    private:
        int vNumber;
        vector<int>* adj;

    public:
        Graph(int Number) 
        : vNumber(Number), adj(new vector<int>[Number]) {}

        ~Graph() {
            delete[]adj;
        }

        void addEdge(int vertex, int edge) {
            adj[vertex - 1].push_back(edge - 1);
        }
};

int main(int argc, char* argv[]) {

    int avenues, streets, markets, citizens, vertexes = 0;

    scanf("%d %d", &avenues, &streets);

    vertexes = avenues * streets;

    Graph graph(vertexes);

    // aqui vamos construir as ligações do grafo

    scanf("%d %d", &markets, &citizens);
    
    graph.~Graph();

    exit(EXIT_SUCCESS);
}
