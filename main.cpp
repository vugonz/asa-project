#include <vector>
#include <list>
#include <stdio.h>

using namespace std;

enum color {WHITE, GRAY, BLACK};

class Edge {
    private:
        int _weight;
        int _dest;

    public:
        Edge(int weight, int dest) {
            _weight = weight;
            _dest = dest;
        }

        int getWeight() {
            return _weight;
        }

        int getDest() {
            return _dest;
        }

        void printEdge() {
            printf("Edge of weight %d, destionation Vertix nr %d\n", _weight, _dest);
        }
};

class Vertix {
    private:
        int _n;
        color _color;
        vector<Edge> _adj;
        

    public:
        Vertix(int n) {
            _n = n;
            _color = WHITE;
        }

        void setColor(enum color newColor) {
            _color = newColor;
        }

        int getNumber() {
            return _n;
        }

        /*
        * Add and edge from this Vertix to conn Vertix
        */
        void addEdge(Edge conn) {
            _adj.push_back(conn);
        }

        vector<Edge> getEdges() {
            return _adj;
        }

        enum color getColor() {
            return _color;
        }

        void printVertix() {
            printf("Vertix nr: %d\n", _n);
            for(Edge e: _adj) {
                e.printEdge();
            }
            printf("\n");
        }
};


class Graph {
    public:
        vector <Vertix> vertixes;
        /*
        * Add Vertix with number n
        */
        void addVertix(int n) {
            vertixes.push_back(Vertix(n));
        }

        vector <Vertix> &getVertixes() {
            return vertixes;
        }

        /*
        * Get reference for Vertix with number n
        */
        Vertix &getVertix(int n) {
            return vertixes[n - 1]; 
        }

        void printGraph() {
            for (Vertix v: vertixes) {
                v.printVertix();
            }
        }

};


void DfsVisit(Graph &g, Vertix &v) {
    v.setColor(GRAY);
    for(Edge e: v.getEdges()) {
        Vertix &visitedVector = g.getVertix(e.getDest());
        if (visitedVector.getColor() == WHITE) {
            DfsVisit(g, visitedVector);
        }
    }
    v.setColor(BLACK);
}

int main() {
    int n1, n2;
    scanf("%d\n%d", &n1, &n2);

    Graph graph;

    // Initialize vertixes
    for(int i = 0; i < n1; ++i) {
        graph.addVertix(i + 1);
    }

    int v1, v2, w; 
    // Read edges
    for(int i = 0; i < n2; ++i) {
        scanf("%d %d %d", &v1, &v2, &w);
        graph.getVertix(v1).addEdge(Edge(w, v2));
        graph.getVertix(v2).addEdge(Edge(w, v1));
    }

    // Using DFS to determine cycles in graph
    for(Vertix v: graph.getVertixes()) {
        if (v.getColor() == WHITE) {
            DfsVisit(graph, v);
            printf("One cyclig graph found\n");
        }
    }
}
