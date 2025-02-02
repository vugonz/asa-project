#include <vector>
#include <list>
#include <stdio.h>

using namespace std;

enum color {WHITE, GRAY, BLACK};

class Edge {
    private:
        int _weight;
        int _v1;
        int _v2;

    public:
        Edge(int weight, int v1, int v2) {
            _weight = weight;
            _v1 = v1;
            _v2 = v2;
        }

        int getWeight() {
            return _weight;
        }

        int getV1() {
            return _v1;
        }

        int getV2() {
            return _v2;
        }
};

class Vertex {
    private:
        int _n;
        color _color;
        vector<Edge> _adj;

    public:
        Vertex(int n) {
            _n = n;
            _color = WHITE;
        }

        int getNumber() {
            return _n;
        }

        enum color getColor() {
            return _color;
        }
        
        vector<Edge> &getEdges() {
            return _adj;
        }
        
        void setColor(enum color newColor) {
            _color = newColor;
        }

        /*
        * Add and edge from this Vertex to conn Vertex
        */
        void addEdge(Edge conn) {
            _adj.push_back(conn);
        }
};


class Graph {
    private:
        vector <Vertex> vertexes;

    public:
        /*
        * Add Vertex with number n
        */
        void addVertex(int n) {
            vertexes.push_back(Vertex(n));
        }

        vector <Vertex> &getVertexes() {
            return vertexes;
        }

        /*
        * Get reference for Vertex with number n
        */
        Vertex &getVertex(int n) {
            return vertexes[n - 1]; 
        }
};


void dfsVisit(Graph &g, Vertex &v, Graph &g2) {
    v.setColor(GRAY);
    for(Edge e: v.getEdges()) {
        Vertex &visitedVertix = g.getVertex(e.getV2());
        if (visitedVertix.getColor() == WHITE) {
            dfsVisit(g, visitedVertix, g2);
        }
    }
    if (v.getColor() == GRAY) {
        v.setColor(BLACK);
        g2.addVertex(v.getNumber());
    }
}

int main() {
    int n1, n2;
    scanf("%d\n%d", &n1, &n2);

    Graph graph;

    // Initialize Vertexes
    for(int i = 1; i <= n1; ++i) {
        graph.addVertex(i);
    }

    int v1, v2, w; 
    // Read edges
    for(int i = 0; i < n2; ++i) {
        scanf("%d %d %d", &v1, &v2, &w);
        graph.getVertex(v1).addEdge(Edge(w, v1,v2));
        graph.getVertex(v2).addEdge(Edge(w, v1, v2));
    }

    // Using dfs to determine cycles in graph
    for(Vertex &v: graph.getVertexes()) {
        if (v.getColor() == WHITE) {
            Graph cyclicGraph;
            dfsVisit(graph, v, cyclicGraph);
            printf("One cyclig graph found\n");
            for (Vertex v: cyclicGraph.getVertexes()) {
                printf("Vertex nr: %d\n", v.getNumber());
            }
        }
    }
}
