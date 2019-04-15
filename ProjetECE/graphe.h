#ifndef GRAPHE_H
#define GRAPHE_H
#include "sommet.h"
#include <vector>

struct Vertex
{
    float x;
    float y;
};

struct Edge
{
    int vertex1;
    int vertex2;
    std::vector<float> weights;

    bool checkIfVertex(int vertex) const
    {
        return ((vertex == vertex1) || (vertex == vertex2));
    }
};

class graphe
{
    public:
        graphe(std::string,std::string);
        void afficher_graph();
        void Prim(int startId, int weightNum);
        //graphe_weight(std::string);
        virtual ~graphe();

    protected:

    private:
        std::vector<Vertex> vertices;
        std::vector<Edge> edges;
};

#endif // GRAPHE_H
