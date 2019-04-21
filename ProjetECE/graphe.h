#ifndef GRAPHE_H
#define GRAPHE_H
#include "couleur.h"
#include "svgfile.h"
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
	graphe(std::string, std::string, Svgfile *svgout);
	void afficher_graph();
	void Prim(int startId, int weightNum);
	unsigned int countSetBits(unsigned int n);
	std::vector<int> getAllNBitsNumbers(int N, int k);
	void Pareto();
	void Dijkstra();
	void generateSvg();
	//graphe_weight(std::string);
	virtual ~graphe();

protected:

private:
	Svgfile *svgout;
	int weightsNum;
	std::vector<Vertex> vertices;
	std::vector<Edge> edges;
};

#endif // GRAPHE_H
