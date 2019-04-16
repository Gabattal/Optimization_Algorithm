#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>



graphe::graphe(std::string nomFichier, std::string nomFichier2)
{
    std::ifstream file{nomFichier};
    int verticesNum, edgesNum;
    file>>verticesNum;

    int vertexId, edgeId;
    float x,y, weight;
    int vertex1, vertex2;

    for(int i=0; i<verticesNum; i++)
    {
        file>>vertexId>>x>>y;
        vertices.push_back(Vertex{x,y});
    }

    file>>edgesNum;

    for(int i=0; i<edgesNum; i++)
    {
        file>>edgeId>>vertex1>>vertex2;
        edges.push_back(Edge{vertex1,vertex2});
    }

    std::ifstream file2{nomFichier2};
    file2>>edgesNum;
    file2>>weightsNum;

    for(int i=0; i<edgesNum; i++)
    {
        file2>>edgeId;

        for (int j=0; j<weightsNum; j++)
        {
            file2>>weight;
            edges[i].weights.push_back(weight);
        }
    }
}

void graphe::afficher_graph()
{
    std::cout<<"Liste des sommets :\n"<<std::endl;

    for(int i=0; i< vertices.size(); i++)
    {
        std::cout<<i<<"   "<<vertices[i].x<<"   "<<vertices[i].y<<std::endl;
    }
    std::cout<<"\n";
    std::cout<<"Liste des aretes :\n"<<std::endl;
    for(int i=0; i<edges.size() ; i++)
    {
        std::cout<<i<<"   "<<edges[i].vertex1<<"   "<<edges[i].vertex2<<"   "<<"[";
        for (int j=0; j<edges[i].weights.size(); j++)
        {
            if (j!=0)
            {
                std::cout<<",";
            }
            std::cout<<edges[i].weights[j];
        }
        std::cout<<"]"<<std::endl;
    }
    std::cout<<std::endl;
}

void graphe::Prim(int startId, int weightNum)
{
    std::vector<bool> visitedVertices(vertices.size(), false);
    std::vector<int> edgesToCheck;
    std::vector<float> OthersEdges(weightsNum,0);

    int visitedCount = 0;
    int cursor = startId;
    float shortest = 0;

    std::cout<<"Shortest way only by using Edge number "<<weightNum+1<<std::endl;

    while (visitedCount < vertices.size())
    {
        std::cout<<"Visit vertex "<< cursor<<std::endl;
        visitedVertices[cursor]=true;
        visitedCount++;

        for(int i=0; i<edges.size(); i++)
        {
            if (edges[i].checkIfVertex(cursor))
            {
                edgesToCheck.push_back(i);
            }
        }

        auto newEnd = std::remove_if(edgesToCheck.begin(), edgesToCheck.end(), [this, visitedVertices](const int& edge)
        {
            return visitedVertices[this->edges[edge].vertex1] && visitedVertices[this->edges[edge].vertex2];
        });

        edgesToCheck.erase(newEnd, edgesToCheck.end());

        std::sort(edgesToCheck.begin(), edgesToCheck.end(), [this, weightNum](const int& edge1, const int& edge2)
        {
            return this->edges[edge1].weights[weightNum] < this->edges[edge2].weights[weightNum];
        });
        cursor = visitedVertices[edges[edgesToCheck[0]].vertex1] ? edges[edgesToCheck[0]].vertex2 : edges[edgesToCheck[0]].vertex1;
        //std::cout<<edges[edgesToCheck[0]].weights[weightNum];

        if(visitedCount!=vertices.size()-1)
        {
            for(int j=0; j<weightsNum; j++)
            {
                    OthersEdges[j]+=edges[edgesToCheck[0]].weights[j];
            }
        }
    }

    for(int j=0; j<weightsNum; j++)
    {
        std::cout<<OthersEdges[j]<<" ";
    }
    std::cout<<std::endl;

}


graphe::~graphe()
{
    //dtor
}
