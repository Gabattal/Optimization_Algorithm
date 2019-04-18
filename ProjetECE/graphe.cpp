#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <math.h>

graphe::graphe(std::string nomFichier, std::string nomFichier2, Svgfile *svgout)
{
    this->svgout = svgout;

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
    for(int i=0; i<edges.size(); i++) //svg
    {
        svgout->addLine(vertices[edges[i].vertex1].x,vertices[edges[i].vertex1].y,
                        vertices[edges[i].vertex2].x,vertices[edges[i].vertex2].y,Couleur{255,0,0});
        if(vertices[edges[i].vertex1].x==vertices[edges[i].vertex2].x)
        {
            svgout->addText(vertices[edges[i].vertex1].x-10,(vertices[edges[i].vertex1].y+vertices[edges[i].vertex2].y)/2,edges[i].weights[0],Couleur{0,0,255});
        }
        else if(vertices[edges[i].vertex1].y==vertices[edges[i].vertex2].y)
        {
            svgout->addText((vertices[edges[i].vertex1].x+vertices[edges[i].vertex2].x)/2,vertices[edges[i].vertex1].y-2,edges[i].weights[0],Couleur{0,0,255});
        }
        else
        {
            svgout->addText((vertices[edges[i].vertex1].x+vertices[edges[i].vertex2].x)/2-4,
                            (vertices[edges[i].vertex1].y+vertices[edges[i].vertex2].y)/2,edges[i].weights[0],Couleur{0,0,255});
        }
    }
    for(int i=0; i<vertices.size() ; i++)
    {
        svgout->addDisk(vertices[i].x, vertices[i].y, 10, Couleur{0,0,0});

        if(i<10)
        {
            svgout->addText(vertices[i].x-5, vertices[i].y+5,i, Couleur{255,255,255});
        }
        else
        {
            svgout->addText(vertices[i].x-8, vertices[i].y+5,i, Couleur{255,255,255});
        }
    }

    std::cout<<"Liste des sommets :\n"<<std::endl;//console

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
    int vert1;
    int vert2;


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

        vert1=edges[edgesToCheck[0]].vertex1;
        vert2=edges[edgesToCheck[0]].vertex2;

        svgout->addLine(vertices[vert1].x+800*(weightNum+1),vertices[vert1].y,
                        vertices[vert2].x+800*(weightNum+1),vertices[vert2].y,Couleur{255,0,0});

        if(vertices[vert1].x==vertices[vert2].x)
        {
            svgout->addText(vertices[vert1].x-10+800,(vertices[vert1].y+vertices[vert2].y)/2,edges[edgesToCheck[0]].weights[weightNum],Couleur{0,0,255});
        }
        else if(vertices[vert1].y==vertices[vert2].y)
        {
            svgout->addText((vertices[vert1].x+vertices[vert2].x)/2+800,vertices[vert1].y-2,edges[edgesToCheck[0]].weights[weightNum],Couleur{0,0,255});
        }
        else
        {
            svgout->addText((vertices[vert1].x+vertices[vert2].x)/2-4+800,
                            (vertices[vert1].y+vertices[vert2].y)/2,edges[edgesToCheck[0]].weights[weightNum],Couleur{0,0,255});
        }


        if(visitedCount!=vertices.size()-1)
        {
            for(int j=0; j<weightsNum; j++)
            {
                OthersEdges[j]+=edges[edgesToCheck[0]].weights[j];

            }
        }
    }

    for(int i=0; i<vertices.size() ; i++)
    {
        svgout->addDisk(vertices[i].x+800, vertices[i].y, 10, Couleur{0,0,0});
        if(i<10)
        {
            svgout->addText(vertices[i].x-5+800, vertices[i].y+5,i, Couleur{255,255,255});
        }
        else
        {
            svgout->addText(vertices[i].x-8+800, vertices[i].y+5,i, Couleur{255,255,255});
        }
    }

    for(int j=0; j<weightsNum; j++)
    {
        std::cout<<OthersEdges[j]<<" ";
    }
    std::cout<<std::endl;
}



void graphe::Pareto()
{


    //compteur binaire
    std::vector<std::vector <int>> edgesUsed
                                (pow(2.0,edges.size()),
                                 std::vector<int>(edges.size()));;

    for(int i = 0; i < pow(2.0,edges.size()); i++)
    {
        for(int j = (edges.size()-1); j >= 0; j--)
        {
            //std::cout<<edges.size()-j-1<<std::endl;
            std::cout << ((i & (1 << j)) >> j);
            if(((i & (1 << j)) >> j)==1)
            {
                edgesUsed[i][edges.size()-1-j]=1;
                std::cout<<"["<<i<<"]["<<edges.size()-1-j<<"]";
            }
        }
        std::cout << std::endl;
    }

    for(int i = 0; i <edges.size(); ++i)
    {
        //std::cout<<"coucou";
        for(int j=0 ; j<edges.size(); i++)
        {
            if(edgesUsed[i][j]==1)
            {
                std::cout<<" "<<edges[j].vertex1<<"-"<<edges[j].vertex2;
            }
        }
        std::cout<<std::endl;
    }
//utiliser vecteurs booléens
}

void graphe::generateSvg()
{


}



graphe::~graphe()
{
    //dtor
}
