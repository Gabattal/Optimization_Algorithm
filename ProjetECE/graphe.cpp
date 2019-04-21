#include "graphe.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>
#include <numeric>
#define FLT_MAX          3.402823466e+38F        // max value

graphe::graphe(std::string nomFichier, std::string nomFichier2, Svgfile *svgout)
{
    this->svgout = svgout;

    std::ifstream file{ nomFichier };
    int verticesNum, edgesNum;
    file >> verticesNum; //on lit la premiere valeur du fichier, elle correspond au nombre de points

    int vertexId, edgeId;
    float x, y, weight;
    int vertex1, vertex2;

    for (int i = 0; i < verticesNum; i++)
    {
        file >> vertexId >> x >> y;
        vertices.push_back(Vertex{ x,y });
    }

    file >> edgesNum; //nombre d'arêtes

    for (int i = 0; i < edgesNum; i++)
    {
        file >> edgeId >> vertex1 >> vertex2; //A chaque ID d'arêtes on associe un point1 et un point2
        edges.push_back(Edge{ vertex1,vertex2 });//qu'on met dans un tableau de structures
    }

    std::ifstream file2{ nomFichier2 };
    file2 >> edgesNum; //nombre d'arêtes
    file2 >> weightsNum;//nombre de poids

    for (int i = 0; i < edgesNum; i++)
    {
        file2 >> edgeId;

        for (int j = 0; j < weightsNum; j++)
        {
            file2 >> weight;
            edges[i].weights.push_back(weight);//A chaque ID d'arête on associe un poid
        }
    }
}

void graphe::afficher_graph()
{
    for (int i = 0; i < edges.size(); i++) //affichage du graphique en utilisant les coordonnées de chaque point
    {
        svgout->addLine(vertices[edges[i].vertex1].x, vertices[edges[i].vertex1].y,
                        vertices[edges[i].vertex2].x, vertices[edges[i].vertex2].y, Couleur{ 255,0,0 });
        if (vertices[edges[i].vertex1].x == vertices[edges[i].vertex2].x)
        {
            svgout->addText(vertices[edges[i].vertex1].x - 10, (vertices[edges[i].vertex1].y + vertices[edges[i].vertex2].y) / 2, edges[i].weights[0], Couleur{ 0,0,255 });
        }
        else if (vertices[edges[i].vertex1].y == vertices[edges[i].vertex2].y)
        {
            svgout->addText((vertices[edges[i].vertex1].x + vertices[edges[i].vertex2].x) / 2, vertices[edges[i].vertex1].y - 2, edges[i].weights[0], Couleur{ 0,0,255 });
        }
        else
        {
            svgout->addText((vertices[edges[i].vertex1].x + vertices[edges[i].vertex2].x) / 2 - 4,
                            (vertices[edges[i].vertex1].y + vertices[edges[i].vertex2].y) / 2, edges[i].weights[0], Couleur{ 0,0,255 });
        }
    }
    for (int i = 0; i < vertices.size(); i++)
    {
        svgout->addDisk(vertices[i].x, vertices[i].y, 10, Couleur{ 0,0,0 });

        if (i < 10)
        {
            svgout->addText(vertices[i].x - 5, vertices[i].y + 5, i, Couleur{ 255,255,255 });
        }
        else
        {
            svgout->addText(vertices[i].x - 8, vertices[i].y + 5, i, Couleur{ 255,255,255 });
        }
    }

    std::cout << "Liste des sommets :\n" << std::endl;//console

    for (int i = 0; i < vertices.size(); i++)
    {
        std::cout << i << "   " << vertices[i].x << "   " << vertices[i].y << std::endl;
    }
    std::cout << "\n";
    std::cout << "Liste des aretes :\n" << std::endl;
    for (int i = 0; i < edges.size(); i++)
    {
        std::cout << i << "   " << edges[i].vertex1 << "   " << edges[i].vertex2 << "   " << "[";
        for (int j = 0; j < edges[i].weights.size(); j++)
        {
            if (j != 0)
            {
                std::cout << ",";
            }
            std::cout << edges[i].weights[j];
        }
        std::cout << "]" << std::endl;
    }
    std::cout << std::endl;
}

void graphe::Prim(int startId, int weightNum)
{
    std::vector<bool> visitedVertices(vertices.size(), false);
    std::vector<int> edgesToCheck;
    std::vector<float> OthersEdges(weightsNum, 0);

    int visitedCount = 0;
    int cursor = startId;
    float shortest = 0;
    int vert1;
    int vert2;


    std::cout << "Shortest way only by using Edge number " << weightNum + 1 << std::endl;

    while (visitedCount < vertices.size()) //on execute cette boucle jusqu'a ce qu on ait parcouru tous les sommets

    {
        std::cout << "Visit vertex " << cursor << std::endl;
        visitedVertices[cursor] = true; //le point déjà visité est set à true
        visitedCount++;

        for (int i = 0; i < edges.size(); i++)
        {
            if (edges[i].checkIfVertex(cursor))
            {
                edgesToCheck.push_back(i); // on push les arêtes par lesquelles on est dejà passés
            }
        }

        auto newEnd = std::remove_if(edgesToCheck.begin(), edgesToCheck.end(), [this, visitedVertices](const int& edge)//fonction pour retourner le point qu on a visité
        {
            return visitedVertices[this->edges[edge].vertex1] && visitedVertices[this->edges[edge].vertex2];
        });

        edgesToCheck.erase(newEnd, edgesToCheck.end());

        std::sort(edgesToCheck.begin(), edgesToCheck.end(), [this, weightNum](const int& edge1, const int& edge2) // on tri les arêtes par ordre croissant de poids
        {
            return this->edges[edge1].weights[weightNum] < this->edges[edge2].weights[weightNum];
        });
        cursor = visitedVertices[edges[edgesToCheck[0]].vertex1] ? edges[edgesToCheck[0]].vertex2 : edges[edgesToCheck[0]].vertex1;

        vert1 = edges[edgesToCheck[0]].vertex1;
        vert2 = edges[edgesToCheck[0]].vertex2;

        svgout->addLine(vertices[vert1].x + 100, vertices[vert1].y,
                        vertices[vert2].x + 100 * (weightNum + 1), vertices[vert2].y, Couleur{ 255,0,0 });

        if (vertices[vert1].x == vertices[vert2].x)
        {
            svgout->addText(vertices[vert1].x - 10 + 100, (vertices[vert1].y + vertices[vert2].y) / 2, edges[edgesToCheck[0]].weights[weightNum], Couleur{ 0,0,255 });
        }
        else if (vertices[vert1].y == vertices[vert2].y)
        {
            svgout->addText((vertices[vert1].x + vertices[vert2].x) / 2 + 100, vertices[vert1].y - 2, edges[edgesToCheck[0]].weights[weightNum], Couleur{ 0,0,255 });
        }
        else
        {
            svgout->addText((vertices[vert1].x + vertices[vert2].x) / 2 - 4 + 100,
                            (vertices[vert1].y + vertices[vert2].y) / 2, edges[edgesToCheck[0]].weights[weightNum], Couleur{ 0,0,255 });
        }


        if (visitedCount != vertices.size() - 1)
        {
            for (int j = 0; j < weightsNum; j++)
            {
                OthersEdges[j] += edges[edgesToCheck[0]].weights[j]; //on calcule les coûts totaux 1 et 2

            }
        }
    }

    for (int i = 0; i < vertices.size(); i++)
    {
        svgout->addDisk(vertices[i].x + 100, vertices[i].y, 10, Couleur{ 0,0,0 });
        if (i < 10)
        {
            svgout->addText(vertices[i].x - 5 + 100, vertices[i].y + 5, i, Couleur{ 255,255,255 });
        }
        else
        {
            svgout->addText(vertices[i].x - 8 + 100, vertices[i].y + 5, i, Couleur{ 255,255,255 });
        }
    }

    for (int j = 0; j < weightsNum; j++)
    {
        std::cout << OthersEdges[j] << " ";
    }
    std::cout << std::endl;
}


std::vector<int> graphe::getAllNBitsNumbers(int N, int k) // fonction qu on utilise pour générer un nombre de bits précis
{
    std::vector<bool> b;

    int j = N;

    while (j--)
    {
        b.push_back(j >= k ? false : true);
    }

    std::vector<int> result;

    do
    {
        result.push_back(std::accumulate(b.rbegin(), b.rend(), 0, [](int x, int y)
        {
            return (x << 1) + y;
        }));
    }
    while (next_permutation(b.begin(), b.end()));


    return result;
    //}
}

void graphe::Pareto()
{

    std::map<std::pair<float, float>, std::pair<bool, std::vector<std::vector<bool>>>> drawedDisk;

    int nb = 0;

    svgout->addLine(50, 350, 50, 50, Couleur{ 0,0,0 });
    svgout->addLine(50, 350, 350, 350, Couleur{ 0,0,0 });

    for (int i = 0; i < 13; i++)
    {
        svgout->addLine(50 + 25 * i, 350, 50 + 25 * i, 50, Couleur{ 0,0,0,0.3f });
        svgout->addLine(50, 350 - 25 * i, 350, 350 - 25 * i, Couleur{ 0,0,0,0.3f });
    }

    std::vector<int> h = getAllNBitsNumbers(edges.size(), vertices.size() - 1);

    std::vector<bool> edgesUsed(edges.size(), false);
    std::vector<bool> verticesUsed(vertices.size(), false);
    std::vector<float> weightWay(weightsNum, 0);

    std::queue<int> pointsToCheck;

    for (auto const &i : h)
    {

        edgesUsed.clear();
        edgesUsed.resize(edges.size(), false);

        verticesUsed.clear();
        verticesUsed.resize(vertices.size(), false);

        weightWay.clear();
        weightWay.resize(weightsNum, 0.0f);

        int n = i;

        for (int j = 0; j < edges.size(); j++)
        {
            if (n & 1) // si le bit selectionné est set à 1
            {
                edgesUsed[edges.size() - 1 - j] = n & 1; //on met les arêtes qu on utilise dans edgeUsed

                for (int k = 0; k < weightsNum; k++)
                {
                    weightWay[k] += edges[edges.size() - 1 - j].weights[k];
                }
            }
            n >>= 1;
        }

        if (drawedDisk.count(std::pair<float, float>(weightWay[0], weightWay[1])))
        {
            if (drawedDisk[std::pair<float, float>(weightWay[0], weightWay[1])].first)
            {
                drawedDisk[std::pair<float, float>(weightWay[0], weightWay[1])].second.push_back(std::vector<bool>());
                continue;
            }
        }

        pointsToCheck = std::queue<int>();
        pointsToCheck.push(0);

        int numberOfVertices = 0;

        do
        {
            int currentPoint = pointsToCheck.front();
            pointsToCheck.pop();
            if (verticesUsed[currentPoint])
            {
                continue;
            }
            verticesUsed[currentPoint] = true;
            numberOfVertices++;

            for (int j = 0; j < edges.size(); j++)
            {
                if (edgesUsed[j])
                {
                    if ((edges[j].vertex1 == currentPoint) && (!verticesUsed[edges[j].vertex2])) //si le point 1 de l arrete i est égal au point selectionné
                    {                                                                            //le point à "checker" est le point 2
                        pointsToCheck.push(edges[j].vertex2);
                    }
                    if ((edges[j].vertex2 == currentPoint) && (!verticesUsed[edges[j].vertex1]))
                    {
                        pointsToCheck.push(edges[j].vertex1);
                    }
                }
            }
        }
        while (pointsToCheck.size() > 0);

        if (numberOfVertices == vertices.size()) //on verifie qu on a parcouru tous les points
        {
            std::pair<float, float> key(weightWay[0], weightWay[1]);
            drawedDisk[key].second.push_back(edgesUsed);

            for (const auto &point2 : drawedDisk)   //on compare les coordonnées d'un point avec les autres pour savoir si il est sur la frontiere de pareto
            {
                if (key == point2.first)
                {
                    continue;
                }
                if (((key.first > point2.first.first) && (key.second >= point2.first.second)) || ((key.first >= point2.first.first) && (key.second > point2.first.second)))
                {
                    drawedDisk[key].first = true;
                }
                if (((key.first < point2.first.first) && (key.second <= point2.first.second)) || ((key.first <= point2.first.first) && (key.second < point2.first.second)))
                {
                    drawedDisk[point2.first].first = true;
                }
            }
        }
    }

    int countExtremum = 0;
    const int numPerLine = 8;

    for (const auto &point : drawedDisk)
    {

        if (!point.second.first)
        {

            svgout->addDisk(point.first.first * 2.5f + 50, -point.first.second * 2.5f + 350, log(point.second.second.size() + 1) * 2, Couleur{ 0,255,0 });

            for (const auto &extremum : point.second.second)
            {
                for (int i = 0; i < extremum.size(); i++)
                {
                    if (extremum[i])
                    {
                        svgout->addLine(25 + 20 * (countExtremum % numPerLine) * 4 + vertices[edges[i].vertex1].x*0.15f, 400 + 80 * (countExtremum / numPerLine) + vertices[edges[i].vertex1].y*0.15f,
                                        25 + 20 * (countExtremum % numPerLine) * 4 + vertices[edges[i].vertex2].x*0.15f, 400 + 80 * (countExtremum / numPerLine) + vertices[edges[i].vertex2].y*0.15f, Couleur{ 0,0,0 });
                    }
                }

                for (int i = 0; i < vertices.size(); i++)
                {
                    svgout->addDisk(25 + 20 * (countExtremum % numPerLine) * 4 + vertices[i].x*0.15f, 400 + 80 * (countExtremum / numPerLine) + vertices[i].y*0.15f, 3, Couleur{ 0,0,0 });
                }

                svgout->addText(25 + 20 * (countExtremum % numPerLine) * 4, 400 + 80 * (countExtremum / numPerLine), "( " + std::to_string((int)point.first.first) + " , " + std::to_string((int)point.first.second) + " )", Couleur{ 50,50,50 });

                countExtremum++;
            }
        }
        else
        {
            svgout->addDisk(point.first.first * 2.5f + 50, -point.first.second * 2.5f + 350, log(point.second.second.size() + 1) / 4.0f, Couleur{ 255,0,0 });
        }
    }
}

auto comp = [](const std::pair<int, int> &a, const std::pair<int, int> &b)
{
    return a.second > b.second;
};

int graphe::weightMin(int StartNode, int sizeVertices, std::vector<std::vector<std::pair<int, int>>> G)///Dijkstra adapté de https://www.40tude.fr/blog/algorithme-de-dijkstra-en-c/
{
    std::vector<int> Distances(sizeVertices, std::numeric_limits<int>::max());

    Distances[StartNode] = 0;

    std::vector<int> Parents(sizeVertices, -1);

    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, decltype(comp)> Q(comp);
    Q.push(std::make_pair(StartNode, 0));

    while (!Q.empty())
    {
        int v = Q.top().first;          //pour avoir le point le plus proche
        int w = Q.top().second;         //pour avoir le poids pour aller au point le plus proche
        Q.pop();

        if (w <= Distances[v])
        {

            for (const auto& l : G[v]) //on calcule toutes les combinaisons possible pour chaque point relié au point v
            {
                auto v2 = l.first;
                auto w2 = l.second;

                if (Distances[v] + w2 < Distances[v2])
                {
                    Distances[v2] = Distances[v] + w2;
                    Parents[v2] = v;
                    Q.push(std::make_pair(v2, Distances[v2]));
                }
            }
        }
    }
    return std::accumulate(Distances.begin(), Distances.end(), 0);
}

void::graphe::Dijkstra()
{
    std::map<std::pair<float, float>, std::pair<bool, std::vector<std::vector<bool>>>> solutions;

    float coeff;

    svgout->addLine(50, 350, 50, 50, Couleur{ 0,0,0 });
    svgout->addLine(50, 350, 350, 350, Couleur{ 0,0,0 });

    for (int i = 0; i < 13; i++)
    {
        svgout->addLine(50 + 25 * i, 350, 50 + 25 * i, 50, Couleur{ 0,0,0,0.3f });
        svgout->addLine(50, 350 - 25 * i, 350, 350 - 25 * i, Couleur{ 0,0,0,0.3f });
    }

    std::vector<bool> edgesUsed(edges.size(), false);
    std::vector<bool> verticesUsed(vertices.size(), false);
    std::vector<float> weightWay(weightsNum, 0);
    std::vector<std::vector<std::pair<int, int>>> graph(vertices.size());

    for (int k = 0; k < edges.size() - vertices.size() + 2; k++) //cette fois on fait varier le compteur binaire pour avoir toutes les solutions avec plus de (nombre de points -1) arêtes
    {
        std::vector<int> h = getAllNBitsNumbers(edges.size(), vertices.size() - 1 + k);
        std::queue<int> pointsToCheck;

        for (auto const &i : h)
        {

            edgesUsed.clear();
            edgesUsed.resize(edges.size(), false);

            verticesUsed.clear();
            verticesUsed.resize(vertices.size(), false);

            weightWay.clear();
            weightWay.resize(weightsNum, 0.0f);

            graph.clear();
            graph.resize(vertices.size());

            int n = i;
            for (int j = 0; j < edges.size(); j++)
            {
                if (n & 1)
                {
                    edgesUsed[j] = n & 1;
                    graph[edges[j].vertex1].push_back(std::make_pair(edges[j].vertex2, edges[j].weights[1]));
                    graph[edges[j].vertex2].push_back(std::make_pair(edges[j].vertex1, edges[j].weights[1]));
                    weightWay[0] += edges[j].weights[0];
                }
                n >>= 1;
            }

            pointsToCheck = std::queue<int>();
            pointsToCheck.push(0);
            int numberOfVertices = 0;

            do
            {
                int currentPoint = pointsToCheck.front();
                pointsToCheck.pop();
                if (verticesUsed[currentPoint])
                {
                    continue;
                }
                verticesUsed[currentPoint] = true;
                numberOfVertices++;

                for (int j = 0; j < edges.size(); j++)
                {
                    if (edgesUsed[j])
                    {

                        if ((edges[j].vertex1 == currentPoint) && (!verticesUsed[edges[j].vertex2]))
                        {
                            pointsToCheck.push(edges[j].vertex2);
                        }
                        if ((edges[j].vertex2 == currentPoint) && (!verticesUsed[edges[j].vertex1]))
                        {
                            pointsToCheck.push(edges[j].vertex1);
                        }
                    }
                }
            }
            while (pointsToCheck.size() > 0);

            if (numberOfVertices == vertices.size())
            {
                for (int StartNode = 0; StartNode < vertices.size(); StartNode++)
                {
                    weightWay[1] += weightMin(StartNode, vertices.size(), graph); // on appelle la fonction pour faire le Dijkstra ici
                }

                std::pair<float, float> key(weightWay[0], weightWay[1]);

                solutions[key].second.push_back(edgesUsed);
                if (solutions.count(std::pair<float, float>(weightWay[0], weightWay[1])))
                {
                    if (solutions[std::pair<float, float>(weightWay[0], weightWay[1])].first)
                    {
                        solutions[std::pair<float, float>(weightWay[0], weightWay[1])].second.push_back(std::vector<bool>());
                        continue;
                    }
                }

                for (const auto &point2 : solutions)
                {
                    if (key == point2.first)
                    {
                        continue;
                    }
                    if (((key.first > point2.first.first) && (key.second >= point2.first.second)) || ((key.first >= point2.first.first) && (key.second > point2.first.second)))
                    {
                        solutions[key].first = true;
                    }
                    if (((key.first < point2.first.first) && (key.second <= point2.first.second)) || ((key.first <= point2.first.first) && (key.second < point2.first.second)))
                    {
                        solutions[point2.first].first = true;
                    }
                }
            }
        }
    }
    int countExtremum = 0;
    const int numPerLine = 8;

    float min_x = FLT_MAX;
    float min_y = FLT_MAX;

    float max_x = 0;
    float max_y = 0;

    int maxSize = 0;

    for (const auto &point : solutions)
    {
        float current_x = point.first.first;
        float current_y = point.first.second;

        min_x = std::min(min_x, current_x);
        min_y = std::min(min_y, current_y);

        max_x = std::max(max_x, current_x);
        max_y = std::max(max_y, current_y);

        maxSize = std::max(maxSize, (int)point.second.second.size());
    }

    for (const auto &point : solutions)
    {
        float current_x = point.first.first;
        float current_y = point.first.second;

        current_x = (current_x - min_x) / (max_x - min_x);
        current_y = (current_y - min_y) / (max_y - min_y);

        if (!point.second.first)
        {
            svgout->addDisk(75 + current_x * 250, 325 - current_y * 250, log(point.second.second.size() + 1) / log(maxSize+1) * 10.0f, Couleur{ 0,255,0 });

            for (const auto &extremum : point.second.second)
            {
                for (int i = 0; i < extremum.size(); i++)
                {
                    if (extremum[i])
                    {
                        svgout->addLine(25 + 20 * (countExtremum % numPerLine) * 4 + vertices[edges[i].vertex1].x*0.15f, 400 + 80 * (countExtremum / numPerLine) + vertices[edges[i].vertex1].y*0.15f,
                                        25 + 20 * (countExtremum % numPerLine) * 4 + vertices[edges[i].vertex2].x*0.15f, 400 + 80 * (countExtremum / numPerLine) + vertices[edges[i].vertex2].y*0.15f, Couleur{ 0,0,0 });
                    }
                }

                for (int i = 0; i < vertices.size(); i++)
                {
                    svgout->addDisk(25 + 20 * (countExtremum % numPerLine) * 4 + vertices[i].x*0.15f, 400 + 80 * (countExtremum / numPerLine) + vertices[i].y*0.15f, 3, Couleur{ 0,0,0 });
                }

                svgout->addText(25 + 20 * (countExtremum % numPerLine) * 4, 400 + 80 * (countExtremum / numPerLine), "(" + std::to_string((int)point.first.first) + ", " + std::to_string((int)point.first.second) + ")", Couleur{ 50,50,50 });

                countExtremum++;
            }
        }
        else
        {
            svgout->addDisk(75 + current_x * 250, 325 - current_y * 250, log(point.second.second.size() + 1) / log(maxSize+1) * 4.0f, Couleur{ 255,0,0 });
        }
    }
}


graphe::~graphe()
{
    //dtor
}
